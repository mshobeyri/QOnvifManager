#ifndef NETWORKDISCOVERYMODE_H
#define NETWORKDISCOVERYMODE_H
#include <QDomElement>
#include <QObject>

namespace ONVIF {
class NetworkDiscoveryMode
{
public:
    NetworkDiscoveryMode();
    QString discoveryMode() const
    {
        return m_discoveryMode;
    }
    void setDiscoveryMode(const QString &discoveryMode)
    {
        m_discoveryMode = discoveryMode;
    }

private:
    QString m_discoveryMode;

};
}
#endif // NETWORKDISCOVERYMODE_H
