QT       += core gui network sql
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chat.cpp \
    chatlist.cpp \
    chatwindow.cpp \
    launcher.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    register.cpp \
    userdatabase.cpp

HEADERS += \
    Function/ENUM_VAR.h \
    chat.h \
    chatlist.h \
    chatwindow.h \
    enum_Var.h \
    launcher.h \
    login.h \
    mainwindow.h \
    register.h \
    userdatabase.h

FORMS += \
    UI/mainwindow.ui \
    chat.ui \
    chatlist.ui \
    chatwindow.ui \
    launcher.ui \
    login.ui \
    register.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    LCSimage.qrc
