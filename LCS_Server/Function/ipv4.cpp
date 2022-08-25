#include "ipv4.h"

#include <QMainWindow>

#include <QHostAddress>
#include <QNetworkInterface>

IPv4::IPv4()
{
    DeviceIP = getIPv4Address();
}

QString IPv4::getIPv4Address()
{
    QString currentIP;

    const QHostAddress &localHost = QHostAddress(QHostAddress::LocalHost);

    for(const QHostAddress &address: QNetworkInterface::allAddresses()) {

        if(address.protocol() == QAbstractSocket::IPv4Protocol && address != localHost) {
            currentIP = address.toString();
        }
    }

    return currentIP;
}
