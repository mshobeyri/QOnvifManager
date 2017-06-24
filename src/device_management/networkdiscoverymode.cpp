#include "networkdiscoverymode.h"
#include "message.h"
using namespace ONVIF;
NetworkDiscoveryMode::NetworkDiscoveryMode() {}

QDomElement
NetworkDiscoveryMode::toxml() {
    QDomElement setDiscoveryMode, discoveryMode;
    setDiscoveryMode = newElement("SetDiscoveryMode");
    discoveryMode    = newElement("DiscoveryMode");
    setDiscoveryMode.appendChild(discoveryMode);
    return setDiscoveryMode;
}
