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
    QOnvifDevice();
    QOnvifDevice(
        QString  _serviceAddress,
        QString  _userName,
        QString  _password,
        QObject* _parent);
    ~QOnvifDevice();
    Data &data();
    // device management
    void setDeviceProbeData(Data::ProbeData _probeData);

    bool setDeviceDateAndTime(QDateTime _dateAndTime);

    bool refreshDeviceCapabilities();
    bool refreshDeviceInformation();

    bool resetFactoryDevice();
    bool rebootDevice();

    // media management
    bool refreshVideoConfigs();
    bool refreshAudioConfigs();

private:
    Q_DECLARE_PRIVATE(QOnvifDevice)
    QScopedPointer<QOnvifDevicePrivate> d_ptr;
};
///////////////////////////////////////////////////////////////////////////////
} // namespace device
///////////////////////////////////////////////////////////////////////////////

#endif // QONVIFDEVICE_HPP
