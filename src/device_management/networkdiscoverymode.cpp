#include "networkdiscoverymode.h"
#include "message.h"
using namespace ONVIF;
NetworkDiscoveryMode::NetworkDiscoveryMode() {}

QDomElement
NetworkDiscoveryMode::toxml() {
    QDomElement setDiscoveryMode, discoveryMode;
    setDiscoveryMode = newElement("SetDiscoveryMode");
    setDiscoveryMode.setAttribute(
        "xmlns", "http://www.onvif.org/ver10/device/wsdl");
    discoveryMode = newElement("DiscoveryMode", this->discoveryMode());
    setDiscoveryMode.appendChild(discoveryMode);
    return setDiscoveryMode;
}
