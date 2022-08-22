#ifndef ENUM_VAR_H
#define ENUM_VAR_H

// 客户端进行的行为
enum todoAction {
    LOGIN,          // 0 : 登录操作
    REGISTER,       // 1 : 注册账号
    SENDMESSAGE,    // 2 : 发送消息
    EDITPROFILE,    // 3 : 编辑个人资料
    ONLINELIST      // 4 : 当前在线列表
};

enum serverAction {
    ERROR,
    MESSAGE,
    VERIFIED
};

enum messageType {
    TEXT,
    IMAGE,
    VIDEO,
    FILE_
};

#endif // ENUM_VAR_H
