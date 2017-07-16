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
    bool refreshDeviceCapabilities(QString _deviceEndPointAddress);
    bool refreshDeviceInformations(QString _deviceEndPointAddress);

    bool refreshDeviceVideoConfigs(QString _deviceEndPointAddress);
    bool refreshDeviceStreamUris(QString _deviceEndPointAddress);
    bool refreshDeviceStreamUri(QString _deviceEndPointAddress);
    bool refreshDeviceVideoConfigsOptions(QString _deviceEndPointAddress);

    bool refreshDeviceProfiles(QString _deviceEndPointAddress);
    bool refreshDeviceInterfaces(QString _deviceEndPointAddress);
    bool refreshDeviceProtocols(QString _deviceEndPointAddress);
    bool refreshDeviceDefaultGateway(QString _deviceEndPointAddress);
    bool refreshDeviceDiscoveryMode(QString _deviceEndPointAddress);
    bool refreshDeviceDNS(QString _deviceEndPointAddress);
    bool refreshDeviceHostname(QString _deviceEndPointAddress);
    bool refreshDeviceNTP(QString _deviceEndPointAddress);
    bool refreshDeviceScopes(QString _deviceEndPointAddress);

    bool refreshDeviceUsers(QString _deviceEndPointAddress);

    bool deviceDateAndTime(
        QString _deviceEndPointAddress, Data::DateTime& _datetime);

    bool setDeviceDateAndTime(
        QString   _deviceEndPointAddress,
        QDateTime _dateTime,
        QString   _zone,
        bool      _daylightSaving,
        bool      _isLocal);
    bool setDeviceImageSetting(
        QString                          _deviceEndPointAddress,
        Data::MediaConfig::ImageSetting& _imageSetting);

    void setDefaulUsernameAndPassword(QString _username, QString _password);
    bool setDeviceScopes(
        QString _deviceEndPointAddress, QString _name, QString _location);
    bool setDeviceVideoConfig(
        QString                                 _deviceEndPointAddress,
        Data::MediaConfig::Video::EncoderConfig _videoConfig);

    bool setDeviceUsers(QString _deviceEndPointAddress, Data::Users _users);

    bool setDeviceNetworkInterfaces(
        QString _deviceEndPointAddress, Data::Network::Interfaces _interfaces);

    bool setDeviceNetworkProtocols(
        QString _deviceEndPointAddress, Data::Network::Protocols _protocols);

    bool setDeviceNetworkDefaultGateway(
        QString                       _deviceEndPointAddress,
        Data::Network::DefaultGateway _defaultGateway);

    bool setDeviceNetworkDiscoveryMode(
        QString                      _deviceEndPointAddress,
        Data::Network::DiscoveryMode _discoveryMode);

    bool setDeviceNetworkDNS(
        QString _deviceEndPointAddress, Data::Network::DNS _dns);

    bool setDeviceNetworkHostname(
        QString _deviceEndPointAddress, Data::Network::Hostname _hostname);

    bool setDeviceNetworkNTP(
        QString _deviceEndPointAddress, Data::Network::NTP _ntp);


    bool refreshDevicePtzConfigs(QString _deviceEndPointAddress);

    bool refreshDeviceImageSetting(QString _deviceEndPointAddress);
    bool refreshDeviceImageSettingOptions(QString _deviceEndPointAddress);

    bool resetFactoryDevice(QString _deviceEndPointAddress, bool isHard);
    bool rebootDevice(QString _deviceEndPointAddress);

    // ptz

    bool continuousMove(
        QString     _deviceEndPointAddress,
        const float _x,
        const float _y,
        const float _z);

    bool stopMovement(QString _deviceEndPointAddress);

    // public
    device::QOnvifDevice* device(QString _deviceEndPointAddress);
    QMap<QString, device::QOnvifDevice*>& devicesMap();


protected:
    Q_DECLARE_PRIVATE(QOnvifManager)
    QScopedPointer<QOnvifManagerPrivate> d_ptr;
    bool cameraExist(const QString& endpoinAddress);

public slots:
    void onReciveData(QHash<QString, QString> _deviceHash);

signals:
    void newDeviceFinded(device::QOnvifDevice* _device);
    void deviceSearchingEnded();
};

#endif // QONVIFMANAGER_HPP
