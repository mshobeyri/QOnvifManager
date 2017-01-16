#include "qonvifdevice.hpp"
#include "devicemanagement.h"

QOnvifDevice::QOnvifDevice()
{
    ideviceManagement =
            new ONVIF::DeviceManagement(ideviceProbeData.ideviceServiceAddress, iuserName, ipassword);//todo
}

QOnvifDevice::~QOnvifDevice()
{
    delete ideviceManagement;
}

QDateTime
QOnvifDevice::deviceDateAndTime()
{
    return idateAndTime;
}

bool
QOnvifDevice::setDeviceDateAndTime(QDateTime _dateAndTime)
{
    idateAndTime = _dateAndTime;
    //todo
    return true;
}

bool
QOnvifDevice::resetFactoryDevice()
{
    return true;
}

bool
QOnvifDevice::rebootDevice()
{
    return true;
}
