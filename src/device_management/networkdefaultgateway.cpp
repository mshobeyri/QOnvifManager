#include "networkdefaultgateway.h"
#include "message.h"

using namespace ONVIF;
NetworkDefaultGateway::NetworkDefaultGateway() {}

QDomElement
NetworkDefaultGateway::toxml() {
    QDomElement setNetworkDefaltGateway, ipv4Address;
    setNetworkDefaltGateway = newElement("SetNetworkDefaultGateway");
    setNetworkDefaltGateway.setAttribute(
        "xmlns", "http://www.onvif.org/ver10/device/wsdl");
    ipv4Address = newElement("IPv4Address", this->ipv4Address());
    setNetworkDefaltGateway.appendChild(ipv4Address);
    return setNetworkDefaltGateway;
}
