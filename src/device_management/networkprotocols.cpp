#include "networkprotocols.h"
#include "message.h"
using namespace ONVIF;
QDomElement
NetworkProtocols::toxml() {
    QDomElement setNetworkProtocols;
    setNetworkProtocols = newElement("SetNetworkProtocols");
    for (int i = 0; i < m_networkProtocolsName.length(); i++) {
        QDomElement networkprotocol = newElement("NetworkProtocols");
        QDomElement name = newElement("Name", m_networkProtocolsName[i]);
        name.setAttribute("xmlns", "http://www.onvif.org/ver10/schema");
        QDomElement enabled = newElement(
            "Enabled", m_networkProtocolsEnabled[i] ? "true" : "false");
        enabled.setAttribute("xmlns", "http://www.onvif.org/ver10/schema");
        QDomElement port =
            newElement("Port", QString::number(m_networkProtocolsPort[i]));
        port.setAttribute("xmlns", "http://www.onvif.org/ver10/schema");

        networkprotocol.appendChild(name);
        networkprotocol.appendChild(enabled);
        networkprotocol.appendChild(port);
        setNetworkProtocols.appendChild(networkprotocol);
    }
    return setNetworkProtocols;
}

NetworkProtocols::NetworkProtocols(QObject* parent) : QObject(parent) {}
NetworkProtocols::~NetworkProtocols() {}
