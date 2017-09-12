#include "capabilities.h"

using namespace ONVIF;

Capabilities::Capabilities(QObject* parent) : QObject(parent) {}
Capabilities::~Capabilities() {}
QDomElement
Capabilities::toxml() {
    QDomElement fake;
    return fake;
}
QString
Capabilities::enumToString(Category category) {
    switch (category) {
    case Capabilities::All:
        return "All";
    case Capabilities::Analytics:
        return "Analytics";
    case Capabilities::Device:
        return "Device";
    case Capabilities::Events:
        return "Events";
    case Capabilities::Imaging:
        return "Imaging";
    case Capabilities::Media:
        return "Media";
    case Capabilities::PTZ:
        return "PTZ";
    }
    return "";
}
