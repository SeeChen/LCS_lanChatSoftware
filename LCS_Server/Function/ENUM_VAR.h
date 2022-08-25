#ifndef ENUM_VAR_H
#define ENUM_VAR_H

// 客户端执行的操作
enum ClientAction {

    REGISTER   ,    // 请求注册
    LOGIN      ,    // 请求登录
    SENDMESSAGE,    // 请求发送消息
    EDITPROFILE,    // 请求编辑个人资料
    ALLUSER    ,    // 请求所有用户
};

enum ServerAction {
    ERROR     ,     // 返回请求错误
    MESSAGE   ,     // 返回信息
    ONLINE    ,     // 返回在线列表
    ALL       ,     // 返回所有用户列表
    SUCCESSFUL,     // 返回成功信息
};

#endif // ENUM_VAR_H
