#ifndef NETWORKDEFAULTGATEWAY_H
#define NETWORKDEFAULTGATEWAY_H
#include <QDomElement>
#include <QObject>

namespace ONVIF {
Q_PROPERTY(QString ipv4Address READ ipv4Address WRITE setIpv4Address)
Q_PROPERTY(QString ipv6Address READ ipv6Address WRITE setIpv6Address)
class NetworkDefaultGateway: public QObject
{
    Q_OBJECT
public:
    NetworkDefaultGateway();
    QDomElement toxml();
    QString ipv4Address() const
    {
        return m_ipv4Address;
    }
    void setIpv4Address(const QString &ipv4Address)
    {
        m_ipv4Address = ipv4Address;
    }
    QString ipv6Address() const
    {
        return m_ipv6Address;
    }
    void setIpv6Address(const QString &ipv6Address)
    {
        m_ipv6Address = ipv6Address;
    }

private:
    QString m_ipv4Address;
    QString m_ipv6Address;
};
}
#endif // NETWORKDEFAULTGATEWAY_H
