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

    QString iuserName;
    QString ipassword;
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

    // when one device found
    connect(
        d->ideviceSearcher,
        &ONVIF::DeviceSearcher::receiveData,
        this,
        &QOnvifManager::onReceiveData);

    // when device searching ended
    connect(
        d->ideviceSearcher,
        &ONVIF::DeviceSearcher::deviceSearchingEnded,
        [this]() { emit deviceSearchingEnded(); });

    connect(
        this,
        &QOnvifManager::newDeviceFound,
        this,
        [this, d](device::QOnvifDevice* _device) {

            connect(
                _device,
                &QOnvifDevice::informationReceived,
                this,
                [this, _device, d](Data::Information data) {
                    emit deviceInformationReceived(
                        data, d->idevicesMap.key(_device));
                });
            connect(
                _device,
                &QOnvifDevice::scopesReceived,
                this,
                [this, _device, d](Data::Scopes data) {
                    emit deviceScopesReceived(
                        data, d->idevicesMap.key(_device));
                });
            connect(
                _device,
                &QOnvifDevice::dateAndTimeReceived,
                this,
                [this, _device, d](Data::DateTime data) {
                    emit deviceDateAndTimeReceived(
                        data, d->idevicesMap.key(_device));
                });
            connect(
                _device,
                &QOnvifDevice::usersReceived,
                this,
                [this, _device, d](Data::Users data) {
                    emit deviceUsersReceived(data, d->idevicesMap.key(_device));
                });
            connect(
                _device,
                &QOnvifDevice::capabilitiesReceived,
                this,
                [this, _device, d](Data::Capabilities data) {
                    emit deviceCapabilitiesReceived(
                        data, d->idevicesMap.key(_device));
                });
            connect(
                _device,
                &QOnvifDevice::networkInterfacesReceived,
                this,
                [this, _device, d](Data::Network::Interfaces data) {
                    emit deviceNetworkInterfacesReceived(
                        data, d->idevicesMap.key(_device));
                });
            connect(
                _device,
                &QOnvifDevice::networkProtocolsReceived,
                this,
                [this, _device, d](Data::Network::Protocols data) {
                    emit deviceNetworkProtocolsReceived(
                        data, d->idevicesMap.key(_device));
                });
            connect(
                _device,
                &QOnvifDevice::networkDefaultGatewayReceived,
                this,
                [this, _device, d](Data::Network::DefaultGateway data) {
                    emit deviceNetworkDefaultGatewayReceived(
                        data, d->idevicesMap.key(_device));
                });
            connect(
                _device,
                &QOnvifDevice::networkDiscoveryModeReceived,
                this,
                [this, _device, d](Data::Network::DiscoveryMode data) {
                    emit deviceNetworkDiscoveryModeReceived(
                        data, d->idevicesMap.key(_device));
                });
            connect(
                _device,
                &QOnvifDevice::networkDNSReceived,
                this,
                [this, _device, d](Data::Network::DNS data) {
                    emit deviceNetworkDNSReceived(
                        data, d->idevicesMap.key(_device));
                });
            connect(
                _device,
                &QOnvifDevice::networkHostnameReceived,
                this,
                [this, _device, d](Data::Network::Hostname data) {
                    emit deviceNetworkHostnameReceived(
                        data, d->idevicesMap.key(_device));
                });
            connect(
                _device,
                &QOnvifDevice::networkNTPReceived,
                this,
                [this, _device, d](Data::Network::NTP data) {
                    emit deviceNetworkNTPReceived(
                        data, d->idevicesMap.key(_device));
                });
            connect(
                _device,
                &QOnvifDevice::profilesReceived,
                this,
                [this, _device, d](Data::Profiles data) {
                    emit deviceProfilesReceived(
                        data, d->idevicesMap.key(_device));
                });
            connect(
                _device,
                &QOnvifDevice::profile720pReceived,
                this,
                [this, _device, d](Data::Profiles data) {
                    emit deviceProfile720pReceived(
                        data, d->idevicesMap.key(_device));
                });
            connect(
                _device,
                &QOnvifDevice::profileD1Received,
                this,
                [this, _device, d](Data::Profiles data) {
                    emit deviceProfileD1Received(
                        data, d->idevicesMap.key(_device));
                });
            connect(
                _device,
                &QOnvifDevice::videoEncoderConfigurationsReceived,
                this,
                [this, _device, d](
                    Data::MediaConfig::Video::EncoderConfigs data) {
                    emit deviceVideoEncoderConfigurationsReceived(
                        data, d->idevicesMap.key(_device));
                });
            connect(
                _device,
                &QOnvifDevice::videoSourceConfigurationsReceived,
                this,
                [this, _device, d](
                    Data::MediaConfig::Video::SourceConfig data) {
                    emit deviceVideoSourceConfigurationsReceived(
                        data, d->idevicesMap.key(_device));
                });
            connect(
                _device,
                &QOnvifDevice::videoEncoderConfigurationOptionReceived,
                this,
                [this, _device, d](
                    Data::MediaConfig::Video::EncoderConfigs::Option data) {
                    emit deviceVideoEncoderConfigurationOptionReceived(
                        data, d->idevicesMap.key(_device));
                });
            connect(
                _device,
                &QOnvifDevice::streamUrisReceived,
                this,
                [this, _device, d](Data::MediaConfig::Video::StreamUri data) {
                    emit deviceStreamUrisReceived(
                        data, d->idevicesMap.key(_device));
                });
            connect(
                _device,
                &QOnvifDevice::imageSettingReceived,
                this,
                [this, _device, d](Data::MediaConfig::ImageSetting data) {
                    emit deviceImageSettingReceived(
                        data, d->idevicesMap.key(_device));
                });
            connect(
                _device,
                &QOnvifDevice::imageSettingOptionsReceived,
                this,
                [this, _device, d](
                    Data::MediaConfig::ImageSetting::Options data) {
                    emit deviceImageSettingOptionsReceived(
                        data, d->idevicesMap.key(_device));
                });
            connect(
                _device,
                &QOnvifDevice::ptzConfigurationReceived,
                this,
                [this, _device, d](Data::Ptz::Config data) {
                    emit devicePtzConfigurationReceived(
                        data, d->idevicesMap.key(_device));
                });
            connect(
                _device,
                &QOnvifDevice::presetsReceived,
                this,
                [this, _device, d]() {
                    emit devicePresetsReceived(d->idevicesMap.key(_device));
                });
            connect(
                _device,
                &QOnvifDevice::getResultReceived,
                this,
                [this, _device, d](Data _data, MessageType _messageType) {
                    emit deviceGetResultReceived(
                        _data, _messageType, d->idevicesMap.key(_device));
                });
            connect(
                _device,
                &QOnvifDevice::setResultReceived,
                this,
                [this, _device, d](bool _result, MessageType _messageType) {
                    emit deviceSetResultReceived(
                        _result, _messageType, d->idevicesMap.key(_device));
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
    Q_D(QOnvifManager);
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d->idevicesMap.value(_deviceEndPointAddress)->getCapabilities();
}

void
QOnvifManager::getDeviceInformation(QString _deviceEndPointAddress) {
    Q_D(QOnvifManager);
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d->idevicesMap.value(_deviceEndPointAddress)->getInformation();
}

void
QOnvifManager::getDeviceScopes(QString _deviceEndPointAddress) {
    Q_D(QOnvifManager);
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d->idevicesMap.value(_deviceEndPointAddress)->getScopes();
}

void
QOnvifManager::getDeviceVideoEncoderConfigurations(
    QString _deviceEndPointAddress) {
    Q_D(QOnvifManager);
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d->idevicesMap.value(_deviceEndPointAddress)
        ->getVideoEncoderConfigurations();
}

void
QOnvifManager::getDeviceVideoEncoderConfigurationOptions(
    QString _deviceEndPointAddress) {
    Q_D(QOnvifManager);
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d->idevicesMap.value(_deviceEndPointAddress)
        ->getVideoEncoderConfigurationOptions();
}

void
QOnvifManager::getDeviceStreamUris(QString _deviceEndPointAddress) {
    Q_D(QOnvifManager);
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d->idevicesMap.value(_deviceEndPointAddress)->getStreamUris();
}

void
QOnvifManager::getDeviceProfiles(QString _deviceEndPointAddress) {
    Q_D(QOnvifManager);
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d->idevicesMap.value(_deviceEndPointAddress)->getProfiles();
}

void
QOnvifManager::getDeviceNetworkInterfaces(QString _deviceEndPointAddress) {
    Q_D(QOnvifManager);
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d->idevicesMap.value(_deviceEndPointAddress)->getInterfaces();
}

void
QOnvifManager::getDeviceNetworkProtocols(QString _deviceEndPointAddress) {
    Q_D(QOnvifManager);
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d->idevicesMap.value(_deviceEndPointAddress)->getProtocols();
}

void
QOnvifManager::getDeviceNetworkDefaultGateway(QString _deviceEndPointAddress) {
    Q_D(QOnvifManager);
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d->idevicesMap.value(_deviceEndPointAddress)->getDefaultGateway();
}

void
QOnvifManager::getDeviceNetworkDiscoveryMode(QString _deviceEndPointAddress) {
    Q_D(QOnvifManager);
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d->idevicesMap.value(_deviceEndPointAddress)->getDiscoveryMode();
}

void
QOnvifManager::getDeviceNetworkDNS(QString _deviceEndPointAddress) {
    Q_D(QOnvifManager);
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d->idevicesMap.value(_deviceEndPointAddress)->getDNS();
}

void
QOnvifManager::getDeviceNetworkHostname(QString _deviceEndPointAddress) {
    Q_D(QOnvifManager);
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d->idevicesMap.value(_deviceEndPointAddress)->getHostname();
}

void
QOnvifManager::getDeviceNetworkNTP(QString _deviceEndPointAddress) {
    Q_D(QOnvifManager);
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d->idevicesMap.value(_deviceEndPointAddress)->getNTP();
}

void
QOnvifManager::getDeviceUsers(QString _deviceEndPointAddress) {
    Q_D(QOnvifManager);
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d->idevicesMap.value(_deviceEndPointAddress)->getUsers();
}

void
QOnvifManager::getDeviceDateAndTime(QString _deviceEndPointAddress) {
    Q_D(QOnvifManager);
    if (!cameraExist(_deviceEndPointAddress))
        return;
    d->idevicesMap.value(_deviceEndPointAddress)->getDateAndTime();
}

void
QOnvifManager::getDevicePtzConfiguration(QString _deviceEndPointAddress) {
    Q_D(QOnvifManager);
    d->idevicesMap.value(_deviceEndPointAddress)->getPtzConfiguration();
}

void
QOnvifManager::getDeviceImageSetting(QString _deviceEndPointAddress) {
    Q_D(QOnvifManager);
    d->idevicesMap.value(_deviceEndPointAddress)->getImageSetting();
}

void
QOnvifManager::getDeviceImageSettingOptions(QString _deviceEndPointAddress) {
    Q_D(QOnvifManager);
    d->idevicesMap.value(_deviceEndPointAddress)->getImageSettingOptions();
}

void
QOnvifManager::setDeviceDateAndTime(
    QString   _deviceEndPointAddress,
    QDateTime _dateTime,
    QString   _zone,
    bool      _daylightSaving,
    bool      _isLocal) {
    Q_D(QOnvifManager);
    d->idevicesMap.value(_deviceEndPointAddress)
        ->setDateAndTime(_dateTime, _zone, _daylightSaving, _isLocal);
}

void
QOnvifManager::setDeviceImageSetting(
    QString                          _deviceEndPointAddress,
    Data::MediaConfig::ImageSetting& _imageSetting) {
    Q_D(QOnvifManager);
    d->idevicesMap.value(_deviceEndPointAddress)
        ->setImageSetting(_imageSetting);
}

QOnvifDevice*
QOnvifManager::device(QString _deviceEndPointAddress) {
    Q_D(QOnvifManager);
    return d->idevicesMap.value(_deviceEndPointAddress);
}

QMap<QString, QOnvifDevice*>&
QOnvifManager::devicesMap() {
    Q_D(QOnvifManager);
    return d->idevicesMap;
}

bool
QOnvifManager::cameraExist(const QString& endpoinAddress) {
    Q_D(QOnvifManager);
    if (d->idevicesMap.contains(endpoinAddress))
        return true;
    return false;
}

void
QOnvifManager::setDefaulUsernameAndPassword(
    QString _username, QString _password) {
    Q_D(QOnvifManager);
    d->iuserName = _username;
    d->ipassword = _password;
    refreshDevicesList();
}

void
QOnvifManager::setDeviceScopes(
    QString _deviceEndPointAddress, QString _name, QString _location) {
    Q_D(QOnvifManager);
    d->idevicesMap.value(_deviceEndPointAddress)->setScopes(_name, _location);
}

void
QOnvifManager::setDeviceVideoEncoderConfiguration(
    QString                                 _deviceEndPointAddress,
    Data::MediaConfig::Video::EncoderConfig _videoConfig) {
    Q_D(QOnvifManager);
    d->idevicesMap.value(_deviceEndPointAddress)
        ->setVideoEncoderConfiguration(_videoConfig);
}

void
QOnvifManager::setDeviceUsers(
    QString _deviceEndPointAddress, Data::Users _users) {
    Q_D(QOnvifManager);
    d->idevicesMap.value(_deviceEndPointAddress)->setUsers(_users);
}

void
QOnvifManager::setDeviceNetworkInterfaces(
    QString _deviceEndPointAddress, Data::Network::Interfaces _interfaces) {
    Q_D(QOnvifManager);
    d->idevicesMap.value(_deviceEndPointAddress)
        ->setNetworkInterfaces(_interfaces);
}

void
QOnvifManager::setDeviceNetworkProtocols(
    QString _deviceEndPointAddress, Data::Network::Protocols _protocols) {
    Q_D(QOnvifManager);
    d->idevicesMap.value(_deviceEndPointAddress)
        ->setNetworkProtocols(_protocols);
}

void
QOnvifManager::setDeviceNetworkDefaultGateway(
    QString                       _deviceEndPointAddress,
    Data::Network::DefaultGateway _defaultGateway) {
    Q_D(QOnvifManager);
    d->idevicesMap.value(_deviceEndPointAddress)
        ->setNetworkDefaultGateway(_defaultGateway);
}

void
QOnvifManager::setDeviceNetworkDiscoveryMode(
    QString                      _deviceEndPointAddress,
    Data::Network::DiscoveryMode _discoveryMode) {
    Q_D(QOnvifManager);
    d->idevicesMap.value(_deviceEndPointAddress)
        ->setNetworkDiscoveryMode(_discoveryMode);
}

void
QOnvifManager::setDeviceNetworkDNS(
    QString _deviceEndPointAddress, Data::Network::DNS _dns) {
    Q_D(QOnvifManager);
    d->idevicesMap.value(_deviceEndPointAddress)->setNetworkDNS(_dns);
}

void
QOnvifManager::setDeviceNetworkHostname(
    QString _deviceEndPointAddress, Data::Network::Hostname _hostname) {
    Q_D(QOnvifManager);
    d->idevicesMap.value(_deviceEndPointAddress)->setNetworkHostname(_hostname);
}

void
QOnvifManager::setDeviceNetworkNTP(
    QString _deviceEndPointAddress, Data::Network::NTP _ntp) {
    Q_D(QOnvifManager);
    d->idevicesMap.value(_deviceEndPointAddress)->setNetworkNTP(_ntp);
}

void
QOnvifManager::resetFactoryDevice(QString _deviceEndPointAddress, bool isHard) {
    Q_D(QOnvifManager);
    d->idevicesMap.value(_deviceEndPointAddress)->resetFactory(isHard);
}

void
QOnvifManager::rebootDevice(QString _deviceEndPointAddress) {
    Q_D(QOnvifManager);
    d->idevicesMap.value(_deviceEndPointAddress)->reboot();
}

void
QOnvifManager::continuousMove(
    QString     _deviceEndPointAddress,
    const float _x,
    const float _y,
    const float _z) {
    Q_D(QOnvifManager);
    d->idevicesMap.value(_deviceEndPointAddress)->continuousMove(_x, _y, _z);
}

void
QOnvifManager::stopMovement(QString _deviceEndPointAddress) {
    Q_D(QOnvifManager);
    d->idevicesMap.value(_deviceEndPointAddress)->stopMovement();
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
