#ifndef QONVIFMANAGER_HPP
#define QONVIFMANAGER_HPP

#include <QDateTime>
#include <QMap>
#include <QHostAddress>
#include "qonvifdevice.hpp"

namespace ONVIF
{
class DeviceSearcher;
}

class QOnvifManager: public QObject
{
    Q_OBJECT
public:
    QOnvifManager(QString _userName, QString _password, QObject *_parent);

    bool refreshDevicesList();
    bool refreshDeviceCapabilities(QString _deviceEndPointAddress);
    bool refreshDeviceInformations(QString _deviceEndPointAddress);

    QOnvifDevice::DateTime deviceDateAndTime(QString _deviceEndPointAddress);

    QOnvifDevice* device(QString _deviceEndPointAddress);
    QMap<QString, QOnvifDevice *> devicesMap();

    bool setDeviceDateAndTime(QString _deviceEndPointAddress, QDateTime _dateTime);
    void setDefaulUsernameAndPassword(QString _username, QString _password);
    bool resetFactoryDevice(QString _deviceEndPointAddress);
    bool rebootDevice(QString _deviceEndPointAddress);

protected:
    QString iuserName;
    QString ipassword;
    QMap <QString, QOnvifDevice* > idevicesMap;
    QHostAddress ihostAddress;
    ONVIF::DeviceSearcher *ideviceSearcher;

public slots:
    void onReciveData(QHash<QString, QString> _deviceHash);

signals:
    void newDeviceFinded(QOnvifDevice* _device);
    void deviceSearchingEnded();
};

#endif // QONVIFMANAGER_HPP
