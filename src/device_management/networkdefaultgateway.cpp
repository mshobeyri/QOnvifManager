#include "networkdefaultgateway.h"
#include "message.h"

using namespace ONVIF;
NetworkDefaultGateway::NetworkDefaultGateway()
{

}

QDomElement NetworkDefaultGateway::toxml()
{
    QDomElement setNetworkDefaltGateway,ipv4Address;
    setNetworkDefaltGateway = newElement("wsdl:SetNetworkDefaultGateway");
    ipv4Address = newElement("sch:IPv4Address",this->ipv4Address());
    setNetworkDefaltGateway.appendChild(ipv4Address);
    return setNetworkDefaltGateway;
}







