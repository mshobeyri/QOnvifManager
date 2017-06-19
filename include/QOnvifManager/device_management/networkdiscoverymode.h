#ifndef NETWORKDISCOVERYMODE_H
#define NETWORKDISCOVERYMODE_H
#include <QDomElement>
#include <QObject>

namespace ONVIF {

class NetworkDiscoveryMode : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString discoveryMode READ discoveryMode WRITE setDiscoveryMode)
public:
    NetworkDiscoveryMode();
    QDomElement toxml();
    QString discoveryMode() const {
        return m_discoveryMode;
    }
    void setDiscoveryMode(const QString& discoveryMode) {
        m_discoveryMode = discoveryMode;
    }

private:
    QString m_discoveryMode;
};
}
#endif // NETWORKDISCOVERYMODE_H
