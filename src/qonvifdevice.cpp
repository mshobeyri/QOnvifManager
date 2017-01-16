#include "qonvifdevice.hpp"
#include "devicemanagement.h"

QOnvifDevice::QOnvifDevice()
{
}

QOnvifDevice::QOnvifDevice(QString _userName, QString _password, QObject *_parent):
    QObject(_parent), iuserName(_userName), ipassword(_password)

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
