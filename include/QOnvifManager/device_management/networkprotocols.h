#ifndef NETWORKPROTOCOLS_H
#define NETWORKPROTOCOLS_H
#include <QObject>
#include <QList>
#include <QDomElement>
namespace ONVIF {
    class NetworkProtocols : public QObject {
        Q_OBJECT
    public:
        QDomElement toxml();
        explicit NetworkProtocols(QObject *parent = NULL);
        virtual ~NetworkProtocols();

        QList<QString> getNetworkProtocolsName()
        {
            return m_networkProtocolsName;
        }

        void setNetworkProtocolsName(QString networkProtocolsName)
        {
            m_networkProtocolsName.push_back(networkProtocolsName);
        }

        QList<bool> getNetworkProtocolsEnabled()
        {
            return m_networkProtocolsEnabled;
        }

        void setNetworkProtocolsEnabled(bool networkProtocolsEnabled)
        {
            m_networkProtocolsEnabled.push_back(networkProtocolsEnabled);
        }

        QList<int> getNetworkProtocolsPort()
        {
            return m_networkProtocolsPort;
        }

        void setNetworkProtocolsPort(int networkProtocolsPort)
        {
            m_networkProtocolsPort.push_back(networkProtocolsPort);
        }

        bool result() const
        {
            return m_result;
        }
        void setResult(bool result)
        {
            m_result = result;
        }

    private:
        QList<QString> m_networkProtocolsName;
        QList<bool> m_networkProtocolsEnabled;
        QList<int> m_networkProtocolsPort;
        bool m_result;
    };
}
#endif // NETWORKPROTOCOLS_H
