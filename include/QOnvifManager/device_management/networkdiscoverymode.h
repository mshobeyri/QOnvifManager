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
    QString     discoveryMode() const {
        return m_discoveryMode;
    }
    void setDiscoveryMode(const QString& discoveryMode) {
        m_discoveryMode = discoveryMode;
    }

    bool result() const {
        return m_result;
    }
    void setResult(bool result) {
        m_result = result;
    }

private:
    QString m_discoveryMode;
    bool    m_result;
};
}
#endif // NETWORKDISCOVERYMODE_H
