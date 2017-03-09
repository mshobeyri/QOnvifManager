#include "systemscopes.h"
#include "message.h"

using namespace ONVIF;
QDomElement
SystemScopes::toxml() {
    QDomElement setScopes, name, location;
    setScopes = newElement("wsdl:SetScopes");
    setScopes.setAttribute("xmlns", "http://www.onvif.org/ver10/device/wsdl");
    name     = newElement("wsdl:Scopes", m_name);
    location = newElement("wsdl:Scopes", m_location);
    setScopes.appendChild(name);
    setScopes.appendChild(location);
    return setScopes;
}

void
SystemScopes::setScopes(QString name, QString location) {
    m_name     = name;
    m_location = location;
}

SystemScopes::SystemScopes() {}
