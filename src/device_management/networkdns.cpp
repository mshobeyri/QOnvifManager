#include "networkdns.h"
#include "message.h"
using namespace ONVIF;
NetworkDNS::NetworkDNS() {}

QDomElement
NetworkDNS::toxml() {
    QDomElement setDNS, fromDhcp;
    setDNS   = newElement("wsdl:SetDNS");
    fromDhcp = newElement("FromDHCP", this->dhcp() ? "true" : "false");
    setDNS.appendChild(fromDhcp);
    for(int i = 0;i < this->manualType().length();i++){
        QDomElement dnsManual = newElement("DNSManual");
        QDomElement type = newElement("Type",this->manualType()[i]);
        QDomElement ipv4Address = newElement("IPv4Address", this->ipv4Address()[i]);
        dnsManual.appendChild(type);
        dnsManual.appendChild(ipv4Address);
        setDNS.appendChild(dnsManual);
    }
    return setDNS;
}
