#include "networkntp.h"
#include "message.h"
using namespace ONVIF;
NetworkNTP::NetworkNTP() {}

QDomElement
NetworkNTP::toxml() {
    QDomElement setNTP, fromDhcp, ntpManual, type, ipv4Address;
    setNTP = newElement("SetNTP");
    setNTP.setAttribute("xmlns", "http://www.onvif.org/ver10/device/wsdl");
    fromDhcp = newElement("FromDHCP", this->dhcp() ? "true" : "false");
    setNTP.appendChild(fromDhcp);
    ntpManual   = newElement("NTPManual");
    type        = newElement("Type", this->manualType());
    ipv4Address = newElement("IPv4Address", this->ipv4Address());
    ntpManual.appendChild(type);
    ntpManual.appendChild(ipv4Address);
    setNTP.appendChild(ntpManual);
    return setNTP;
}
