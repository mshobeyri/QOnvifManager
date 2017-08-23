#ifndef QONVIFDEVICE_HPP
#define QONVIFDEVICE_HPP

#include "datastruct.hpp"

#include <QDateTime>
#include <QObject>
#include <QScopedPointer>

namespace ONVIF {
class DeviceManagement;
class MediaManagement;
}
///////////////////////////////////////////////////////////////////////////////
namespace device {


enum class MessageType{
    DeviceInformation,
    DeviceScopes,
    SystemDateAndTime,
    Users,
    Capabilities,
    NetworkInterfaces,
    NetworkProtocols,
    NetworkDefaultGateway,
    NetworkDiscoveryMode,
    NetworkDNS,
    NetworkHostname,
    NetworkNTP,

    SetDeviceScopes,
    SetSystemDateAndTime,
    SetUsers,
    SetSystemFactoryDefault,
    SetSystemReboot,
    SetNetworkInterfaces,
    SetNetworkProtocols,
    SetNetworkDefaultGateway,
    SetNetworkDiscoveryMode,
    SetNetworkDNS,
    SetNetworkHostname,
    SetNetworkNTP,

    VideoSourceConfigurations,
    VideoEncoderConfigurations,
    Profiles,
    Profile720p,
    ProfileD1,
    AudioSourceConfigurations,
    AudioEncoderConfigurations,
    VideoSourceConfiguration,
    VideoEncoderConfiguration,
    AudioEncoderConfiguration,
    AudioEncoderConfigurationOptions,
    VideoEncoderConfigurationOptions,
    StreamUri,
    ImageSetting,
    ImageSettingOptions,

    setVideoEncoderConfiguration,
    setImageSettings
};



///////////////////////////////////////////////////////////////////////////////
class QOnvifDevicePrivate;
class QOnvifDevice : public QObject
{
public:
    QOnvifDevice(
        QString  _serviceAddress,
        QString  _userName,
        QString  _password,
        QObject* _parent);

    ~QOnvifDevice();

    Data& data();

    // device management
    void getDeviceInformation();
    void getDeviceScopes();
    void getDeviceDateAndTime();
    void getUsers();
    void getDeviceCapabilities();
    void getInterfaces();
    void getProtocols();
    void getDefaultGateway();
    void getDiscoveryMode();
    void getDNS();
    void getHostname();
    void getNTP();

    void setDeviceProbeData(Data::ProbeData _probeData);

    void setScopes(QString _name, QString _location);
    void setDateAndTime(
            QDateTime _dateAndTime,
            QString   _zone,
            bool      _daylightSaving,
            bool      _isLocal);
    void setUsers(Data::Users _users);
    void setNetworkInterfaces(Data::Network::Interfaces _interfaces);
    void setNetworkProtocols(Data::Network::Protocols _protocols);
    void setNetworkDefaultGateway(Data::Network::DefaultGateway _defaultGateway);
    void setNetworkDiscoveryMode(Data::Network::DiscoveryMode _discoveryMode);
    void setNetworkDNS(Data::Network::DNS _dns);
    void setNetworkHostname(Data::Network::Hostname _hostname);
    void setNetworkNTP(Data::Network::NTP _ntp);

    void resetFactoryDevice(bool isHard);
    void rebootDevice();

    // media management
    void getProfiles();
    void getProfile720p();
    void getProfileD1();
    void getVideoEncoderConfigurations();
    void getVideoSourceConfigurations();
    void getVideoEncoderConfigurationOptions();
    void getStreamUris();
    void getImageSetting();
    void getImageSettingOptions();

    void setVideoEncoderConfiguration(Data::MediaConfig::Video::EncoderConfig _videoConfig);
    void setDeviceImageSetting(Data::MediaConfig::ImageSetting  _imageSetting);

    // ptz management
    bool refreshPtzConfiguration();
    bool refreshPresets();
    bool goHomePosition();
    bool setHomePosition();
    bool continuousMove(const float x, const float y, const float z);
    bool stopMovement();

signals:

    void deviceInformationReceived(Data::Information);
    void deviceScopesReceived(Data::Scopes);
    void systemDateAndTimeReceived(Data::DateTime);
    void usersReceived(Data::Users);
    void capabilitiesReceived(Data::Capabilities);
    void networkInterfacesReceived(Data::Network::Interfaces);
    void networkProtocolsReceived(Data::Network::Protocols);
    void networkDefaultGatewayReceived(Data::Network::DefaultGateway);
    void networkDiscoveryModeReceived(Data::Network::DiscoveryMode);
    void networkDNSReceived(Data::Network::DNS);
    void networkHostnameReceived(Data::Network::Hostname);
    void networkNTPReceived(Data::Network::NTP);

    void profilesReceived(Data::Profiles);
    void profile720pReceived(Data::Profiles);
    void profileD1Received(Data::Profiles);
    void videoEncoderConfigurationsReceived(Data::MediaConfig::Video::EncoderConfigs);
    void videoSourceConfigurationsReceived(Data::MediaConfig::Video::SourceConfig);
    void videoEncoderConfigurationOptionsReceived(Data::MediaConfig::Video::EncoderConfigs::Options);
    void streamUrisReceived(Data::MediaConfig::Video::StreamUri);
    void imageSettingReceived(Data::MediaConfig::ImageSetting);
    void imageSettingOptionsReceived(Data::MediaConfig::ImageSetting::Options);

    void setResultReceived(bool, MessageType);
private:
    Q_DECLARE_PRIVATE(QOnvifDevice)
    QScopedPointer<QOnvifDevicePrivate> d_ptr;
};
///////////////////////////////////////////////////////////////////////////////
} // namespace device
///////////////////////////////////////////////////////////////////////////////

#endif // QONVIFDEVICE_HPP
