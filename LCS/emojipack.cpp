#include "emojipack.h"

#include <QDir>
#include <QDomElement>
#include <QRegularExpression>
#include <QStandardPaths>
#include <QtConcurrent/QtConcurrentRun>
#include <QTimer>

QStringList loadDefaultPaths();
static const QStringList DEFAULT_PATHS = loadDefaultPaths();
static const QString RICH_TEXT_PATTERN = QStringLiteral("<img title=\"%1\" src=\"key%1\"\\>");
static const QString EMOTICONS_FILE_NAME = QStringLiteral("emoticons.xml");
static constexpr int CLEANUP_TIMEOUT = 5 * 60 *1000;// 5minutes maximum time;

QStringList loadDefaultPaths()
{
    const QString EMOTICONS_SUB_PATH = QDir::separator() + QStringLiteral("emoticons");
    QStringList paths{":/emojis","~/.kde4/share/emoticons","~/kde/share/emoticons",EMOTICONS_SUB_PATH};

    //
    QStandardPaths::StandardLocation location;
    location = QStandardPaths::AppDataLocation;

    QStringList locations = QStandardPaths::standardLocations(location);


    locations.append(QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation));
    for(QString qtoxPath : locations){
        qtoxPath.append(EMOTICONS_SUB_PATH);
        if(!paths.contains(qtoxPath)){
            paths.append(qtoxPath);
        }
    }
    return paths;
}

//把传递的字符串转换成HTML引用
QString getAsRichText(const QString&key){return RICH_TEXT_PATTERN.arg(key);}

emojiPack::emojiPack():cleanupTimer{new QTimer(this)}
{
    loadingMutex.lock();
    emoticonPack = ":/emoticons/emoticons.xml";
    QtConcurrent::run(this,&emojiPack::load,emoticonPack);

    connect(cleanupTimer,&QTimer::timeout ,this,&emojiPack::cleanupIconsCache);
    cleanupTimer->start(CLEANUP_TIMEOUT);

}
emojiPack::~emojiPack(){delete cleanupTimer;}

//加载表情包 用loadingMutex
bool emojiPack::load(const QString &fileName)
{
    QFile xmlFile(fileName);
    if(!xmlFile.exists()|| !xmlFile.open(QIODevice::ReadOnly)){
        loadingMutex.unlock();
        return false;
    }

    QDomDocument doc;
    doc.setContent(xmlFile.readAll());
    xmlFile.close();

    path = QFileInfo(fileName).absolutePath();
    QDomNodeList emoticonElements = doc.elementsByTagName("emoticon");
    const QString itemName = QStringLiteral("file");
    const QString childName = QStringLiteral("string");
    const int iconsCount = emoticonElements.size();
    emoticons.clear();
    emoticonToPath.clear();
    cachedIcon.clear();

    for(int i = 0; i<iconsCount; i++){
        QDomNode node = emoticonElements.at(i);
        QString iconName = node.attributes().namedItem(itemName).nodeValue();
        QString iconPath = QDir{path}.filePath(iconName);
        QDomElement stringElement = node.firstChildElement(childName);
        QStringList emoticonList;
        while(!stringElement.isNull()){
            QString emoticon = stringElement.text().replace("<","&lt;").replace(">","&gt;");
            emoticonToPath.insert(emoticon,iconPath);
            emoticonList.append(emoticon);
            stringElement = stringElement.nextSibling().toElement();
        }
        emoticons.append(emoticonList);
    }
    loadingMutex.unlock();
    return true;
}
//清除Icon缓存
void emojiPack::cleanupIconsCache()
{
    QMutexLocker locker(&loadingMutex);
    for(auto i = cachedIcon.begin(); i !=cachedIcon.end();){
        std::shared_ptr<QIcon>&icon = i->second;
        if(icon.use_count()==1){
            i = cachedIcon.erase(i);
        }
        else
            ++i;
    }
}
//返回单例实例
emojiPack &emojiPack::getInstance()
{
    static emojiPack emojiPacks;
    return emojiPacks;
}

//在每个传递的路径中以2的深度收缩所有名为emojis.xml的文件
QList<QPair<QString, QString> > emojiPack::listEmojiPack(const QStringList &paths)
{
    QList<QPair<QString,QString>> emoticonPacks;

    const QString homePath = QDir::homePath();
    for(QString path : paths){
        if(path.startsWith('-')){
            path.replace(0,1,homePath);
        }
        QDir dir(path);
        if(!dir.exists())
            continue;

        //解析cfg文件
        for(const QString &subdirectory: dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)){
            dir.cd(subdirectory);
            if(dir.exists(EMOTICONS_FILE_NAME)){
                QString absPath = dir.absolutePath()+QDir::separator() + EMOTICONS_FILE_NAME;
                QPair<QString,QString> p {dir.dirName(),absPath};
                if(!emoticonPacks.contains(p)){
                    emoticonPacks.append(p);
                }
            }

            dir.cdUp();
        }
    }
    return emoticonPacks;
}

QList<QPair<QString,QString>> emojiPack::listEmojiPack(){
    return listEmojiPack(DEFAULT_PATHS);
}

//用其相应的图标文件名将所有找到的文本表情符号替换为HTML引用
QString emojiPack::emojiField(const QString &msg)
{
    QMutexLocker locker(&loadingMutex);
    QString result(msg);
    for(auto r = emoticonToPath.begin();r != emoticonToPath.end(); r++){
        QRegularExpression exp;
        if(r.key().toUcs4().length() == 1)
            exp.setPattern(r.key());
        else //像 ：） 的模式，在单词不能匹配，不然会打标点和html标签
            exp.setPattern(QStringLiteral(R"((?<=^|\s))")+ QRegularExpression::escape(r.key())+QStringLiteral(R"((?=$|\s))"));

        int replaceDiff = 0;
        QRegularExpressionMatchIterator iter = exp.globalMatch(result);
        while(iter.hasNext()){
            QRegularExpressionMatch match = iter.next();
            int startPos = match.capturedStart();
            int keyLength = r.key().length();
            QString imgRichText = getAsRichText(r.key());
            result.replace(startPos + replaceDiff, keyLength,imgRichText);
            replaceDiff += imgRichText.length() - keyLength;
        }
    }
    return result;
}

//返回从文件中提取的所有表情符，进行分组
QList<QStringList> emojiPack::getEmoticons() const{
    QMutexLocker locker(&loadingMutex);
    return emoticons;
}

//根据传递的emoticon获取图标
//return根据传递的emoticon返回缓存的图标，托没有映射到该emoticon的图标，返回null
std::shared_ptr<QIcon> emojiPack::getAsIcon(const QString &key) const
{
    QMutexLocker locket(&loadingMutex);
    if(cachedIcon.find(key) != cachedIcon.end()){
        return cachedIcon[key];
    }
    const auto iconPath = emoticonToPath.find(key);
    if(iconPath == emoticonToPath.end())
        return std::make_shared<QIcon>();

    const QString &iconPaths = iconPath.value();
    auto icon = std::make_shared<QIcon>(iconPaths);
    cachedIcon[key] = icon;
    return icon;
}
void emojiPack::on_EmojiPack_Changed(const QString& path){
    loadingMutex.lock();
    QtConcurrent::run(this,&emojiPack::load,path);
}
