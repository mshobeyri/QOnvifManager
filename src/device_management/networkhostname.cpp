#include "networkhostname.h"
#include "message.h"

using namespace ONVIF;
NetworkHostname::NetworkHostname() {}

QDomElement
NetworkHostname::toxml() {
    QDomElement setNetworkHostname, name;
    setNetworkHostname = newElement("SetHostname");
    setNetworkHostname.setAttribute(
        "xmlns", "http://www.onvif.org/ver10/device/wsdl");
    name = newElement("Name", this->name());
    setNetworkHostname.appendChild(name);
    return setNetworkHostname;
}
