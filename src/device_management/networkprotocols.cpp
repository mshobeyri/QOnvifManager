#include "networkprotocols.h"
#include "message.h"
using namespace ONVIF;
QDomElement
NetworkProtocols::toxml() {
    QDomElement setNetworkProfiles;
    setNetworkProfiles = newElement("SetNetworkProtocols");
    for (int i = 0; i < m_networkProtocolsName.length(); i++) {
        QDomElement networkprotocol = newElement("NetworkProtocols");
        QDomElement name    = newElement("Name", m_networkProtocolsName[i]);
        QDomElement enabled = newElement(
            "Enabled", m_networkProtocolsEnabled[i] ? "true" : "false");
        QDomElement port =
            newElement("Port", QString::number(m_networkProtocolsPort[i]));

        networkprotocol.appendChild(name);
        networkprotocol.appendChild(enabled);
        networkprotocol.appendChild(port);
        setNetworkProfiles.appendChild(networkprotocol);
    }
    return setNetworkProfiles;
}

NetworkProtocols::NetworkProtocols(QObject* parent) : QObject(parent) {}
NetworkProtocols::~NetworkProtocols() {}
