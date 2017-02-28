#include "qonvifmanager.hpp"
#include "devicemanagement.h"
#include "devicesearcher.h"
#include "systemdateandtime.h"

class QOnvifManagerPrivate
{
public:
    QOnvifManagerPrivate() {}
    ~QOnvifManagerPrivate() {}

    QScopedPointer<QOnvifManagerPrivate> d_ptr;
    QString                              iuserName;
    QString                              ipassword;
    QMap<QString, QOnvifDevice*> idevicesMap;
    QHostAddress           ihostAddress;
    ONVIF::DeviceSearcher* ideviceSearcher;
};


QOnvifManager::QOnvifManager(QObject* _parent)
    : QObject(_parent), d_ptr(new QOnvifManagerPrivate) {
    Q_D(QOnvifManager);
    // device finding
    d->ideviceSearcher = ONVIF::DeviceSearcher::instance(d->ihostAddress);

    // when one device finded
    connect(
        d->ideviceSearcher,
        SIGNAL(receiveData(QHash<QString, QString>)),
        this,
        SLOT(onReciveData(QHash<QString, QString>)),
        Qt::UniqueConnection);

    // when device searching ended
    connect(
        d->ideviceSearcher,
        &ONVIF::DeviceSearcher::deviceSearchingEnded,
        [this]() { emit deviceSearchingEnded(); });
    refreshDevicesList();
}

QOnvifManager::~QOnvifManager() {}

bool
QOnvifManager::refreshDevicesList() {
    Q_D(QOnvifManager);
    qDeleteAll(d->idevicesMap);
    d->idevicesMap.clear();
    d->ideviceSearcher->sendSearchMsg();
    return true;
}

bool
QOnvifManager::refreshDeviceCapabilities(QString _deviceEndPointAddress) {
    return d_ptr->idevicesMap.value(_deviceEndPointAddress)
        ->refreshDeviceCapabilities();
}

bool
QOnvifManager::refreshDeviceInformations(QString _deviceEndPointAddress) {
    return d_ptr->idevicesMap.value(_deviceEndPointAddress)
        ->refreshDeviceInformation();
}

bool
QOnvifManager::refreshDeviceVideoConfigs(QString _deviceEndPointAddress) {
    return d_ptr->idevicesMap.value(_deviceEndPointAddress)
        ->refreshVideoConfigs();
}

Data::DateTime
QOnvifManager::deviceDateAndTime(QString _deviceEndPointAddress) {
    return d_ptr->idevicesMap.value(_deviceEndPointAddress)->data().dateTime;
}

QOnvifDevice*
QOnvifManager::device(QString _deviceEndPointAddress) {
    return d_ptr->idevicesMap.value(_deviceEndPointAddress);
}

QMap<QString, QOnvifDevice*>&
QOnvifManager::devicesMap() {
    return d_ptr->idevicesMap;
}

bool
QOnvifManager::setDeviceDateAndTime(
    QString _deviceEndPointAddress, QDateTime _dateTime) {
    return d_ptr->idevicesMap.value(_deviceEndPointAddress)
        ->setDeviceDateAndTime(_dateTime);
}

void
QOnvifManager::setDefaulUsernameAndPassword(
    QString _username, QString _password) {
    d_ptr->iuserName = _username;
    d_ptr->ipassword = _password;
}

bool
QOnvifManager::resetFactoryDevice(QString _deviceEndPointAddress) {
    return d_ptr->idevicesMap.value(_deviceEndPointAddress)
        ->resetFactoryDevice();
}

bool
QOnvifManager::rebootDevice(QString _deviceEndPointAddress) {
    return d_ptr->idevicesMap.value(_deviceEndPointAddress)->rebootDevice();
}

void
QOnvifManager::onReciveData(QHash<QString, QString> _deviceHash) {
    Q_D(QOnvifManager);

    Data::ProbeData probeData;
    probeData.endPointAddress = _deviceHash.value("ep_address");

    if (d->idevicesMap.contains(probeData.endPointAddress))
        return;

    probeData.types    = _deviceHash.value("types");
    probeData.deviceIp = _deviceHash.value("device_ip");
    probeData.deviceServiceAddress =
        _deviceHash.value("device_service_address");
    probeData.scopes          = _deviceHash.value("scopes");
    probeData.metadataVersion = _deviceHash.value("metadata_version");

    QOnvifDevice* device = new QOnvifDevice(
        probeData.deviceServiceAddress, d->iuserName, d->ipassword, this);
    device->setDeviceProbeData(probeData);
    d->idevicesMap.insert(probeData.endPointAddress, device);
    emit newDeviceFinded(device);
}
