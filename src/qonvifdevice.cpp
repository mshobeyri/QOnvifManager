#include "qonvifdevice.hpp"
#include "devicemanagement.h"
#include "mediamanagement.h"

///////////////////////////////////////////////////////////////////////////////
namespace device {
///////////////////////////////////////////////////////////////////////////////
class QOnvifDevicePrivate
{
public:
    QOnvifDevicePrivate(const QString& _username, const QString& _password)
        : iuserName(_username), ipassword(_password) {}
    ~QOnvifDevicePrivate() {

        //        ideviceManagement =
        //            new ONVIF::DeviceManagement(_serviceAddress, iuserName,
        //            ipassword);

        //        imediaManagement =
        //            new ONVIF::MediaManagement(_serviceAddress, iuserName,
        //            ipassword);
    }

    QString iuserName;
    QString ipassword;
    Data    idata;

    // device management
    ONVIF::DeviceManagement* ideviceManagement;


    // media management
    ONVIF::MediaManagement* imediaManagement;

    Data::ProbeData deviceProbeData() {
        return idata.probeData;
    }

    void setDeviceProbeData(Data::ProbeData _probeData) {
        idata.probeData = _probeData;
    }

    Data::DateTime deviceDateAndTime() {
        QScopedPointer<ONVIF::SystemDateAndTime> systemDateAndTime(
            ideviceManagement->getSystemDateAndTime());
        idata.dateTime.localTime = systemDateAndTime->localTime();
        idata.dateTime.utcTime   = systemDateAndTime->utcTime();
        return idata.dateTime;
    }

    bool setDeviceDateAndTime(QDateTime _dateAndTime) {
        ONVIF::SystemDateAndTime systemDateAndTime;
        systemDateAndTime.setlocalTime(_dateAndTime);
        ideviceManagement->setSystemDateAndTime(&systemDateAndTime);
        return true;
    }

    bool refreshDeviceCapabilities() {
        QScopedPointer<ONVIF::Capabilities> capabilitiesDevice(
            ideviceManagement->getCapabilitiesDevice());

        idata.capabilities.accessPolicyConfig =
            capabilitiesDevice->accessPolicyConfig();
        idata.capabilities.deviceXAddr = capabilitiesDevice->deviceXAddr();
        idata.capabilities.iPFilter    = capabilitiesDevice->iPFilter();
        idata.capabilities.zeroConfiguration =
            capabilitiesDevice->zeroConfiguration();
        idata.capabilities.iPVersion6 = capabilitiesDevice->iPVersion6();
        idata.capabilities.dynDNS     = capabilitiesDevice->dynDNS();
        idata.capabilities.discoveryResolve =
            capabilitiesDevice->discoveryResolve();
        idata.capabilities.systemLogging = capabilitiesDevice->systemLogging();
        idata.capabilities.firmwareUpgrade =
            capabilitiesDevice->firmwareUpgrade();
        idata.capabilities.major = capabilitiesDevice->major();
        idata.capabilities.minor = capabilitiesDevice->minor();
        idata.capabilities.httpFirmwareUpgrade =
            capabilitiesDevice->httpFirmwareUpgrade();
        idata.capabilities.httpSystemBackup =
            capabilitiesDevice->httpSystemBackup();
        idata.capabilities.httpSystemLogging =
            capabilitiesDevice->httpSystemLogging();
        idata.capabilities.httpSupportInformation =
            capabilitiesDevice->httpSupportInformation();
        idata.capabilities.inputConnectors =
            capabilitiesDevice->inputConnectors();
        idata.capabilities.relayOutputs = capabilitiesDevice->relayOutputs();
        idata.capabilities.tls11        = capabilitiesDevice->tls11();
        idata.capabilities.tls22        = capabilitiesDevice->tls22();
        idata.capabilities.onboardKeyGeneration =
            capabilitiesDevice->onboardKeyGeneration();
        idata.capabilities.accessPolicyConfig =
            capabilitiesDevice->accessPolicyConfig();
        idata.capabilities.x509Token     = capabilitiesDevice->x509Token();
        idata.capabilities.samlToken     = capabilitiesDevice->samlToken();
        idata.capabilities.kerberosToken = capabilitiesDevice->kerberosToken();
        idata.capabilities.relToken      = capabilitiesDevice->relToken();
        idata.capabilities.tls10         = capabilitiesDevice->tls10();
        idata.capabilities.dot1x         = capabilitiesDevice->dot1x();
        idata.capabilities.remoteUserHanding =
            capabilitiesDevice->remoteUserHanding();
        idata.capabilities.systemBackup = capabilitiesDevice->systemBackup();
        idata.capabilities.discoveryBye = capabilitiesDevice->discoveryBye();
        idata.capabilities.remoteDiscovery =
            capabilitiesDevice->remoteDiscovery();

        // ptz capabilities
        QScopedPointer<ONVIF::Capabilities> capabilitiesPtz(
            ideviceManagement->getCapabilitiesDevice());

        idata.capabilities.ptzAddress = capabilitiesPtz->ptzXAddr();

        // image capabilities
        QScopedPointer<ONVIF::Capabilities> capabilitiesImage(
            ideviceManagement->getCapabilitiesDevice());

        idata.capabilities.imagingXAddress = capabilitiesImage->imagingXAddr();

        // media capabilities
        QScopedPointer<ONVIF::Capabilities> capabilitiesMedia(
            ideviceManagement->getCapabilitiesDevice());

        idata.capabilities.mediaXAddress = capabilitiesMedia->mediaXAddr();
        idata.capabilities.rtpMulticast  = capabilitiesMedia->rtpMulticast();
        idata.capabilities.rtpTcp        = capabilitiesMedia->rtpTcp();
        idata.capabilities.rtpRtspTcp    = capabilitiesMedia->rtpRtspTcp();

        return true;
    }

