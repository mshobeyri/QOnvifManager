#ifndef NETWORKHOSTNAME_H
#define NETWORKHOSTNAME_H

#include <QDomElement>
#include <QObject>

namespace ONVIF {
class NetworkHostname
{
public:
    NetworkHostname();
    bool dhcp() const
    {
        return m_dhcp;
    }
    void setDhcp(bool dhcp)
    {
        m_dhcp = dhcp;
    }

    QString name() const
    {
        return m_name;
    }
    void setName(const QString &name)
    {
        m_name = name;
    }

private:
    bool m_dhcp;
    QString m_name;
};
}
#endif // NETWORKHOSTNAME_H
