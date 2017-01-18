#ifndef QONVIFDEVICE_HPP
#define QONVIFDEVICE_HPP

#include <QDateTime>
#include <QObject>

namespace ONVIF {
    class DeviceManagement;
}

class QOnvifDevice : public QObject
{
public:
    struct DeviceInformation{
        QString manufacturer;
        QString model;
        QString firmwareVersion;
        QString serialNumber;
        QString hardwareId;
    };

    struct DeviceCapabilities{
        //ptz capabilities
        QString ptzAddress;

        //imaging capabilities
        QString imagingXAddress;

        //media capabilities
        QString mediaXAddress;
        bool rtpMulticast;
        bool rtpTcp;
        bool rtpRtspTcp;

        //public capabilities
        QString deviceXAddr;
        bool iPFilter;
        bool zeroConfiguration;
        bool iPVersion6;
        bool dynDNS;
        bool discoveryResolve;
        bool systemLogging;
        bool firmwareUpgrade;
        int major;
        bool minor;
        bool httpFirmwareUpgrade;
        bool httpSystemBackup;
        bool httpSystemLogging;
        bool httpSupportInformation;
        int inputConnectors;
        int relayOutputs;
        bool tls11;
        bool tls22;
        bool onboardKeyGeneration;
        bool accessPolicyConfig;
        bool x509Token;
        bool samlToken;
        bool kerberosToken;
        bool relToken;
        bool tls10;
        bool dot1x;
        bool remoteUserHanding;
        bool systemBackup;
        bool discoveryBye;
        bool remoteDiscovery;
    };

    struct DeviceProbeData{
        QString iendPointAddress;
        QString itypes;
        QString ideviceIp;
        QString ideviceServiceAddress;
        QString iscopes;
        QString imetadataVersion;
    };

    struct DateTime{
        QDateTime utcTime;
        QDateTime localTime;
    };

    QOnvifDevice();
    QOnvifDevice(QString _serviceAddress, QString _userName, QString _password, QObject* _parent);
    ~QOnvifDevice();

    DeviceProbeData deviceProbeData();
    void setDeviceProbeData(DeviceProbeData _probeData);

    DateTime deviceDateAndTime();
    bool setDeviceDateAndTime(QDateTime _dateAndTime);

    bool refreshDeviceCapabilities();
    bool refreshDeviceInformation();

    bool resetFactoryDevice();
    bool rebootDevice();

private:
    ONVIF::DeviceManagement *ideviceManagement;

    QString idescription;
    QString iuserName;
    QString ipassword;
    DateTime idateAndTime;
    DeviceProbeData ideviceProbeData;
    DeviceInformation ideviceInformation;
    DeviceCapabilities ideviceCapabilities;


};

#endif // QONVIFDEVICE_HPP