    bool refreshDeviceInformation() {
        QHash<QString, QString> deviceInformationHash =
            ideviceManagement->getDeviceInformation();
        idata.information.manufacturer = deviceInformationHash.value("mf");
        idata.information.model        = deviceInformationHash.value("model");
        idata.information.firmwareVersion =
            deviceInformationHash.value("firmware_version");
        idata.information.serialNumber =
            deviceInformationHash.value("serial_number");
        idata.information.hardwareId =
            deviceInformationHash.value("hardware_id");
        return true;
    }

    bool resetFactoryDevice() {
        // todo: reset factory device
        return true;
    }

    bool rebootDevice() {
        // todo: reboot device
        return true;
    }

    bool refreshVideoConfigs() {
        // get video encoder options
        QScopedPointer<ONVIF::VideoEncoderConfigurationOptions>
            videoEncoderConfigurationOptions(
                imediaManagement->getVideoEncoderConfigurationOptions());

        idata.mediaConfig.video.encodingOptions.encodingIntervalRangeMax =
            videoEncoderConfigurationOptions->encodingIntervalRangeMax();

        idata.mediaConfig.video.encodingOptions.encodingIntervalRangeMin =
            videoEncoderConfigurationOptions->encodingIntervalRangeMin();

        idata.mediaConfig.video.encodingOptions.frameRateRangeMax =
            videoEncoderConfigurationOptions->frameRateRangeMax();

        idata.mediaConfig.video.encodingOptions.frameRateRangeMin =
            videoEncoderConfigurationOptions->frameRateRangeMin();

        idata.mediaConfig.video.encodingOptions.govLengthRangeMax =
            videoEncoderConfigurationOptions->govLengthRangeMax();

        idata.mediaConfig.video.encodingOptions.govLengthRangeMin =
            videoEncoderConfigurationOptions->govLengthRangeMin();

        idata.mediaConfig.video.encodingOptions.qualityRangeMin =
            videoEncoderConfigurationOptions->qualityRangeMin();

        idata.mediaConfig.video.encodingOptions.qulityRangeMax =
            videoEncoderConfigurationOptions->qulityRangeMax();

        idata.mediaConfig.video.encodingOptions.resAvailableHeight =
            videoEncoderConfigurationOptions->getResAvailableHeight();

        idata.mediaConfig.video.encodingOptions.resAvailableWidth =
            videoEncoderConfigurationOptions->getResAvailableWidth();

        foreach (
            ONVIF::VideoEncoderConfigurationOptions::H264ProfilesSupported
                h264ProfilesSupporte,
            videoEncoderConfigurationOptions->getH264ProfilesSupported()) {
            int intCastTemp = static_cast<int>(h264ProfilesSupporte);

            Data::MediaConfig::Video::EncodingOptions::H264ProfilesSupported
                enumCastTemp =
                    static_cast<Data::MediaConfig::Video::EncodingOptions::
                                    H264ProfilesSupported>(intCastTemp);

            idata.mediaConfig.video.encodingOptions.h264ProfilesSupported
                .append(enumCastTemp);
        }

        // get video encoder config
        QScopedPointer<ONVIF::VideoEncoderConfigurations>
            videoEncoderConfigurations(
                imediaManagement->getVideoEncoderConfigurations());

        idata.mediaConfig.video.encodingConfig.autoStart =
            videoEncoderConfigurations->getAutoStart();

        idata.mediaConfig.video.encodingConfig.bitrateLimit =
            videoEncoderConfigurations->getBitrateLimit();

        idata.mediaConfig.video.encodingConfig.encoding =
            videoEncoderConfigurations->getEncoding();

        idata.mediaConfig.video.encodingConfig.encodingInterval =
            videoEncoderConfigurations->getEncodingInterval();

        idata.mediaConfig.video.encodingConfig.frameRateLimit =
            videoEncoderConfigurations->getFrameRateLimit();

        idata.mediaConfig.video.encodingConfig.govLength =
            videoEncoderConfigurations->getGovLength();

        idata.mediaConfig.video.encodingConfig.h264Profile =
            videoEncoderConfigurations->getH264Profile();

        idata.mediaConfig.video.encodingConfig.height =
            videoEncoderConfigurations->getHeight();

        idata.mediaConfig.video.encodingConfig.ipv4Address =
            videoEncoderConfigurations->getIpv4Address();

        idata.mediaConfig.video.encodingConfig.ipv6Address =
            videoEncoderConfigurations->getIpv6Address();

        idata.mediaConfig.video.encodingConfig.name =
            videoEncoderConfigurations->getName();

        idata.mediaConfig.video.encodingConfig.port =
            videoEncoderConfigurations->getPort();

        idata.mediaConfig.video.encodingConfig.quality =
            videoEncoderConfigurations->getQuality();

        idata.mediaConfig.video.encodingConfig.sessionTimeout =
            videoEncoderConfigurations->getSessionTimeout();

        idata.mediaConfig.video.encodingConfig.token =
            videoEncoderConfigurations->getToken();

        idata.mediaConfig.video.encodingConfig.ttl =
            videoEncoderConfigurations->getTtl();

        idata.mediaConfig.video.encodingConfig.type =
            videoEncoderConfigurations->getType();

        idata.mediaConfig.video.encodingConfig.useCount =
            videoEncoderConfigurations->getUseCount();

        // get video source config
        QScopedPointer<ONVIF::VideoSourceConfigurations>
            videoSourceConfigurations(
                imediaManagement->getVideoSourceConfigurations());


        idata.mediaConfig.video.sourceConfig.name =
            videoSourceConfigurations->getName();

        idata.mediaConfig.video.sourceConfig.useCount =
            videoSourceConfigurations->getUseCount();

        idata.mediaConfig.video.sourceConfig.sourceToken =
            videoSourceConfigurations->getSourceToken();

        idata.mediaConfig.video.sourceConfig.bounds =
            videoSourceConfigurations->getBounds();

        return true;
    }

