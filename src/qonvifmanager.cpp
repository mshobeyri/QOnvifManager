#include "qonvifmanager.hpp"
#include "devicesearcher.h"
#include "devicemanagement.h"
#include "systemdateandtime.h"


QOnvifManager::QOnvifManager(QString _userName, QString _password, QObject *_parent):
    QObject(_parent),iuserName(_userName), ipassword(_password)
{
    // device finding
    ideviceSearcher = ONVIF::DeviceSearcher::instance(ihostAddress);

    // when one device finded
    connect(ideviceSearcher,SIGNAL(receiveData(QHash<QString,QString>)),
            this,SLOT(onReciveData(QHash<QString,QString>)),Qt::UniqueConnection);

    // when device searching ended
    connect(ideviceSearcher,&ONVIF::DeviceSearcher::deviceSearchingEnded,[this]()
    {
        emit deviceSearchingEnded();
    });
}

bool
QOnvifManager::refreshDevicesList()
{
    qDeleteAll(idevicesMap);
    idevicesMap.clear();
    ideviceSearcher->sendSearchMsg();
    return true;
}

bool
QOnvifManager::refreshDeviceCapabilities(QString _deviceEndPointAddress)
{
    return idevicesMap.value(_deviceEndPointAddress)->refreshDeviceCapabilities();
}

bool
QOnvifManager::refreshDeviceInformations(QString _deviceEndPointAddress)
{
    return idevicesMap.value(_deviceEndPointAddress)->refreshDeviceInformation();
}

bool
QOnvifManager::refreshDeviceVideoConfigs(QString _deviceEndPointAddress)
{
    return idevicesMap.value(_deviceEndPointAddress)->refreshVideoConfigs();
}

QOnvifDevice::DateTime
QOnvifManager::deviceDateAndTime(QString _deviceEndPointAddress)
{
    return idevicesMap.value(_deviceEndPointAddress)->deviceDateAndTime();
}

QOnvifDevice*
QOnvifManager::device(QString _deviceEndPointAddress)
{
    return idevicesMap.value(_deviceEndPointAddress);
}

QMap<QString, QOnvifDevice*>
QOnvifManager::devicesMap()
{
    return idevicesMap;
}

bool
QOnvifManager::setDeviceDateAndTime(QString _deviceEndPointAddress, QDateTime _dateTime)
{
    return idevicesMap.value(_deviceEndPointAddress)->setDeviceDateAndTime(_dateTime);
}

void
QOnvifManager::setDefaulUsernameAndPassword(QString _username, QString _password)
{
    iuserName = _username;
    ipassword = _password;
}

bool
QOnvifManager::resetFactoryDevice(QString _deviceEndPointAddress)
{
    return idevicesMap.value(_deviceEndPointAddress)->resetFactoryDevice();
}

bool
QOnvifManager::rebootDevice(QString _deviceEndPointAddress)
{
    return idevicesMap.value(_deviceEndPointAddress)->rebootDevice();
}

void
QOnvifManager::onReciveData(QHash<QString,QString> _deviceHash)
{
    QOnvifDevice::DeviceProbeData probeData;

    probeData.iendPointAddress = _deviceHash.value("ep_address");

    if(idevicesMap.contains(probeData.iendPointAddress))
        return;

    probeData.itypes = _deviceHash.value("types");
    probeData.ideviceIp = _deviceHash.value("device_ip");
    probeData.ideviceServiceAddress = _deviceHash.value("device_service_address");
    probeData.iscopes = _deviceHash.value("scopes");
    probeData.imetadataVersion = _deviceHash.value("metadata_version");

    QOnvifDevice *device = new QOnvifDevice(probeData.ideviceServiceAddress, iuserName, ipassword,this);
    device->setDeviceProbeData(probeData);
    idevicesMap.insert(probeData.iendPointAddress, device);
    emit newDeviceFinded(device);
}
