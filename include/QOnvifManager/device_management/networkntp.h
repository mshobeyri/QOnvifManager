#ifndef NETWORKNTP_H
#define NETWORKNTP_H

#include <QDomElement>
#include <QObject>

namespace ONVIF {
class NetworkNTP: public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool dhcp READ dhcp WRITE setDhcp)
    Q_PROPERTY(QString manualType READ manualType WRITE setManualType)
    Q_PROPERTY(QString ipv4Address READ ipv4Address WRITE setIpv4Address)
public:
    NetworkNTP();
    QDomElement toxml();
    bool dhcp() const
    {
        return m_dhcp;
    }
    void setDhcp(bool dhcp)
    {
        m_dhcp = dhcp;
    }

    QString manualType() const
    {
        return m_manualType;
    }
    void setManualType(const QString &manualType)
    {
        m_manualType = manualType;
    }

    QString ipv4Address() const
    {
        return m_ipv4Address;
    }
    void setIpv4Address(const QString &ipv4Address)
    {
        m_ipv4Address = ipv4Address;
    }

private:
    bool m_dhcp;
    QString m_manualType;
    QString m_ipv4Address;
};
}
#endif // NETWORKNTP_H
