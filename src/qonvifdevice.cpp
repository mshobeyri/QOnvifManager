#include "qonvifdevice.hpp"
#include "devicemanagement.h"

QOnvifDevice::QOnvifDevice()
{
    ideviceManagement =
            new ONVIF::DeviceManagement(ideviceProbeData.ideviceServiceAddress, iuserName, ipassword);//todo
}

QDateTime QOnvifDevice::deviceDateAndTime()
{

}

bool QOnvifDevice::setDeviceDateAndTime(QDateTime _dateAndTime)
{
    idateAndTime = _dateAndTime;
}

bool QOnvifDevice::resetFactoryDevice()
{

}

bool QOnvifDevice::rebootDevice()
{

}
