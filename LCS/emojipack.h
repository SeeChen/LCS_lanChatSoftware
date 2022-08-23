#ifndef EMOJIPACK_H
#define EMOJIPACK_H

#include <QObject>
#include<QIcon>
#include<QMap>
#include<QMutex>
#include<QMutexLocker>

#include <memory>

class emojiPack : public QObject
{
    Q_OBJECT
public:
    //explicit emojiPack(QObject *parent = nullptr);
    emojiPack();
    static emojiPack& getInstance();

    static QList<QPair<QString,QString>>listEmojiPack(const QStringList &paths);
    static QList<QPair<QString,QString>> listEmojiPack();
    QString emojiField(const QString &msg);
    QList<QStringList> getEmoticons() const;
    std::shared_ptr<QIcon> getAsIcon(const QString &key) const;

public slots:
    void on_EmojiPack_Changed(const QString & path);
    void cleanupIconsCache();

private:
    emojiPack(emojiPack&) = delete;
    emojiPack& operator = (const emojiPack&) = delete;
    ~emojiPack() override;

    bool load(const QString& fileName);

    mutable std::map<QString,std::shared_ptr<QIcon>> cachedIcon;
    QHash<QString,QString> emoticonToPath;
    QList<QStringList> emoticons;
    QString path;
    QTimer *cleanupTimer;
    mutable QMutex loadingMutex;

    QString emoticonPack;

};
#endif // EMOJIPACK_H
