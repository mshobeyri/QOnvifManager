#include "networkdns.h"
#include "message.h"
using namespace ONVIF;
NetworkDNS::NetworkDNS() {}

QDomElement
NetworkDNS::toxml() {
    QDomElement setDNS, fromDhcp;
    setDNS = newElement("SetDNS");
    setDNS.setAttribute("xmlns", "http://www.onvif.org/ver10/device/wsdl");
    fromDhcp = newElement("FromDHCP", this->dhcp() ? "true" : "false");
    setDNS.appendChild(fromDhcp);
    auto minimumLength =
        qMin(this->manualType().length(), this->ipv4Address().length());
    for (int i = 0; i < minimumLength; i++) {
        QDomElement dnsManual = newElement("DNSManual");
        QDomElement type      = newElement("Type", this->manualType()[i]);
        type.setAttribute("xmlns", "http://www.onvif.org/ver10/schema");
        QDomElement ipv4Address =
            newElement("IPv4Address", this->ipv4Address()[i]);
        ipv4Address.setAttribute("xmlns", "http://www.onvif.org/ver10/schema");
        dnsManual.appendChild(type);
        dnsManual.appendChild(ipv4Address);
        setDNS.appendChild(dnsManual);
    }
    return setDNS;
}
