#ifndef QONVIFMANAGER_HPP
#define QONVIFMANAGER_HPP

#include "qonvifdevice.hpp"
#include <QDateTime>
#include <QHostAddress>
#include <QMap>
#include <QScopedPointer>

#ifndef QONVIFMANAGER_GLOBAL_HPP
#define QONVIFMANAGER_GLOBAL_HPP

#include <QtCore/qglobal.h>

#if defined(QONVIFMANAGER_LIBRARY)
#define QONVIFMANAGERSHARED_EXPORT Q_DECL_EXPORT
#else
#define QONVIFMANAGERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif


namespace ONVIF {
class DeviceSearcher;
}

using namespace device;
class QOnvifManagerPrivate;

class QONVIFMANAGERSHARED_EXPORT QOnvifManager : public QObject
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
    bool refreshDeviceVideoConfigsOptions(
        QString _deviceEndPointAddress,
        QString _configToken = "",
        QString _profileToken = "");


    bool refreshDeviceProfiles(QString _deviceEndPointAddress);
    bool refreshDeviceInterfaces(QString _deviceEndPointAddress);
    bool refreshDeviceScopes(QString _deviceEndPointAddress);

    bool refreshDeviceUsers(QString _deviceEndPointAddress);

    bool deviceDateAndTime(
        QString _deviceEndPointAddress, Data::DateTime& _datetime);

    bool
    setDeviceDateAndTime(QString _deviceEndPointAddress, QDateTime _dateTime);
    void setDefaulUsernameAndPassword(QString _username, QString _password);
    bool setDeviceScopes(
        QString _deviceEndPointAddress, QString _name, QString _location);

    bool resetFactoryDevice(QString _deviceEndPointAddress);
    bool rebootDevice(QString _deviceEndPointAddress);

    QOnvifDevice* device(QString _deviceEndPointAddress);
    QMap<QString, QOnvifDevice*>& devicesMap();

protected:
    Q_DECLARE_PRIVATE(QOnvifManager)
    QScopedPointer<QOnvifManagerPrivate> d_ptr;
    bool cameraExist(const QString& endpoinAddress);

public slots:
    void onReciveData(QHash<QString, QString> _deviceHash);

signals:
    void newDeviceFinded(QOnvifDevice* _device);
    void deviceSearchingEnded();
};

#endif // QONVIFMANAGER_HPP
