#include "networkinterfaces.h"
#include "message.h"

using namespace ONVIF;

NetworkInterfaces::NetworkInterfaces(QObject* parent) : QObject(parent) {}
NetworkInterfaces::~NetworkInterfaces() {}

QDomElement
NetworkInterfaces::toxml() {
    QDomElement setNetworkInterfaces, interfaceToken, networkInterface,
        networkInterfaceEnabled, link, autoNegotiation, speed, duplex, mtu,
        ipv4, ipv4Enabled, manual, address, prefixLength, dhcp;
    setNetworkInterfaces = newElement("SetNetworkInterfaces");
    setNetworkInterfaces.setAttribute(
        "xmlns", "http://www.onvif.org/ver10/device/wsdl");
    interfaceToken   = newElement("InterfaceToken", this->interfaceToken());
    networkInterface = newElement("NetworkInterface");
    networkInterfaceEnabled = newElement(
        "Enabled", this->networkInfacesEnabled() == true ? "true" : "false");
    networkInterfaceEnabled.setAttribute(
        "xmlns", "http://www.onvif.org/ver10/schema");
    link            = newElement("Link");
    autoNegotiation = newElement(
        "AutoNegotiation", this->autoNegotiation() == true ? "true" : "false");
    speed  = newElement("Speed", QString::number(this->speed()));
    duplex = newElement(
        "Duplex", this->duplex() == NetworkInterfaces::Full ? "Full" : "Half");

    mtu = newElement("MTU", QString::number(this->mtu()));
    mtu.setAttribute("xmlns", "http://www.onvif.org/ver10/schema");
    ipv4 = newElement("IPv4");
    ipv4.setAttribute("xmlns", "http://www.onvif.org/ver10/schema");

    ipv4Enabled =
        newElement("Enabled", this->ipv4Enabled() == true ? "true" : "false");
    manual       = newElement("Manual");
    address      = newElement("Address", this->ipv4ManualAddress());
    prefixLength = newElement(
        "PrefixLength", QString::number(this->ipv4ManualPrefixLength()));
    dhcp = newElement("DHCP", this->ipv4DHCP() == true ? "true" : "false");
    setNetworkInterfaces.appendChild(interfaceToken);
    setNetworkInterfaces.appendChild(networkInterface);
    networkInterface.appendChild(networkInterfaceEnabled);
    // not nessecary for now(we do not set link values)
    //    networkInterface.appendChild(link);
    networkInterface.appendChild(mtu);
    networkInterface.appendChild(ipv4);
    link.appendChild(autoNegotiation);
    link.appendChild(speed);
    link.appendChild(duplex);
    ipv4.appendChild(ipv4Enabled);
    ipv4.appendChild(manual);
    ipv4.appendChild(dhcp);
    manual.appendChild(address);
    manual.appendChild(prefixLength);
    return setNetworkInterfaces;
}