    bool refreshAudioConfigs() {
        // todo: add giving audio options of cameras
        imediaManagement->getAudioEncoderConfigurationOptions();
        imediaManagement->getAudioEncoderConfigurations();
        imediaManagement->getAudioSourceConfigurations();
        return true;
    }
};

QOnvifDevice::QOnvifDevice() {}

QOnvifDevice::QOnvifDevice(
    QString  _serviceAddress,
    QString  _userName,
    QString  _password,
    QObject* _parent)
    : d_ptr{new QOnvifDevicePrivate{_userName, _password}}, QObject(_parent) {}

QOnvifDevice::~QOnvifDevice() {}

Data&
QOnvifDevice::data() {
    return d_ptr->idata;
}

void QOnvifDevice::setDeviceProbeData(Data::ProbeData _probeData)
{
    d_ptr->setDeviceProbeData(_probeData);
}

bool QOnvifDevice::setDeviceDateAndTime(QDateTime _dateAndTime)
{
    return d_ptr->setDeviceDateAndTime(_dateAndTime);
}

bool QOnvifDevice::refreshDeviceCapabilities()
{
    return d_ptr->refreshDeviceCapabilities();
}

bool QOnvifDevice::refreshDeviceInformation()
{
    return d_ptr->refreshDeviceInformation();
}

bool QOnvifDevice::resetFactoryDevice()
{
    return d_ptr->resetFactoryDevice();
}

bool QOnvifDevice::rebootDevice()
{
    return d_ptr->rebootDevice();
}

bool QOnvifDevice::refreshVideoConfigs()
{
    return d_ptr->refreshVideoConfigs();
}

bool QOnvifDevice::refreshAudioConfigs()
{
    return d_ptr->refreshAudioConfigs();
}

///////////////////////////////////////////////////////////////////////////////
} // namespace device
///////////////////////////////////////////////////////////////////////////////
