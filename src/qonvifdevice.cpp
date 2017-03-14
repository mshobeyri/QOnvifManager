#include "qonvifdevice.hpp"
#include "devicemanagement.h"
#include "mediamanagement.h"

///////////////////////////////////////////////////////////////////////////////
namespace device {
///////////////////////////////////////////////////////////////////////////////
class QOnvifDevicePrivate
{
public:
    QOnvifDevicePrivate(
        const QString _serviceAddress,
        const QString _username,
        const QString _password)
        : iuserName(_username), ipassword(_password) {
        ideviceManagement =
            new ONVIF::DeviceManagement{_serviceAddress, iuserName, ipassword};

        imediaManagement =
            new ONVIF::MediaManagement{_serviceAddress, iuserName, ipassword};
    }
    ~QOnvifDevicePrivate() {
        delete ideviceManagement;
        delete imediaManagement;
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

    bool deviceDateAndTime(Data::DateTime& _datetime) {
        QScopedPointer<ONVIF::SystemDateAndTime> systemDateAndTime(
            ideviceManagement->getSystemDateAndTime());
        if (!systemDateAndTime)
            return false;
        idata.dateTime.localTime = systemDateAndTime->localTime();
        idata.dateTime.utcTime   = systemDateAndTime->utcTime();
        _datetime                = idata.dateTime;
        return true;
    }

    bool setDeviceDateAndTime(QDateTime _dateAndTime) {
        ONVIF::SystemDateAndTime systemDateAndTime;
        systemDateAndTime.setlocalTime(_dateAndTime);
        ideviceManagement->setSystemDateAndTime(&systemDateAndTime);
        return true;
    }

    bool setScopes(QString _name, QString _location) {
        ONVIF::SystemScopes systemScopes;
        systemScopes.setScopes(_name, _location);

        ideviceManagement->setDeviceScopes(&systemScopes);
        return true;
    }

    bool refreshDeviceCapabilities() {
        QScopedPointer<ONVIF::Capabilities> capabilitiesDevice(
            ideviceManagement->getCapabilitiesDevice());
        if (!capabilitiesDevice)
            return false;
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

    bool refreshDeviceInformation() { // todo
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

    bool refreshDeviceScopes() {
        QHash<QString, QString> deviceScopesHash =
            ideviceManagement->getDeviceScopes();
        idata.scopes.name     = deviceScopesHash.value("name");
        idata.scopes.location = deviceScopesHash.value("location");
        idata.scopes.hardware = deviceScopesHash.value("hardware");
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
        // get video encoder config
        QScopedPointer<ONVIF::VideoEncoderConfigurations>
            videoEncoderConfigurations(
                imediaManagement->getVideoEncoderConfigurations());

        if (!videoEncoderConfigurations)
            return false;

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

        idata.mediaConfig.video.encodingConfig.width =
            videoEncoderConfigurations->getWidth();

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

        if (!videoSourceConfigurations)
            return false;

        idata.mediaConfig.video.sourceConfig.name =
            videoSourceConfigurations->getName();

        idata.mediaConfig.video.sourceConfig.useCount =
            videoSourceConfigurations->getUseCount();

        idata.mediaConfig.video.sourceConfig.sourceToken =
            videoSourceConfigurations->getSourceToken();

        idata.mediaConfig.video.sourceConfig.bounds =
            videoSourceConfigurations->getBounds();

        // get video stream uri
        QScopedPointer<ONVIF::StreamUri> streamUri(
            imediaManagement->getStreamUri("10")); // todo: whats this input
                                                   // exactly? meld retrun value
                                                   // and value of odm
        if (!streamUri)
            return false;

        idata.mediaConfig.video.streamUri.uri = streamUri->uri();
        idata.mediaConfig.video.streamUri.invalidAfterConnect =
            streamUri->invalidAfterConnect();
        idata.mediaConfig.video.streamUri.invalidAfterReboot =
            streamUri->invalidAfterReboot();
        idata.mediaConfig.video.streamUri.timeout = streamUri->timeout();
        return true;
    }

    bool
    refreshVideoConfigsOptions(QString _configToken, QString _profileToken) {
        // get video encoder options
        QScopedPointer<ONVIF::VideoEncoderConfigurationOptions>
            videoEncoderConfigurationOptions(
                imediaManagement->getVideoEncoderConfigurationOptions(
                    _configToken, _profileToken));

        if (!videoEncoderConfigurationOptions)
            return false;
        idata.mediaConfig.video.encodingOptions.encodingIntervalRangeMax =
            videoEncoderConfigurationOptions->encodingIntervalRangeMax();

        idata.mediaConfig.video.encodingOptions.encodingIntervalRangeMin =
            videoEncoderConfigurationOptions->encodingIntervalRangeMin();

        idata.mediaConfig.video.encodingOptions.frameRateRangeMax =
            videoEncoderConfigurationOptions->frameRateRangeMax();

        idata.mediaConfig.video.encodingOptions.frameRateRangeMin =
            videoEncoderConfigurationOptions->frameRateRangeMin();

        idata.mediaConfig.video.encodingOptions.bitRateRangeMax =
            videoEncoderConfigurationOptions->bitRateRangeMax();

        idata.mediaConfig.video.encodingOptions.bitRateRangeMin =
            videoEncoderConfigurationOptions->bitRateRangeMin();

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
        return true;
    }

    bool refreshAudioConfigs() {
        // todo: add giving audio options of cameras
        imediaManagement->getAudioEncoderConfigurationOptions();
        imediaManagement->getAudioEncoderConfigurations();
        imediaManagement->getAudioSourceConfigurations();
        return true;
    }

    bool refreshProfiles() {
        QScopedPointer<ONVIF::Profiles> profiles(
            imediaManagement->getProfiles());
        if (!profiles)
            return false;

        idata.profiles.analytics           = profiles->m_analytics;
        idata.profiles.toKenPro            = profiles->m_toKenPro;
        idata.profiles.fixed               = profiles->m_fixed;
        idata.profiles.namePro             = profiles->m_namePro;
        idata.profiles.nameVsc             = profiles->m_nameVsc;
        idata.profiles.useCountVsc         = profiles->m_useCountVsc;
        idata.profiles.sourceTokenVsc      = profiles->m_sourceTokenVsc;
        idata.profiles.boundsVsc           = profiles->m_boundsVsc;
        idata.profiles.nameVec             = profiles->m_nameVec;
        idata.profiles.useCountVec         = profiles->m_useCountVec;
        idata.profiles.encodingVec         = profiles->m_encodingVec;
        idata.profiles.widthVec            = profiles->m_widthVec;
        idata.profiles.heightVec           = profiles->m_heightVec;
        idata.profiles.qualityVec          = profiles->m_qualityVec;
        idata.profiles.frameRateLimitVec   = profiles->m_frameRateLimitVec;
        idata.profiles.encodingIntervalVec = profiles->m_encodingIntervalVec;
        idata.profiles.bitrateLimitVec     = profiles->m_bitrateLimitVec;
        idata.profiles.govLengthVec        = profiles->m_govLengthVec;
        idata.profiles.h264ProfileVec      = profiles->m_h264ProfileVec;
        idata.profiles.typeVec             = profiles->m_typeVec;
        idata.profiles.ipv4AddressVec      = profiles->m_ipv4AddressVec;
        idata.profiles.ipv6AddressVec      = profiles->m_ipv6AddressVec;
        idata.profiles.portVec             = profiles->m_portVec;
        idata.profiles.ttlVec              = profiles->m_ttlVec;
        idata.profiles.autoStartVec        = profiles->m_autoStartVec;
        idata.profiles.sessionTimeoutVec   = profiles->m_sessionTimeoutVec;
        idata.profiles.namePtz             = profiles->m_namePtz;
        idata.profiles.useCountPtz         = profiles->m_useCountPtz;
        idata.profiles.nodeToken           = profiles->m_nodeToken;
        idata.profiles.defaultAbsolutePantTiltPositionSpace =
            profiles->m_defaultAbsolutePantTiltPositionSpace;
        idata.profiles.defaultAbsoluteZoomPositionSpace =
            profiles->m_defaultAbsoluteZoomPositionSpace;
        idata.profiles.defaultRelativePantTiltTranslationSpace =
            profiles->m_defaultRelativePantTiltTranslationSpace;
        idata.profiles.defaultRelativeZoomTranslationSpace =
            profiles->m_defaultRelativeZoomTranslationSpace;
        idata.profiles.defaultContinuousPantTiltVelocitySpace =
            profiles->m_defaultContinuousPantTiltVelocitySpace;
        idata.profiles.defaultContinuousZoomVelocitySpace =
            profiles->m_defaultContinuousZoomVelocitySpace;
        idata.profiles.panTiltSpace       = profiles->m_panTiltSpace;
        idata.profiles.panTiltX           = profiles->m_panTiltX;
        idata.profiles.panTiltY           = profiles->m_panTiltY;
        idata.profiles.zoomSpace          = profiles->m_zoomSpace;
        idata.profiles.zoomX              = profiles->m_zoomX;
        idata.profiles.defaultPTZTimeout  = profiles->m_defaultPTZTimeout;
        idata.profiles.panTiltUri         = profiles->m_panTiltUri;
        idata.profiles.xRangeMinPt        = profiles->m_xRangeMinPt;
        idata.profiles.xRangeMaxPt        = profiles->m_xRangeMaxPt;
        idata.profiles.yRangeMinPt        = profiles->m_yRangeMinPt;
        idata.profiles.yRangeMaxPt        = profiles->m_yRangeMaxPt;
        idata.profiles.zoomUri            = profiles->m_zoomUri;
        idata.profiles.xRangeMinZm        = profiles->m_xRangeMinZm;
        idata.profiles.xRangeMaxZm        = profiles->m_xRangeMaxZm;
        idata.profiles.nameMc             = profiles->m_nameMc;
        idata.profiles.useCountMc         = profiles->m_useCountMc;
        idata.profiles.status             = profiles->m_status;
        idata.profiles.position           = profiles->m_position;
        idata.profiles.filter             = profiles->m_filter;
        idata.profiles.subscriptionPolicy = profiles->m_subscriptionPolicy;
        idata.profiles.analytics          = profiles->m_analytics;
        idata.profiles.typeMc             = profiles->m_typeMc;
        idata.profiles.ipv4AddressMc      = profiles->m_ipv4AddressMc;
        idata.profiles.ipv6AddressMc      = profiles->m_ipv6AddressMc;
        idata.profiles.portMc             = profiles->m_portMc;
        idata.profiles.ttlMc              = profiles->m_ttlMc;
        idata.profiles.autoStartMc        = profiles->m_autoStartMc;
        idata.profiles.sessionTimeoutMc   = profiles->m_sessionTimeoutMc;


        QScopedPointer<ONVIF::Profile> profile720p(
            imediaManagement->getProfile720P());
        if (!profile720p)
            return false;
        idata.profile720p.analytics         = profile720p->m_analytics;
        idata.profile720p.toKenPro          = profile720p->m_toKenPro;
        idata.profile720p.fixed             = profile720p->m_fixed;
        idata.profile720p.namePro           = profile720p->m_namePro;
        idata.profile720p.nameVsc           = profile720p->m_nameVsc;
        idata.profile720p.useCountVsc       = profile720p->m_useCountVsc;
        idata.profile720p.sourceTokenVsc    = profile720p->m_sourceTokenVsc;
        idata.profile720p.boundsVsc         = profile720p->m_boundsVsc;
        idata.profile720p.nameVec           = profile720p->m_nameVec;
        idata.profile720p.useCountVec       = profile720p->m_useCountVec;
        idata.profile720p.encodingVec       = profile720p->m_encodingVec;
        idata.profile720p.widthVec          = profile720p->m_widthVec;
        idata.profile720p.heightVec         = profile720p->m_heightVec;
        idata.profile720p.qualityVec        = profile720p->m_qualityVec;
        idata.profile720p.frameRateLimitVec = profile720p->m_frameRateLimitVec;
        idata.profile720p.encodingIntervalVec =
            profile720p->m_encodingIntervalVec;
        idata.profile720p.bitrateLimitVec   = profile720p->m_bitrateLimitVec;
        idata.profile720p.govLengthVec      = profile720p->m_govLengthVec;
        idata.profile720p.h264ProfileVec    = profile720p->m_h264ProfileVec;
        idata.profile720p.typeVec           = profile720p->m_typeVec;
        idata.profile720p.ipv4AddressVec    = profile720p->m_ipv4AddressVec;
        idata.profile720p.ipv6AddressVec    = profile720p->m_ipv6AddressVec;
        idata.profile720p.portVec           = profile720p->m_portVec;
        idata.profile720p.ttlVec            = profile720p->m_ttlVec;
        idata.profile720p.autoStartVec      = profile720p->m_autoStartVec;
        idata.profile720p.sessionTimeoutVec = profile720p->m_sessionTimeoutVec;
        idata.profile720p.namePtz           = profile720p->m_namePtz;
        idata.profile720p.useCountPtz       = profile720p->m_useCountPtz;
        idata.profile720p.nodeToken         = profile720p->m_nodeToken;
        idata.profile720p.defaultAbsolutePantTiltPositionSpace =
            profile720p->m_defaultAbsolutePantTiltPositionSpace;
        idata.profile720p.defaultAbsoluteZoomPositionSpace =
            profile720p->m_defaultAbsoluteZoomPositionSpace;
        idata.profile720p.defaultRelativePantTiltTranslationSpace =
            profile720p->m_defaultRelativePantTiltTranslationSpace;
        idata.profile720p.defaultRelativeZoomTranslationSpace =
            profile720p->m_defaultRelativeZoomTranslationSpace;
        idata.profile720p.defaultContinuousPantTiltVelocitySpace =
            profile720p->m_defaultContinuousPantTiltVelocitySpace;
        idata.profile720p.defaultContinuousZoomVelocitySpace =
            profile720p->m_defaultContinuousZoomVelocitySpace;
        idata.profile720p.panTiltSpace      = profile720p->m_panTiltSpace;
        idata.profile720p.panTiltX          = profile720p->m_panTiltX;
        idata.profile720p.panTiltY          = profile720p->m_panTiltY;
        idata.profile720p.zoomSpace         = profile720p->m_zoomSpace;
        idata.profile720p.zoomX             = profile720p->m_zoomX;
        idata.profile720p.defaultPTZTimeout = profile720p->m_defaultPTZTimeout;
        idata.profile720p.panTiltUri        = profile720p->m_panTiltUri;
        idata.profile720p.xRangeMinPt       = profile720p->m_xRangeMinPt;
        idata.profile720p.xRangeMaxPt       = profile720p->m_xRangeMaxPt;
        idata.profile720p.yRangeMinPt       = profile720p->m_yRangeMinPt;
        idata.profile720p.yRangeMaxPt       = profile720p->m_yRangeMaxPt;
        idata.profile720p.zoomUri           = profile720p->m_zoomUri;
        idata.profile720p.xRangeMinZm       = profile720p->m_xRangeMinZm;
        idata.profile720p.xRangeMaxZm       = profile720p->m_xRangeMaxZm;
        idata.profile720p.nameMc            = profile720p->m_nameMc;
        idata.profile720p.useCountMc        = profile720p->m_useCountMc;
        idata.profile720p.status            = profile720p->m_status;
        idata.profile720p.position          = profile720p->m_position;
        idata.profile720p.filter            = profile720p->m_filter;
        idata.profile720p.subscriptionPolicy =
            profile720p->m_subscriptionPolicy;
        idata.profile720p.analytics        = profile720p->m_analytics;
        idata.profile720p.typeMc           = profile720p->m_typeMc;
        idata.profile720p.ipv4AddressMc    = profile720p->m_ipv4AddressMc;
        idata.profile720p.ipv6AddressMc    = profile720p->m_ipv6AddressMc;
        idata.profile720p.portMc           = profile720p->m_portMc;
        idata.profile720p.ttlMc            = profile720p->m_ttlMc;
        idata.profile720p.autoStartMc      = profile720p->m_autoStartMc;
        idata.profile720p.sessionTimeoutMc = profile720p->m_sessionTimeoutMc;


        QScopedPointer<ONVIF::Profile> profileD1(
            imediaManagement->getProfileD1());
        if (!profileD1)
            return false;
        idata.profileD1.analytics           = profileD1->m_analytics;
        idata.profileD1.toKenPro            = profileD1->m_toKenPro;
        idata.profileD1.fixed               = profileD1->m_fixed;
        idata.profileD1.namePro             = profileD1->m_namePro;
        idata.profileD1.nameVsc             = profileD1->m_nameVsc;
        idata.profileD1.useCountVsc         = profileD1->m_useCountVsc;
        idata.profileD1.sourceTokenVsc      = profileD1->m_sourceTokenVsc;
        idata.profileD1.boundsVsc           = profileD1->m_boundsVsc;
        idata.profileD1.nameVec             = profileD1->m_nameVec;
        idata.profileD1.useCountVec         = profileD1->m_useCountVec;
        idata.profileD1.encodingVec         = profileD1->m_encodingVec;
        idata.profileD1.widthVec            = profileD1->m_widthVec;
        idata.profileD1.heightVec           = profileD1->m_heightVec;
        idata.profileD1.qualityVec          = profileD1->m_qualityVec;
        idata.profileD1.frameRateLimitVec   = profileD1->m_frameRateLimitVec;
        idata.profileD1.encodingIntervalVec = profileD1->m_encodingIntervalVec;
        idata.profileD1.bitrateLimitVec     = profileD1->m_bitrateLimitVec;
        idata.profileD1.govLengthVec        = profileD1->m_govLengthVec;
        idata.profileD1.h264ProfileVec      = profileD1->m_h264ProfileVec;
        idata.profileD1.typeVec             = profileD1->m_typeVec;
        idata.profileD1.ipv4AddressVec      = profileD1->m_ipv4AddressVec;
        idata.profileD1.ipv6AddressVec      = profileD1->m_ipv6AddressVec;
        idata.profileD1.portVec             = profileD1->m_portVec;
        idata.profileD1.ttlVec              = profileD1->m_ttlVec;
        idata.profileD1.autoStartVec        = profileD1->m_autoStartVec;
        idata.profileD1.sessionTimeoutVec   = profileD1->m_sessionTimeoutVec;
        idata.profileD1.namePtz             = profileD1->m_namePtz;
        idata.profileD1.useCountPtz         = profileD1->m_useCountPtz;
        idata.profileD1.nodeToken           = profileD1->m_nodeToken;
        idata.profileD1.defaultAbsolutePantTiltPositionSpace =
            profileD1->m_defaultAbsolutePantTiltPositionSpace;
        idata.profileD1.defaultAbsoluteZoomPositionSpace =
            profileD1->m_defaultAbsoluteZoomPositionSpace;
        idata.profileD1.defaultRelativePantTiltTranslationSpace =
            profileD1->m_defaultRelativePantTiltTranslationSpace;
        idata.profileD1.defaultRelativeZoomTranslationSpace =
            profileD1->m_defaultRelativeZoomTranslationSpace;
        idata.profileD1.defaultContinuousPantTiltVelocitySpace =
            profileD1->m_defaultContinuousPantTiltVelocitySpace;
        idata.profileD1.defaultContinuousZoomVelocitySpace =
            profileD1->m_defaultContinuousZoomVelocitySpace;
        idata.profileD1.panTiltSpace       = profileD1->m_panTiltSpace;
        idata.profileD1.panTiltX           = profileD1->m_panTiltX;
        idata.profileD1.panTiltY           = profileD1->m_panTiltY;
        idata.profileD1.zoomSpace          = profileD1->m_zoomSpace;
        idata.profileD1.zoomX              = profileD1->m_zoomX;
        idata.profileD1.defaultPTZTimeout  = profileD1->m_defaultPTZTimeout;
        idata.profileD1.panTiltUri         = profileD1->m_panTiltUri;
        idata.profileD1.xRangeMinPt        = profileD1->m_xRangeMinPt;
        idata.profileD1.xRangeMaxPt        = profileD1->m_xRangeMaxPt;
        idata.profileD1.yRangeMinPt        = profileD1->m_yRangeMinPt;
        idata.profileD1.yRangeMaxPt        = profileD1->m_yRangeMaxPt;
        idata.profileD1.zoomUri            = profileD1->m_zoomUri;
        idata.profileD1.xRangeMinZm        = profileD1->m_xRangeMinZm;
        idata.profileD1.xRangeMaxZm        = profileD1->m_xRangeMaxZm;
        idata.profileD1.nameMc             = profileD1->m_nameMc;
        idata.profileD1.useCountMc         = profileD1->m_useCountMc;
        idata.profileD1.status             = profileD1->m_status;
        idata.profileD1.position           = profileD1->m_position;
        idata.profileD1.filter             = profileD1->m_filter;
        idata.profileD1.subscriptionPolicy = profileD1->m_subscriptionPolicy;
        idata.profileD1.analytics          = profileD1->m_analytics;
        idata.profileD1.typeMc             = profileD1->m_typeMc;
        idata.profileD1.ipv4AddressMc      = profileD1->m_ipv4AddressMc;
        idata.profileD1.ipv6AddressMc      = profileD1->m_ipv6AddressMc;
        idata.profileD1.portMc             = profileD1->m_portMc;
        idata.profileD1.ttlMc              = profileD1->m_ttlMc;
        idata.profileD1.autoStartMc        = profileD1->m_autoStartMc;
        idata.profileD1.sessionTimeoutMc   = profileD1->m_sessionTimeoutMc;

        return true;
    }

    bool refreshInterfaces() {
        QScopedPointer<ONVIF::NetworkInterfaces> networkInterfaces(
            ideviceManagement->getNetworkInterfaces());
        if (!networkInterfaces)
            return false;
        idata.network.interfaces.networkInfacesEnabled =
            networkInterfaces->networkInfacesEnabled();
        idata.network.interfaces.autoNegotiation =
            networkInterfaces->autoNegotiation();
        idata.network.interfaces.speed = networkInterfaces->speed();
        idata.network.interfaces.duplex =
            static_cast<Data::Network::Interfaces::Duplex>(
                static_cast<int>(networkInterfaces->duplex()));

        idata.network.interfaces.mtu         = networkInterfaces->mtu();
        idata.network.interfaces.ipv4Enabled = networkInterfaces->ipv4Enabled();
        idata.network.interfaces.ipv4ManualAddress =
            networkInterfaces->ipv4ManualAddress();
        idata.network.interfaces.ipv4ManualPrefixLength =
            networkInterfaces->ipv4ManualPrefixLength();
        idata.network.interfaces.ipv4DHCP = networkInterfaces->getIpv4DHCP();
        idata.network.interfaces.networkInfacesName =
            networkInterfaces->networkInfacesName();
        idata.network.interfaces.hwAaddress = networkInterfaces->hwAaddress();
        idata.network.interfaces.ipv4LinkLocalAddress =
            networkInterfaces->ipv4LinkLocalAddress();
        idata.network.interfaces.ipvLinkLocalPrefixLength =
            networkInterfaces->ipvLinkLocalPrefixLength();
        idata.network.interfaces.ipv4FromDHCPAddress =
            networkInterfaces->ipv4FromDHCPAddress();
        idata.network.interfaces.ipv4FromDHCPPrefixLength =
            networkInterfaces->ipv4FromDHCPPrefixLength();
        idata.network.interfaces.result = networkInterfaces->result();

        return true;
    }

    bool refreshUsers() {
        QScopedPointer<ONVIF::Users> users(ideviceManagement->getUsers());
        if (!users)
            return false;
        idata.users.username  = users->userName();
        idata.users.password  = users->passWord();
        idata.users.userLevel = static_cast<Data::Users::UserLevelType>(
            static_cast<int>(users->userLevel()));

        return true;
    }
};

// QOnvifDevice::QOnvifDevice() {}

QOnvifDevice::QOnvifDevice(
    QString  _serviceAddress,
    QString  _userName,
    QString  _password,
    QObject* _parent)
    : d_ptr{new QOnvifDevicePrivate{_serviceAddress, _userName, _password}},
      QObject(_parent) {}

QOnvifDevice::~QOnvifDevice() {}

Data&
QOnvifDevice::data() {
    return d_ptr->idata;
}

bool
QOnvifDevice::deviceDateAndTime(Data::DateTime& _datetime) {
    return d_ptr->deviceDateAndTime(_datetime);
}

void
QOnvifDevice::setDeviceProbeData(Data::ProbeData _probeData) {
    d_ptr->setDeviceProbeData(_probeData);
}

bool
QOnvifDevice::setScopes(QString _name, QString _location) {
    return d_ptr->setScopes(_name, _location);
}

bool
QOnvifDevice::setDateAndTime(QDateTime _dateAndTime) {
    return d_ptr->setDeviceDateAndTime(_dateAndTime);
}

bool
QOnvifDevice::refreshDeviceCapabilities() {
    return d_ptr->refreshDeviceCapabilities();
}

bool
QOnvifDevice::refreshDeviceInformation() {
    return d_ptr->refreshDeviceInformation();
}

bool
QOnvifDevice::refreshDeviceScopes() {
    return d_ptr->refreshDeviceScopes();
}

bool
QOnvifDevice::resetFactoryDevice() {
    return d_ptr->resetFactoryDevice();
}

bool
QOnvifDevice::rebootDevice() {
    return d_ptr->rebootDevice();
}

bool
QOnvifDevice::refreshVideoConfigs() {
    return d_ptr->refreshVideoConfigs();
}

bool
QOnvifDevice::refreshVideoConfigsOptions(
    QString _configToken, QString _profileToken) {
    return d_ptr->refreshVideoConfigsOptions(_configToken, _profileToken);
}

bool
QOnvifDevice::refreshAudioConfigs() {
    return d_ptr->refreshAudioConfigs();
}

bool
QOnvifDevice::refreshProfiles() {
    return d_ptr->refreshProfiles();
}

bool
QOnvifDevice::refreshInterfaces() {
    return d_ptr->refreshInterfaces();
}

bool
QOnvifDevice::refreshUsers() {
    return d_ptr->refreshUsers();
}

///////////////////////////////////////////////////////////////////////////////
} // namespace device
///////////////////////////////////////////////////////////////////////////////
