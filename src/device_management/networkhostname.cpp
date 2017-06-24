#include "networkhostname.h"
#include "message.h"

using namespace ONVIF;
NetworkHostname::NetworkHostname()
{

}

QDomElement NetworkHostname::toxml()
{
    QDomElement setNetworkHostname,name;
    setNetworkHostname   = newElement("wsdl:SetHostname");
    name = newElement("Name", this->name());
    setNetworkHostname.appendChild(name);
    return setNetworkHostname;
}
