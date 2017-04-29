#include "videoencoderconfiguration.h"

#include "message.h"
using namespace ONVIF;

VideoEncoderConfiguration::VideoEncoderConfiguration(QObject* parent)
    : QObject(parent) {}
VideoEncoderConfiguration::~VideoEncoderConfiguration() {}
QDomElement
VideoEncoderConfiguration::toxml() {
    QDomElement setVideoConfiguration, configuration, width, height, name,
        token, useCount, encoding, resolution, quality, rateControl,
        frameRateLimit, encodingInterval, bitrateLimit, h264, h264profile,
        govLength, multicast, address, type, ipv4Address, port, ttl, autoStart,
        sessionTimeout, forcePresistence;
    setVideoConfiguration = newElement("wsdl:SetVideoEncoderConfiguration");
    configuration         = newElement("trt:Configuration");
    name                  = newElement("tt:Name", this->name());
    useCount    = newElement("tt:UseCount", QString::number(this->useCount()));
    encoding    = newElement("tt:Encoding", this->encoding());
    resolution  = newElement("tt:Resolution");
    width       = newElement("tt:Width", QString::number(this->width()));
    height      = newElement("tt:Height", QString::number(this->height()));
    quality     = newElement("tt:Quality", QString::number(this->quality()));
    rateControl = newElement("tt:RateControl");
    frameRateLimit = newElement(
        "tt:FrameRateLimit", QString::number(this->frameRateLimit()));
    encodingInterval = newElement(
        "tt:EncodingInterval", QString::number(this->encodingInterval()));
    bitrateLimit =
        newElement("tt:BitrateLimit", QString::number(this->bitrateLimit()));
    h264      = newElement("tt:H264");
    govLength = newElement("tt:GovLength", QString::number(this->govLength()));
    h264profile = newElement("tt:H264Profile", this->h264Profile());
    multicast   = newElement("tt:Multicast");
    address     = newElement("tt:Address");
    type        = newElement("tt:Type", this->type());
    ipv4Address = newElement("tt:IPv4Address", this->ipv4Address());
    port        = newElement("tt:Port", QString::number(this->port()));
    ttl         = newElement("tt:TTL", QString::number(this->ttl()));
    autoStart   = newElement(
        "tt:AutoStart", this->autoStart() == true ? "true" : "false");
    sessionTimeout   = newElement("tt:SessionTimeout", this->sessionTimeout());
    forcePresistence = newElement("tt:ForcePersistence", "true");

    setVideoConfiguration.setAttribute(
        "xmlns", "http://www.onvif.org/ver10/media/wsdl");
    configuration.setAttribute("token", this->token());
    name.setAttribute("xmlns", "http://www.onvif.org/ver10/schema");
    useCount.setAttribute("xmlns", "http://www.onvif.org/ver10/schema");
    encoding.setAttribute("xmlns", "http://www.onvif.org/ver10/schema");
    resolution.setAttribute("xmlns", "http://www.onvif.org/ver10/schema");
    quality.setAttribute("xmlns", "http://www.onvif.org/ver10/schema");
    rateControl.setAttribute("xmlns", "http://www.onvif.org/ver10/schema");
    h264.setAttribute("xmlns", "http://www.onvif.org/ver10/schema");
    multicast.setAttribute("xmlns", "http://www.onvif.org/ver10/schema");
    sessionTimeout.setAttribute("xmlns", "http://www.onvif.org/ver10/schema");

    resolution.appendChild(width);
    resolution.appendChild(height);
    rateControl.appendChild(frameRateLimit);
    rateControl.appendChild(encodingInterval);
    rateControl.appendChild(bitrateLimit);
    h264.appendChild(govLength);
    h264.appendChild(h264profile);
    address.appendChild(type);
//    address.appendChild(ipv4Address);
    multicast.appendChild(address);
    multicast.appendChild(port);
    multicast.appendChild(ttl);
    multicast.appendChild(autoStart);

    configuration.appendChild(name);
    configuration.appendChild(useCount);
    configuration.appendChild(encoding);
    configuration.appendChild(resolution);
    configuration.appendChild(quality);
    configuration.appendChild(rateControl);
    configuration.appendChild(h264);
    configuration.appendChild(multicast);
    configuration.appendChild(sessionTimeout);

    setVideoConfiguration.appendChild(configuration);
    setVideoConfiguration.appendChild(forcePresistence);
    return setVideoConfiguration;
}
