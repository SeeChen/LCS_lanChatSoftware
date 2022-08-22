// 获取本机 IPv4 地址
#ifndef IPV4_H
#define IPV4_H

#include <QMainWindow>

class IPv4
{
public:
    QString DeviceIP;

    IPv4();
private:
    QString getIPv4Address();
};

#endif // IPV4_H
