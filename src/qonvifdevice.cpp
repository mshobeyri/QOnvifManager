#include "qonvifdevice.hpp"
#include "devicemanagement.h"
#include "mediamanagement.h"

using namespace device;

QOnvifDevice::QOnvifDevice()
{
}

QOnvifDevice::QOnvifDevice(QString _serviceAddress, QString _userName, QString _password, QObject *_parent):
    QObject(_parent), iuserName(_userName), ipassword(_password)

{
    ideviceManagement = new ONVIF::DeviceManagement(
        _serviceAddress, iuserName, ipassword);

    imediaManagement = new ONVIF::MediaManagement(
        _serviceAddress, iuserName, ipassword);
}

QOnvifDevice::~QOnvifDevice()
{
    delete ideviceManagement;
}

QOnvifDevice::ProbeData QOnvifDevice::deviceProbeData()
{
    return ideviceProbeData;
}

void QOnvifDevice::setDeviceProbeData(ProbeData _probeData)
{
    ideviceProbeData = _probeData;
}

QOnvifDevice::DateTime
QOnvifDevice::deviceDateAndTime()
{
    QScopedPointer <ONVIF::SystemDateAndTime> systemDateAndTime(ideviceManagement->getSystemDateAndTime());
    idateAndTime.localTime = systemDateAndTime->localTime();
    idateAndTime.utcTime = systemDateAndTime->utcTime();
    return idateAndTime;
}

bool
QOnvifDevice::setDeviceDateAndTime(QDateTime _dateAndTime)
{
    ONVIF::SystemDateAndTime systemDateAndTime;
    systemDateAndTime.setlocalTime(_dateAndTime);
    ideviceManagement->setSystemDateAndTime(&systemDateAndTime);
    return true;
}

bool
QOnvifDevice::refreshDeviceCapabilities()
{
    QScopedPointer <ONVIF::Capabilities> capabilitiesDevice (ideviceManagement->getCapabilitiesDevice());

    ideviceCapabilities.accessPolicyConfig = capabilitiesDevice->accessPolicyConfig();
    ideviceCapabilities.deviceXAddr = capabilitiesDevice->deviceXAddr();
    ideviceCapabilities.iPFilter = capabilitiesDevice->iPFilter();
    ideviceCapabilities.zeroConfiguration = capabilitiesDevice->zeroConfiguration();
    ideviceCapabilities.iPVersion6 = capabilitiesDevice->iPVersion6();
    ideviceCapabilities.dynDNS = capabilitiesDevice->dynDNS();
    ideviceCapabilities.discoveryResolve = capabilitiesDevice->discoveryResolve();
    ideviceCapabilities.systemLogging = capabilitiesDevice->systemLogging();
    ideviceCapabilities.firmwareUpgrade = capabilitiesDevice->firmwareUpgrade();
    ideviceCapabilities.major = capabilitiesDevice->major();
    ideviceCapabilities.minor = capabilitiesDevice->minor();
    ideviceCapabilities.httpFirmwareUpgrade = capabilitiesDevice->httpFirmwareUpgrade();
    ideviceCapabilities.httpSystemBackup = capabilitiesDevice->httpSystemBackup();
    ideviceCapabilities.httpSystemLogging = capabilitiesDevice->httpSystemLogging();
    ideviceCapabilities.httpSupportInformation = capabilitiesDevice->httpSupportInformation();
    ideviceCapabilities.inputConnectors = capabilitiesDevice->inputConnectors();
    ideviceCapabilities.relayOutputs = capabilitiesDevice->relayOutputs();
    ideviceCapabilities.tls11 = capabilitiesDevice->tls11();
    ideviceCapabilities.tls22 = capabilitiesDevice->tls22();
    ideviceCapabilities.onboardKeyGeneration = capabilitiesDevice->onboardKeyGeneration();
    ideviceCapabilities.accessPolicyConfig = capabilitiesDevice->accessPolicyConfig();
    ideviceCapabilities.x509Token = capabilitiesDevice->x509Token();
    ideviceCapabilities.samlToken = capabilitiesDevice->samlToken();
    ideviceCapabilities.kerberosToken = capabilitiesDevice->kerberosToken();
    ideviceCapabilities.relToken = capabilitiesDevice->relToken();
    ideviceCapabilities.tls10 = capabilitiesDevice->tls10();
    ideviceCapabilities.dot1x = capabilitiesDevice->dot1x();
    ideviceCapabilities.remoteUserHanding = capabilitiesDevice->remoteUserHanding();
    ideviceCapabilities.systemBackup = capabilitiesDevice->systemBackup();
    ideviceCapabilities.discoveryBye = capabilitiesDevice->discoveryBye();
    ideviceCapabilities.remoteDiscovery = capabilitiesDevice->remoteDiscovery();

    //ptz capabilities
    QScopedPointer <ONVIF::Capabilities> capabilitiesPtz (ideviceManagement->getCapabilitiesDevice());

    ideviceCapabilities.ptzAddress = capabilitiesPtz->ptzXAddr();

    //image capabilities
    QScopedPointer <ONVIF::Capabilities> capabilitiesImage (ideviceManagement->getCapabilitiesDevice());

    ideviceCapabilities.imagingXAddress = capabilitiesImage->imagingXAddr();

    //media capabilities
    QScopedPointer <ONVIF::Capabilities> capabilitiesMedia (ideviceManagement->getCapabilitiesDevice());

    ideviceCapabilities.mediaXAddress = capabilitiesMedia->mediaXAddr();
    ideviceCapabilities.rtpMulticast = capabilitiesMedia->rtpMulticast();
    ideviceCapabilities.rtpTcp = capabilitiesMedia->rtpTcp();
    ideviceCapabilities.rtpRtspTcp = capabilitiesMedia->rtpRtspTcp();

    return true;
}

