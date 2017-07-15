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
    // date time
    bool deviceDateAndTime(Data::DateTime& _datetime);
    // device management
    void setDeviceProbeData(Data::ProbeData _probeData);

    bool setDateAndTime(
        QDateTime _dateAndTime,
        QString   _zone,
        bool      _daylightSaving,
        bool      _isLocal);
    bool setScopes(QString _name, QString _location);
    bool setVideoConfig(Data::MediaConfig::Video::EncoderConfig _videoConfig);
    bool setUsers(Data::Users _users);
    bool setInterfaces(Data::Network::Interfaces _interfaces);
    bool setProtocols(Data::Network::Protocols _protocols);
    bool setDefaultGateway(Data::Network::DefaultGateway _defaultGateway);
    bool setDiscoveryMode(Data::Network::DiscoveryMode _discoveryMode);
    bool setDNS(Data::Network::DNS _dns);
    bool setHostname(Data::Network::Hostname _hostname);
    bool setNTP(Data::Network::NTP _ntp);

    bool refreshDeviceCapabilities();
    bool refreshDeviceInformation();
    bool refreshDeviceScopes();
    bool refreshInterfaces();
    bool refreshProtocols();
    bool refreshDefaultGateway();
    bool refreshDiscoveryMode();
    bool refreshDNS();
    bool refreshHostname();
    bool refreshNTP();
    bool refreshProfiles();
    bool refreshUsers();

    bool resetFactoryDevice(bool isHard);
    bool rebootDevice();

    // media management
    bool refreshVideoConfigs();
    bool refreshVideoConfigsOptions();
    bool refreshStreamUris();
    bool refreshAudioConfigs();

    // ptz management
    bool refreshPtzConfiguration();
    bool refreshPresets();
    bool goHomePosition();
    bool setHomePosition();
    bool continuousMove(const float x, const float y, const float z);
    bool stopMovement();

    bool refreshImageSetting();
    bool refreshImageSettingOptions();
private:
    Q_DECLARE_PRIVATE(QOnvifDevice)
    QScopedPointer<QOnvifDevicePrivate> d_ptr;
};
///////////////////////////////////////////////////////////////////////////////
} // namespace device
///////////////////////////////////////////////////////////////////////////////

#endif // QONVIFDEVICE_HPP
