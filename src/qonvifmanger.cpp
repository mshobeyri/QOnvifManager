#include "qonvifmanger.hpp"
#include "devicesearcher.h"
#include "devicemanagement.h"
#include "systemdateandtime.h"


QOnvifManger::QOnvifManger(QString _userName, QString _password, QObject *_parent):
    QObject(_parent),iuserName(_userName), ipassword(_password)
{
    // device finding

    ideviceSearcher = ONVIF::DeviceSearcher::instance(ihostAddress);

    // when one device finded
    connect(ideviceSearcher,SIGNAL(receiveData(QHash<QString,QString>)),
            this,SLOT(onNewDeviceFinded(QHash<QString,QString>)),Qt::UniqueConnection);

    // when device searching ended
    connect(ideviceSearcher,&ONVIF::DeviceSearcher::deviceSearchingEnded,[this](){
        emit deviceSearchingEnded();
    });
}

bool
QOnvifManger::refreshDevicesList()
{
    idevicesMap.clear();
    ideviceSearcher->sendSearchMsg();
    return true;
}

QDateTime
QOnvifManger::deviceDateAndTime(QString _deviceEndPointAddress)
{
    return idevicesMap.value(_deviceEndPointAddress)->deviceDateAndTime();
}

QMap<QString, QOnvifDevice*> QOnvifManger::devicesMap()
{
    return idevicesMap;
}

bool
QOnvifManger::setDeviceDateAndTime(QString _deviceEndPointAddress, QDateTime _dateTime)
{
    return idevicesMap.value(_deviceEndPointAddress)->setDeviceDateAndTime(_dateTime);
}

bool
QOnvifManger::resetFactoryDevice(QString _deviceEndPointAddress)
{
    return idevicesMap.value(_deviceEndPointAddress)->resetFactoryDevice();
}

bool
QOnvifManger::rebootDevice(QString _deviceEndPointAddress)
{
    return idevicesMap.value(_deviceEndPointAddress)->rebootDevice();
}

void
QOnvifManger::onNewDeviceFinded(QHash<QString,QString> _deviceHash)
{
    QOnvifDevice *device = new QOnvifDevice(iuserName, ipassword,this);
    QOnvifDevice::DeviceProbeData probeData;

    probeData.iendPointAddress = _deviceHash.value("ep_address");
    probeData.itypes = _deviceHash.value("types");
    probeData.ideviceIp = _deviceHash.value("device_ip");
    probeData.ideviceServiceAddress = _deviceHash.value("device_service_address");
    probeData.iscopes = _deviceHash.value("scopes");
    probeData.imetadataVersion = _deviceHash.value("metadata_version");

    device->ideviceProbeData = probeData;
    idevicesMap.insert(probeData.iendPointAddress, device);
    emit newDeviceFinded(device);
}
