#ifndef NETWORKDNS_H
#define NETWORKDNS_H
#include <QDomElement>
#include <QObject>

namespace ONVIF {

class NetworkDNS : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool dhcp READ dhcp WRITE setDhcp)
    Q_PROPERTY(QString searchDomain READ searchDomain WRITE setSearchDomain)
    Q_PROPERTY(QStringList manualType READ manualType WRITE setManualType)
    Q_PROPERTY(QStringList ipv4Address READ ipv4Address WRITE setIpv4Address)
public:
    NetworkDNS();
    QDomElement toxml();
    bool dhcp() const {
        return m_dhcp;
    }
    void setDhcp(bool dhcp) {
        m_dhcp = dhcp;
    }

    QString searchDomain() const {
        return m_searchDomain;
    }
    void setSearchDomain(const QString& searchDomain) {
        m_searchDomain = searchDomain;
    }

    QStringList manualType() const {
        return m_manualType;
    }
    void setManualType(const QStringList& manualType) {
        m_manualType = manualType;
    }

    QStringList ipv4Address() const {
        return m_ipv4Address;
    }
    void setIpv4Address(const QStringList& ipv4Address) {
        m_ipv4Address = ipv4Address;
    }

private:
    bool        m_dhcp;
    QString     m_searchDomain;
    QStringList m_manualType;
    QStringList m_ipv4Address;
};
}
#endif // NETWORKDNS_H