bool
QOnvifDevice::refreshDeviceInformation()
{
    QHash<QString, QString>  deviceInformationHash = ideviceManagement->getDeviceInformation();
    ideviceInformation.manufacturer = deviceInformationHash.value("mf");
    ideviceInformation.model = deviceInformationHash.value("model");
    ideviceInformation.firmwareVersion = deviceInformationHash.value("firmware_version");
    ideviceInformation.serialNumber = deviceInformationHash.value("serial_number");
    ideviceInformation.hardwareId = deviceInformationHash.value("hardware_id");
    return true;
}

bool
QOnvifDevice::resetFactoryDevice()
{
    //todo: reset factory device
    return true;
}

bool
QOnvifDevice::rebootDevice()
{
    //todo: reboot device
    return true;
}

bool
QOnvifDevice::refreshVideoConfigs()
{
    // get video encoder options
    QScopedPointer<ONVIF::VideoEncoderConfigurationOptions> videoEncoderConfigurationOptions
            (imediaManagement->getVideoEncoderConfigurationOptions());

    imediaConfig.video.encodingOptions.encodingIntervalRangeMax =
            videoEncoderConfigurationOptions->encodingIntervalRangeMax();

    imediaConfig.video.encodingOptions.encodingIntervalRangeMin =
            videoEncoderConfigurationOptions->encodingIntervalRangeMin();

    imediaConfig.video.encodingOptions.frameRateRangeMax =
            videoEncoderConfigurationOptions->frameRateRangeMax();

    imediaConfig.video.encodingOptions.frameRateRangeMin =
            videoEncoderConfigurationOptions->frameRateRangeMin();

    imediaConfig.video.encodingOptions.govLengthRangeMax =
            videoEncoderConfigurationOptions->govLengthRangeMax();

    imediaConfig.video.encodingOptions.govLengthRangeMin =
            videoEncoderConfigurationOptions->govLengthRangeMin();

    imediaConfig.video.encodingOptions.qualityRangeMin =
            videoEncoderConfigurationOptions->qualityRangeMin();

    imediaConfig.video.encodingOptions.qulityRangeMax =
            videoEncoderConfigurationOptions->qulityRangeMax();

    imediaConfig.video.encodingOptions.resAvailableHeight =
            videoEncoderConfigurationOptions->getResAvailableHeight();

    imediaConfig.video.encodingOptions.resAvailableWidth =
            videoEncoderConfigurationOptions->getResAvailableWidth();

    foreach (ONVIF::VideoEncoderConfigurationOptions::H264ProfilesSupported h264ProfilesSupporte,
             videoEncoderConfigurationOptions->getH264ProfilesSupported())
    {
        int intCastTemp = static_cast<int>(h264ProfilesSupporte);

        MediaConfig::Video::EncodingOptions::H264ProfilesSupported enumCastTemp =
                static_cast<MediaConfig::Video::EncodingOptions::H264ProfilesSupported>(intCastTemp);

        imediaConfig.video.encodingOptions.h264ProfilesSupported.append(enumCastTemp);
    }

    // get video encoder config
    QScopedPointer<ONVIF::VideoEncoderConfigurations> videoEncoderConfigurations
            (imediaManagement->getVideoEncoderConfigurations());

    imediaConfig.video.encodingConfig.autoStart =
            videoEncoderConfigurations->getAutoStart();

    imediaConfig.video.encodingConfig.bitrateLimit =
            videoEncoderConfigurations->getBitrateLimit();

    imediaConfig.video.encodingConfig.encoding =
            videoEncoderConfigurations->getEncoding();

    imediaConfig.video.encodingConfig.encodingInterval =
            videoEncoderConfigurations->getEncodingInterval();

    imediaConfig.video.encodingConfig.frameRateLimit =
            videoEncoderConfigurations->getFrameRateLimit();

    imediaConfig.video.encodingConfig.govLength =
            videoEncoderConfigurations->getGovLength();

    imediaConfig.video.encodingConfig.h264Profile =
            videoEncoderConfigurations->getH264Profile();

    imediaConfig.video.encodingConfig.height =
            videoEncoderConfigurations->getHeight();

    imediaConfig.video.encodingConfig.ipv4Address =
            videoEncoderConfigurations->getIpv4Address();

    imediaConfig.video.encodingConfig.ipv6Address =
            videoEncoderConfigurations->getIpv6Address();

    imediaConfig.video.encodingConfig.name =
            videoEncoderConfigurations->getName();

    imediaConfig.video.encodingConfig.port =
            videoEncoderConfigurations->getPort();

    imediaConfig.video.encodingConfig.quality =
            videoEncoderConfigurations->getQuality();

    imediaConfig.video.encodingConfig.sessionTimeout =
            videoEncoderConfigurations->getSessionTimeout();

    imediaConfig.video.encodingConfig.token =
            videoEncoderConfigurations->getToken();

    imediaConfig.video.encodingConfig.ttl =
            videoEncoderConfigurations->getTtl();

    imediaConfig.video.encodingConfig.type =
            videoEncoderConfigurations->getType();

    imediaConfig.video.encodingConfig.useCount =
            videoEncoderConfigurations->getUseCount();

    // get video source config
    QScopedPointer<ONVIF::VideoSourceConfigurations> videoSourceConfigurations
            (imediaManagement->getVideoSourceConfigurations());


    imediaConfig.video.sourceConfig.name =
            videoSourceConfigurations->getName();

    imediaConfig.video.sourceConfig.useCount =
            videoSourceConfigurations->getUseCount();

    imediaConfig.video.sourceConfig.sourceToken =
            videoSourceConfigurations->getSourceToken();

    imediaConfig.video.sourceConfig.bounds =
            videoSourceConfigurations->getBounds();

    return true;

}

bool
QOnvifDevice::refreshAudioConfigs()
{
    //todo: add giving audio options of cameras
    imediaManagement->getAudioEncoderConfigurationOptions();
    imediaManagement->getAudioEncoderConfigurations();
    imediaManagement->getAudioSourceConfigurations();
    return true;
}
