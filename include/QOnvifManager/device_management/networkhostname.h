#ifndef NETWORKHOSTNAME_H
#define NETWORKHOSTNAME_H

#include <QDomElement>
#include <QObject>

namespace ONVIF {
class NetworkHostname : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool dhcp READ dhcp WRITE setDhcp)
    Q_PROPERTY(QString name READ name WRITE setName)
public:
    NetworkHostname();
    QDomElement toxml();
    bool        dhcp() const {
        return m_dhcp;
    }
    void setDhcp(bool dhcp) {
        m_dhcp = dhcp;
    }

    QString name() const {
        return m_name;
    }
    void setName(const QString& name) {
        m_name = name;
    }

    bool result() const {
        return m_result;
    }
    void setResult(bool result) {
        m_result = result;
    }

private:
    bool    m_dhcp;
    QString m_name;
    bool    m_result;
};
}
#endif // NETWORKHOSTNAME_H
