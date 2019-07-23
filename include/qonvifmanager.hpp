#ifndef QONVIFMANAGER_HPP
#define QONVIFMANAGER_HPP

#include "qonvifdevice.hpp"
#include <QDateTime>
#include <QHostAddress>
#include <QMap>
#include <QScopedPointer>

//#ifndef QONVIFMANAGER_GLOBAL_HPP
//#define QONVIFMANAGER_GLOBAL_HPP

//#include <QtCore/qglobal.h>

//#if defined(QONVIFMANAGER_LIBRARY)
//#define QONVIFMANAGERSHARED_EXPORT Q_DECL_EXPORT
//#else
//#define QONVIFMANAGERSHARED_EXPORT Q_DECL_IMPORT
//#endif

//#endif


namespace ONVIF {
class DeviceSearcher;
}

// using namespace device;
class QOnvifManagerPrivate;

class /*QONVIFMANAGERSHARED_EXPORT*/ QOnvifManager : public QObject
{
    Q_OBJECT
public:
    QOnvifManager(
        const QString _username, const QString _password, QObject* _parent = 0);
    ~QOnvifManager();

    bool refreshDevicesList();

    void getDeviceCapabilities(QString _deviceEndPointAddress);
    void getDeviceInformation(QString _deviceEndPointAddress);
    void getDeviceScopes(QString _deviceEndPointAddress);
    void getDeviceVideoEncoderConfigurations(QString _deviceEndPointAddress);
    void
    getDeviceVideoEncoderConfigurationOptions(QString _deviceEndPointAddress);
    void getDeviceStreamUris(QString _deviceEndPointAddress);
    void getDeviceProfiles(QString _deviceEndPointAddress);
    void getDeviceNetworkInterfaces(QString _deviceEndPointAddress);
    void getDeviceNetworkProtocols(QString _deviceEndPointAddress);
    void getDeviceNetworkDefaultGateway(QString _deviceEndPointAddress);
    void getDeviceNetworkDiscoveryMode(QString _deviceEndPointAddress);
    void getDeviceNetworkDNS(QString _deviceEndPointAddress);
    void getDeviceNetworkHostname(QString _deviceEndPointAddress);
    void getDeviceNetworkNTP(QString _deviceEndPointAddress);
    void getDeviceUsers(QString _deviceEndPointAddress);
    void getDeviceDateAndTime(QString _deviceEndPointAddress);
    void getDevicePtzConfiguration(QString _deviceEndPointAddress);
    void getDeviceImageSetting(QString _deviceEndPointAddress);
    void getDeviceImageSettingOptions(QString _deviceEndPointAddress);


    void setDeviceDateAndTime(
        QString   _deviceEndPointAddress,
        QDateTime _dateTime,
        QString   _zone,
        bool      _daylightSaving,
        bool      _isLocal);
    void setDeviceImageSetting(
        QString                          _deviceEndPointAddress,
        Data::MediaConfig::ImageSetting& _imageSetting);

    void setDefaulUsernameAndPassword(QString _username, QString _password);
    void setDeviceScopes(
        QString _deviceEndPointAddress, QString _name, QString _location);
    void setDeviceVideoEncoderConfiguration(
        QString                                 _deviceEndPointAddress,
        Data::MediaConfig::Video::EncoderConfig _videoConfig);

    void setDeviceUsers(QString _deviceEndPointAddress, Data::Users _users);

    void setDeviceNetworkInterfaces(
        QString _deviceEndPointAddress, Data::Network::Interfaces _interfaces);

    void setDeviceNetworkProtocols(
        QString _deviceEndPointAddress, Data::Network::Protocols _protocols);

    void setDeviceNetworkDefaultGateway(
        QString                       _deviceEndPointAddress,
        Data::Network::DefaultGateway _defaultGateway);

    void setDeviceNetworkDiscoveryMode(
        QString                      _deviceEndPointAddress,
        Data::Network::DiscoveryMode _discoveryMode);

    void setDeviceNetworkDNS(
        QString _deviceEndPointAddress, Data::Network::DNS _dns);

    void setDeviceNetworkHostname(
        QString _deviceEndPointAddress, Data::Network::Hostname _hostname);

    void setDeviceNetworkNTP(
        QString _deviceEndPointAddress, Data::Network::NTP _ntp);

    void resetFactoryDevice(QString _deviceEndPointAddress, bool isHard);
    void rebootDevice(QString _deviceEndPointAddress);

    // ptz

    void continuousMove(
        QString     _deviceEndPointAddress,
        const float _x,
        const float _y,
        const float _z);

    void stopMovement(QString _deviceEndPointAddress);

    // public
    device::QOnvifDevice* device(QString _deviceEndPointAddress);
    QMap<QString, device::QOnvifDevice*>& devicesMap();


protected:
    Q_DECLARE_PRIVATE(QOnvifManager)
    QScopedPointer<QOnvifManagerPrivate> d_ptr;
    bool cameraExist(const QString& endpoinAddress);

public slots:
    void onReceiveData(QHash<QString, QString> _deviceHash);

signals:
    void newDeviceFound(device::QOnvifDevice* _device);
    void deviceSearchingEnded();

    void deviceInformationReceived(Data::Information, QString);
    void deviceScopesReceived(Data::Scopes, QString);
    void deviceDateAndTimeReceived(Data::DateTime, QString);
    void deviceUsersReceived(Data::Users, QString);
    void deviceCapabilitiesReceived(Data::Capabilities, QString);
    void deviceNetworkInterfacesReceived(Data::Network::Interfaces, QString);
    void deviceNetworkProtocolsReceived(Data::Network::Protocols, QString);
    void deviceNetworkDefaultGatewayReceived(
        Data::Network::DefaultGateway, QString);
    void deviceNetworkDiscoveryModeReceived(
        Data::Network::DiscoveryMode, QString);
    void deviceNetworkDNSReceived(Data::Network::DNS, QString);
    void deviceNetworkHostnameReceived(Data::Network::Hostname, QString);
    void deviceNetworkNTPReceived(Data::Network::NTP, QString);

    void deviceProfilesReceived(Data::Profiles, QString);
    void deviceProfile720pReceived(Data::Profiles, QString);
    void deviceProfileD1Received(Data::Profiles, QString);
    void deviceVideoEncoderConfigurationsReceived(
        Data::MediaConfig::Video::EncoderConfigs, QString);
    void deviceVideoSourceConfigurationsReceived(
        Data::MediaConfig::Video::SourceConfig, QString);
    void deviceVideoEncoderConfigurationOptionReceived(
        Data::MediaConfig::Video::EncoderConfigs::Option, QString);
    void deviceStreamUrisReceived(Data::MediaConfig::Video::StreamUri, QString);
    void deviceImageSettingReceived(Data::MediaConfig::ImageSetting, QString);
    void deviceImageSettingOptionsReceived(
        Data::MediaConfig::ImageSetting::Options, QString);

    void devicePtzConfigurationReceived(Data::Ptz::Config, QString);
    void devicePresetsReceived(QString);

    void deviceGetResultReceived(Data, device::MessageType, QString);
    void deviceSetResultReceived(bool, device::MessageType, QString);
};

#endif // QONVIFMANAGER_HPP
