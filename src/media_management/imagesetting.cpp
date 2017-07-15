#include "imagesetting.h"

using namespace ONVIF;

ImageSetting::ImageSetting(QObject* parent) : QObject(parent) {}

QDomElement ImageSetting::toxml()
{
    QDomElement s;
    return s;
}
