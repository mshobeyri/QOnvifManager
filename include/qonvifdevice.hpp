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

    bool setDateAndTime(QDateTime _dateAndTime);
    bool setScopes(QString _name, QString _location);
    bool setVideoConfig(Data::MediaConfig::Video::EncoderConfig _videoConfig);

    bool refreshDeviceCapabilities();
    bool refreshDeviceInformation();
    bool refreshDeviceScopes();

    bool resetFactoryDevice();
    bool rebootDevice();

    // media management
    bool refreshVideoConfigs();
    bool refreshVideoConfigsOptions();
    bool refreshStreamUri();
    bool refreshAudioConfigs();


    bool refreshProfiles();
    bool refreshInterfaces();

    bool refreshUsers();

    //ptz management
    bool refreshPtzConfiguration();
    bool goHomePosition();
    bool setHomePosition();

private:
    Q_DECLARE_PRIVATE(QOnvifDevice)
    QScopedPointer<QOnvifDevicePrivate> d_ptr;
};
///////////////////////////////////////////////////////////////////////////////
} // namespace device
///////////////////////////////////////////////////////////////////////////////

#endif // QONVIFDEVICE_HPP
