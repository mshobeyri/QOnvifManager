#include "qonvifmanger.hpp"
#include "devicesearcher.h"
#include "devicemanagement.h"
#include "systemdateandtime.h"

QOnvifManger::QOnvifManger(QString _userName, QString _password):
    iuserName(_userName), ipassword(_password)
{
}

bool
QOnvifManger::refreshDevicesList()
{
    idevicesMap.clear();
    ideviceSearcher = ONVIF::DeviceSearcher::instance(ihostAddress);
    connect(ideviceSearcher,SIGNAL(receiveData(QHash<QString,QString>)),
            this,SLOT(onDeviceFinded(QHash<QString,QString>)),Qt::UniqueConnection);
    ideviceSearcher->sendSearchMsg();
    return true;
}

QDateTime
QOnvifManger::deviceDateAndTime(QString _deviceEndPointAddress)
{
    return idevicesMap[_deviceEndPointAddress].deviceDateAndTime();
}

bool
QOnvifManger::setDeviceDateAndTime(QString _deviceEndPointAddress, QDateTime _dateTime)
{
    return idevicesMap[_deviceEndPointAddress].setDeviceDateAndTime(_dateTime);
}

bool
QOnvifManger::resetFactoryDevice(QString _deviceEndPointAddress)
{
    return idevicesMap[_deviceEndPointAddress].resetFactoryDevice();
}

bool
QOnvifManger::rebootDevice(QString _deviceEndPointAddress)
{
    return idevicesMap[_deviceEndPointAddress].rebootDevice();
}

void
QOnvifManger::onDeviceFinded(QHash<QString,QString> _deviceHash)
{
    QOnvifDevice device;
    QOnvifDevice::DeviceProbeData probeData;

    probeData.iendPointAddress = _deviceHash.value("ep_Address");
    probeData.itypes = _deviceHash.value("types");
    probeData.ideviceIp = _deviceHash.value("device_ip");
    probeData.ideviceServiceAddress = _deviceHash.value("device_service_address");
    probeData.iscopes = _deviceHash.value("scopes");
    probeData.imetadataVersion = _deviceHash.value("metadata_version");

    device.ideviceProbeData = probeData;
    idevicesMap.insert(probeData.iendPointAddress, device);
}
