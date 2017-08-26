#include "qonvifmanager.hpp"
#include "devicemanagement.h"
#include "devicesearcher.h"
#include "systemdateandtime.h"

using namespace device;

class QOnvifManagerPrivate
{
public:
    QOnvifManagerPrivate(const QString _username, const QString _password)
        : iuserName(_username), ipassword(_password) {}
    ~QOnvifManagerPrivate() {}

    QString                              iuserName;
    QString                              ipassword;
    QMap<QString, QOnvifDevice*> idevicesMap;
    QHostAddress           ihostAddress;
    ONVIF::DeviceSearcher* ideviceSearcher;
};

QOnvifManager::QOnvifManager(
    const QString _username, const QString _password, QObject* _parent)
    : QObject(_parent), d_ptr(new QOnvifManagerPrivate(_username, _password)) {
    Q_D(QOnvifManager);
    // device finding
    d->ideviceSearcher = ONVIF::DeviceSearcher::instance(d->ihostAddress);

    // when one device finded
    connect(
        d->ideviceSearcher,
        SIGNAL(receiveData(QHash<QString, QString>)),
        this,
        SLOT(onReceiveData(QHash<QString, QString>)),
        Qt::UniqueConnection);

    // when device searching ended
    connect(
        d->ideviceSearcher,
        &ONVIF::DeviceSearcher::deviceSearchingEnded,
        [this]() { emit deviceSearchingEnded(); });

    connect(this,&QOnvifManager::newDeviceFound,this,[this](device::QOnvifDevice* _device){

        connect(_device,&QOnvifDevice::informationReceived,this,[this,_device](Data::Information d){
            emit deviceInformationReceived(d, d_ptr->idevicesMap.key(_device));
        });
        connect(_device,&QOnvifDevice::scopesReceived,this,[this,_device](Data::Scopes d){
            emit deviceScopesReceived(d, d_ptr->idevicesMap.key(_device));
        });
        connect(_device,&QOnvifDevice::dateAndTimeReceived,this,[this,_device](Data::DateTime d){
            emit deviceDateAndTimeReceived(d, d_ptr->idevicesMap.key(_device));
        });
        connect(_device,&QOnvifDevice::usersReceived,this,[this,_device](Data::Users d){
            emit deviceUsersReceived(d, d_ptr->idevicesMap.key(_device));
        });
        connect(_device,&QOnvifDevice::capabilitiesReceived,this,[this,_device](Data::Capabilities d){
            emit deviceCapabilitiesReceived(d, d_ptr->idevicesMap.key(_device));
        });
        connect(_device,&QOnvifDevice::networkInterfacesReceived,this,[this,_device](Data::Network::Interfaces d){
            emit deviceNetworkInterfacesReceived(d, d_ptr->idevicesMap.key(_device));
        });
        connect(_device,&QOnvifDevice::networkProtocolsReceived,this,[this,_device](Data::Network::Protocols d){
            emit deviceNetworkProtocolsReceived(d, d_ptr->idevicesMap.key(_device));
        });
        connect(_device,&QOnvifDevice::networkDefaultGatewayReceived,this,[this,_device](Data::Network::DefaultGateway d){
            emit deviceNetworkDefaultGatewayReceived(d, d_ptr->idevicesMap.key(_device));
        });
        connect(_device,&QOnvifDevice::networkDiscoveryModeReceived,this,[this,_device](Data::Network::DiscoveryMode d){
            emit deviceNetworkDiscoveryModeReceived(d, d_ptr->idevicesMap.key(_device));
        });
        connect(_device,&QOnvifDevice::networkDNSReceived,this,[this,_device](Data::Network::DNS d){
            emit deviceNetworkDNSReceived(d, d_ptr->idevicesMap.key(_device));
        });
        connect(_device,&QOnvifDevice::networkHostnameReceived,this,[this,_device](Data::Network::Hostname d){
            emit deviceNetworkHostnameReceived(d, d_ptr->idevicesMap.key(_device));
        });
        connect(_device,&QOnvifDevice::networkNTPReceived,this,[this,_device](Data::Network::NTP d){
            emit deviceNetworkNTPReceived(d, d_ptr->idevicesMap.key(_device));
        });
        connect(_device,&QOnvifDevice::profilesReceived,this,[this,_device](Data::Profiles d){
            emit deviceProfilesReceived(d, d_ptr->idevicesMap.key(_device));
        });
        connect(_device,&QOnvifDevice::profile720pReceived,this,[this,_device](Data::Profiles d){
            emit deviceProfile720pReceived(d, d_ptr->idevicesMap.key(_device));
        });
        connect(_device,&QOnvifDevice::profileD1Received,this,[this,_device](Data::Profiles d){
            emit deviceProfileD1Received(d, d_ptr->idevicesMap.key(_device));
        });
        connect(_device,&QOnvifDevice::videoEncoderConfigurationsReceived,this,[this,_device](Data::MediaConfig::Video::EncoderConfigs d){
            emit deviceVideoEncoderConfigurationsReceived(d, d_ptr->idevicesMap.key(_device));
        });
        connect(_device,&QOnvifDevice::videoSourceConfigurationsReceived,this,[this,_device](Data::MediaConfig::Video::SourceConfig d){
            emit deviceVideoSourceConfigurationsReceived(d, d_ptr->idevicesMap.key(_device));
        });
        connect(_device,&QOnvifDevice::videoEncoderConfigurationOptionsReceived,this,[this,_device](Data::MediaConfig::Video::EncoderConfigs::Options d){
            emit deviceVideoEncoderConfigurationOptionsReceived(d, d_ptr->idevicesMap.key(_device));
        });
        connect(_device,&QOnvifDevice::streamUrisReceived,this,[this,_device](Data::MediaConfig::Video::StreamUri d){
            emit deviceStreamUrisReceived(d, d_ptr->idevicesMap.key(_device));
        });
        connect(_device,&QOnvifDevice::imageSettingReceived,this,[this,_device](Data::MediaConfig::ImageSetting d){
            emit deviceImageSettingReceived(d, d_ptr->idevicesMap.key(_device));
        });
        connect(_device,&QOnvifDevice::imageSettingOptionsReceived,this,[this,_device](Data::MediaConfig::ImageSetting::Options d){
            emit deviceImageSettingOptionsReceived(d, d_ptr->idevicesMap.key(_device));
        });
        connect(_device,&QOnvifDevice::ptzConfigurationReceived,this,[this,_device](Data::Ptz::Config d){
            emit devicePtzConfigurationReceived(d, d_ptr->idevicesMap.key(_device));
        });
        connect(_device,&QOnvifDevice::presetsReceived,this,[this,_device](){
            emit devicePresetsReceived(d_ptr->idevicesMap.key(_device));
        });
        connect(_device,&QOnvifDevice::setResultReceived,this,[this,_device](bool _result, MessageType _messageType){
            emit deviceSetResultReceived(_result, _messageType, d_ptr->idevicesMap.key(_device));
        });
    });

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

void
QOnvifManager::getDeviceCapabilities(QString _deviceEndPointAddress) {
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d_ptr->idevicesMap.value(_deviceEndPointAddress)->getCapabilities();
}

void
QOnvifManager::getDeviceInformation(QString _deviceEndPointAddress) {
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d_ptr->idevicesMap.value(_deviceEndPointAddress)->getInformation();
}

void
QOnvifManager::getDeviceScopes(QString _deviceEndPointAddress) {
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d_ptr->idevicesMap.value(_deviceEndPointAddress)->getScopes();
}

void
QOnvifManager::getDeviceVideoEncoderConfigurations(QString _deviceEndPointAddress) {
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d_ptr->idevicesMap.value(_deviceEndPointAddress)->getVideoEncoderConfigurations();
}

void
QOnvifManager::getDeviceVideoEncoderConfigurationOptions(
    QString _deviceEndPointAddress) {
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d_ptr->idevicesMap.value(_deviceEndPointAddress)
            ->getVideoEncoderConfigurationOptions();
}

void
QOnvifManager::getDeviceStreamUris(QString _deviceEndPointAddress) {
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d_ptr->idevicesMap.value(_deviceEndPointAddress)->getStreamUris();
}

void
QOnvifManager::getDeviceProfiles(QString _deviceEndPointAddress) {
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d_ptr->idevicesMap.value(_deviceEndPointAddress)->getProfiles();
}

void
QOnvifManager::getDeviceInterfaces(QString _deviceEndPointAddress) {
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d_ptr->idevicesMap.value(_deviceEndPointAddress)->getInterfaces();
}

void
QOnvifManager::getDeviceProtocols(QString _deviceEndPointAddress) {
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d_ptr->idevicesMap.value(_deviceEndPointAddress)->getProtocols();
}

void
QOnvifManager::getDeviceDefaultGateway(QString _deviceEndPointAddress) {
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d_ptr->idevicesMap.value(_deviceEndPointAddress)->getDefaultGateway();
}

void
QOnvifManager::getDeviceDiscoveryMode(QString _deviceEndPointAddress) {
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d_ptr->idevicesMap.value(_deviceEndPointAddress)->getDiscoveryMode();
}

void
QOnvifManager::getDeviceDNS(QString _deviceEndPointAddress) {
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d_ptr->idevicesMap.value(_deviceEndPointAddress)->getDNS();
}

void
QOnvifManager::getDeviceHostname(QString _deviceEndPointAddress) {
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d_ptr->idevicesMap.value(_deviceEndPointAddress)->getHostname();
}

void
QOnvifManager::getDeviceNTP(QString _deviceEndPointAddress) {
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d_ptr->idevicesMap.value(_deviceEndPointAddress)->getNTP();
}

void
QOnvifManager::getDeviceUsers(QString _deviceEndPointAddress) {
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d_ptr->idevicesMap.value(_deviceEndPointAddress)->getUsers();
}

void
QOnvifManager::getDeviceDateAndTime(QString _deviceEndPointAddress) {
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d_ptr->idevicesMap.value(_deviceEndPointAddress)->getDateAndTime();
}

void
QOnvifManager::getDevicePtzConfiguration(QString _deviceEndPointAddress) {
    d_ptr->idevicesMap.value(_deviceEndPointAddress)
        ->getPtzConfiguration();
}

void
QOnvifManager::getDeviceImageSetting(QString _deviceEndPointAddress) {
    d_ptr->idevicesMap.value(_deviceEndPointAddress)
        ->getImageSetting();
}

void
QOnvifManager::getDeviceImageSettingOptions(
    QString _deviceEndPointAddress) {
    d_ptr->idevicesMap.value(_deviceEndPointAddress)
        ->getImageSettingOptions();
}

void
QOnvifManager::setDeviceDateAndTime(
    QString   _deviceEndPointAddress,
    QDateTime _dateTime,
    QString   _zone,
    bool      _daylightSaving,
    bool      _isLocal) {
    d_ptr->idevicesMap.value(_deviceEndPointAddress)
        ->setDateAndTime(_dateTime, _zone, _daylightSaving, _isLocal);
}

void
QOnvifManager::setDeviceImageSetting(
    QString                          _deviceEndPointAddress,
    Data::MediaConfig::ImageSetting& _imageSetting) {
    d_ptr->idevicesMap.value(_deviceEndPointAddress)
        ->setImageSetting(_imageSetting);
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
QOnvifManager::cameraExist(const QString& endpoinAddress) {
    if (d_ptr->idevicesMap.contains(endpoinAddress))
        return true;
    return false;
}

void
QOnvifManager::setDefaulUsernameAndPassword(
    QString _username, QString _password) {
    d_ptr->iuserName = _username;
    d_ptr->ipassword = _password;
    refreshDevicesList();
}

void
QOnvifManager::setDeviceScopes(
    QString _deviceEndPointAddress, QString _name, QString _location) {
    d_ptr->idevicesMap.value(_deviceEndPointAddress)
        ->setScopes(_name, _location);
}

void
QOnvifManager::setDeviceVideoEncoderConfiguration(
    QString                                 _deviceEndPointAddress,
    Data::MediaConfig::Video::EncoderConfig _videoConfig) {
    d_ptr->idevicesMap.value(_deviceEndPointAddress)
        ->setVideoEncoderConfiguration(_videoConfig);
}

void
QOnvifManager::setDeviceUsers(
    QString _deviceEndPointAddress, Data::Users _users) {
    d_ptr->idevicesMap.value(_deviceEndPointAddress)->setUsers(_users);
}

void
QOnvifManager::setDeviceNetworkInterfaces(
    QString _deviceEndPointAddress, Data::Network::Interfaces _interfaces) {
    d_ptr->idevicesMap.value(_deviceEndPointAddress)
        ->setNetworkInterfaces(_interfaces);
}

void
QOnvifManager::setDeviceNetworkProtocols(
    QString _deviceEndPointAddress, Data::Network::Protocols _protocols) {
    d_ptr->idevicesMap.value(_deviceEndPointAddress)
        ->setNetworkProtocols(_protocols);
}

void
QOnvifManager::setDeviceNetworkDefaultGateway(
    QString                       _deviceEndPointAddress,
    Data::Network::DefaultGateway _defaultGateway) {
    d_ptr->idevicesMap.value(_deviceEndPointAddress)
        ->setNetworkDefaultGateway(_defaultGateway);
}

void
QOnvifManager::setDeviceNetworkDiscoveryMode(
    QString                      _deviceEndPointAddress,
    Data::Network::DiscoveryMode _discoveryMode) {
    d_ptr->idevicesMap.value(_deviceEndPointAddress)
        ->setNetworkDiscoveryMode(_discoveryMode);
}

void
QOnvifManager::setDeviceNetworkDNS(
    QString _deviceEndPointAddress, Data::Network::DNS _dns) {
    d_ptr->idevicesMap.value(_deviceEndPointAddress)->setNetworkDNS(_dns);
}

void
QOnvifManager::setDeviceNetworkHostname(
    QString _deviceEndPointAddress, Data::Network::Hostname _hostname) {
    d_ptr->idevicesMap.value(_deviceEndPointAddress)
        ->setNetworkHostname(_hostname);
}

void
QOnvifManager::setDeviceNetworkNTP(
    QString _deviceEndPointAddress, Data::Network::NTP _ntp) {
    d_ptr->idevicesMap.value(_deviceEndPointAddress)->setNetworkNTP(_ntp);
}

void
QOnvifManager::resetFactoryDevice(QString _deviceEndPointAddress, bool isHard) {
    d_ptr->idevicesMap.value(_deviceEndPointAddress)
        ->resetFactory(isHard);
}

void
QOnvifManager::rebootDevice(QString _deviceEndPointAddress) {
    d_ptr->idevicesMap.value(_deviceEndPointAddress)->reboot();
}

void
QOnvifManager::continuousMove(
    QString     _deviceEndPointAddress,
    const float _x,
    const float _y,
    const float _z) {
    d_ptr->idevicesMap.value(_deviceEndPointAddress)
        ->continuousMove(_x, _y, _z);
}

void QOnvifManager::stopMovement(QString _deviceEndPointAddress) {
    d_ptr->idevicesMap.value(_deviceEndPointAddress)->stopMovement();
}

void
QOnvifManager::onReceiveData(QHash<QString, QString> _deviceHash) {
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
    QOnvifDevice* device      = new QOnvifDevice(
        probeData.deviceServiceAddress, d->iuserName, d->ipassword, this);
    device->setProbeData(probeData);
    d->idevicesMap.insert(probeData.endPointAddress, device);
    emit newDeviceFound(device);
}
