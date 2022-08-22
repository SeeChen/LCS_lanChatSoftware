// 枚举变量头文件 : 用于定义各种行为的变量
#ifndef TODOACTION_H
#define TODOACTION_H

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

#endif // TODOACTION_H
