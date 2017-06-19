#ifndef NETWORKDEFAULTGATEWAY_H
#define NETWORKDEFAULTGATEWAY_H
#include <QDomElement>
#include <QObject>

namespace ONVIF {
class NetworkDefaultGateway
{
public:
    NetworkDefaultGateway();
    QString ipv4Address() const
    {
        return m_ipv4Address;
    }
    void setIpv4Address(const QString &ipv4Address)
    {
        m_ipv4Address = ipv4Address;
    }

private:
    QString m_ipv4Address;
};
}
#endif // NETWORKDEFAULTGATEWAY_H
