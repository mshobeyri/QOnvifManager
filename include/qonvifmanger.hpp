#ifndef QONVIFMANGER_HPP
#define QONVIFMANGER_HPP

#include <QDateTime>
#include <QMap>
#include <QHostAddress>
#include "qonvifdevice.hpp"

namespace ONVIF {
class DeviceSearcher;
}
class QOnvifDevice;

class QOnvifManger: public QObject
{
    Q_OBJECT
public:
    QOnvifManger(QString _userName, QString _password, QObject *_parent);

    bool refreshDevicesList();

    QDateTime deviceDateAndTime(QString _deviceEndPointAddress);
    QOnvifDevice deviceFullData(QString _deviceEndPointAddress);

    bool setDeviceDateAndTime(QString _deviceEndPointAddress, QDateTime _dateTime);
    bool resetFactoryDevice(QString _deviceEndPointAddress);
    bool rebootDevice(QString _deviceEndPointAddress);

protected:
    QString iuserName;
    QString ipassword;
    QMap <QString , QOnvifDevice> idevicesMap;
    QHostAddress ihostAddress;
    ONVIF::DeviceSearcher *ideviceSearcher;

private slots:
    void onDeviceFinded(QHash<QString, QString> _deviceHash);
};

#endif // QONVIFMANGER_HPP
