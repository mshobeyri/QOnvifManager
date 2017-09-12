#ifndef NETWORKNTP_H
#define NETWORKNTP_H

#include <QDomElement>
#include <QObject>

namespace ONVIF {
class NetworkNTP : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool dhcp READ dhcp WRITE setDhcp)
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString manualType READ manualType WRITE setManualType)
    Q_PROPERTY(QString ipv4Address READ ipv4Address WRITE setIpv4Address)
    Q_PROPERTY(QString ipv6Address READ ipv6Address WRITE setIpv6Address)
public:
    NetworkNTP();
    QDomElement toxml();
    bool        dhcp() const {
        return m_dhcp;
    }
    void setDhcp(bool dhcp) {
        m_dhcp = dhcp;
    }

    QString manualType() const {
        return m_manualType;
    }
    void setManualType(const QString& manualType) {
        m_manualType = manualType;
    }

    QString ipv4Address() const {
        return m_ipv4Address;
    }
    void setIpv4Address(const QString& ipv4Address) {
        m_ipv4Address = ipv4Address;
    }

    QString ipv6Address() const {
        return m_ipv6Address;
    }
    void setIpv6Address(const QString& ipv6Address) {
        m_ipv6Address = ipv6Address;
    }

    bool result() const {
        return m_result;
    }
    void setResult(bool result) {
        m_result = result;
    }

    QString name() const {
        return m_name;
    }
    void setName(const QString& name) {
        m_name = name;
    }

private:
    bool    m_dhcp;
    QString m_name;
    QString m_manualType;
    QString m_ipv4Address;
    QString m_ipv6Address;
    bool    m_result;
};
}
#endif // NETWORKNTP_H
