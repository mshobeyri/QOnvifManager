#include "homeposition.h"
#include "message.h"

using namespace ONVIF;

ONVIF::HomePosition::HomePosition(QObject* parent) : QObject(parent) {}

ONVIF::HomePosition::~HomePosition() {}

QDomElement
HomePosition::toxml() {
    QDomElement setHomePosition = newElement("wsdl:SetHomePosition");
    QDomElement profileToken =
        newElement("wsdl:ProfileToken", this->profileToken());
    setHomePosition.appendChild(profileToken);
    return setHomePosition;
}
