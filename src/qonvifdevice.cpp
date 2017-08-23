#include "qonvifdevice.hpp"
#include "devicemanagement.h"
#include "mediamanagement.h"
#include "ptzmanagement.h"
#include <QString>

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

        iptzManagement =
            new ONVIF::PtzManagement{_serviceAddress, iuserName, ipassword};
    }
    ~QOnvifDevicePrivate() {
        delete ideviceManagement;
        delete imediaManagement;
        delete iptzManagement;
    }

    QString iuserName;
    QString ipassword;
    Data    idata;

    // onvif managers
    ONVIF::DeviceManagement* ideviceManagement;
    ONVIF::MediaManagement*  imediaManagement;
    ONVIF::PtzManagement*    iptzManagement;
};

// QOnvifDevice::QOnvifDevice() {}

QOnvifDevice::QOnvifDevice(
    QString  _serviceAddress,
    QString  _userName,
    QString  _password,
    QObject* _parent)
    : d_ptr{new QOnvifDevicePrivate{_serviceAddress, _userName, _password}},
      QObject(_parent){

    connect(d_ptr->ideviceManagement,&ONVIF::DeviceManagement::resultReceived,this,[this](QVariant var, MessageType messageType){

        switch (messageType) {
        case MessageType::DeviceInformation :
        {
            QHash<QString, QString> deviceInformationHash = var.value<QHash<QString, QString> >();
            d_ptr->idata.information.manufacturer = deviceInformationHash.value("mf");
            d_ptr->idata.information.model        = deviceInformationHash.value("model");
            d_ptr->idata.information.firmwareVersion =
                deviceInformationHash.value("firmware_version");
            d_ptr->idata.information.serialNumber =
                deviceInformationHash.value("serial_number");
            d_ptr->idata.information.hardwareId =
                deviceInformationHash.value("hardware_id");

            emit deviceInformationReceived(d_ptr->idata.information);
        }
            break;
        case MessageType::DeviceScopes :
        {
            QHash<QString, QString> deviceScopesHash = var.value<QHash<QString, QString> >();
            d_ptr->idata.scopes.name     = deviceScopesHash.value("name");
            d_ptr->idata.scopes.location = deviceScopesHash.value("location");
            d_ptr->idata.scopes.hardware = deviceScopesHash.value("hardware");

            emit deviceScopesReceived(d_ptr->idata.scopes);
        }
            break;
        case MessageType::SystemDateAndTime :
        {
            QScopedPointer<ONVIF::SystemDateAndTime> systemDateAndTime(ONVIF::VPtr<ONVIF::SystemDateAndTime>::asPtr(var));

            d_ptr->idata.dateTime.localTime      = systemDateAndTime->localTime();
            d_ptr->idata.dateTime.utcTime        = systemDateAndTime->utcTime();
            d_ptr->idata.dateTime.timeZone       = systemDateAndTime->tz();
            d_ptr->idata.dateTime.daylightSaving = systemDateAndTime->daylightSavings();

            emit systemDateAndTimeReceived(d_ptr->idata.dateTime);
        }
            break;
        case MessageType::Users :
        {
            QScopedPointer<ONVIF::Users> users(ONVIF::VPtr<ONVIF::Users>::asPtr(var));

            d_ptr->idata.users.clear();
            for (int i = 0; i < users->userNames().length(); i++) {
                Data::User user;
                user.username  = users->userNames().value(i);
                user.password  = users->passWord().value(i);
                user.userLevel = users->userLevel().value(i);
                d_ptr->idata.users.append(user);
            }

            emit usersReceived(d_ptr->idata.users);
        }
            break;
        case MessageType::Capabilities :
        {
            QScopedPointer<ONVIF::Capabilities> capabilities(ONVIF::VPtr<ONVIF::Capabilities>::asPtr(var));

            auto& src = capabilities;
            auto& des = d_ptr->idata.capabilities;

            // device capabilities
            des.accessPolicyConfig     = src->accessPolicyConfig();
            des.deviceXAddr            = src->deviceXAddr();
            des.iPFilter               = src->iPFilter();
            des.zeroConfiguration      = src->zeroConfiguration();
            des.iPVersion6             = src->iPVersion6();
            des.dynDNS                 = src->dynDNS();
            des.discoveryResolve       = src->discoveryResolve();
            des.systemLogging          = src->systemLogging();
            des.firmwareUpgrade        = src->firmwareUpgrade();
            des.major                  = src->major();
            des.minor                  = src->minor();
            des.httpFirmwareUpgrade    = src->httpFirmwareUpgrade();
            des.httpSystemBackup       = src->httpSystemBackup();
            des.httpSystemLogging      = src->httpSystemLogging();
            des.httpSupportInformation = src->httpSupportInformation();
            des.inputConnectors        = src->inputConnectors();
            des.relayOutputs           = src->relayOutputs();
            des.tls11                  = src->tls11();
            des.tls22                  = src->tls22();
            des.onboardKeyGeneration   = src->onboardKeyGeneration();
            des.accessPolicyConfig     = src->accessPolicyConfig();
            des.x509Token              = src->x509Token();
            des.samlToken              = src->samlToken();
            des.kerberosToken          = src->kerberosToken();
            des.relToken               = src->relToken();
            des.tls10                  = src->tls10();
            des.dot1x                  = src->dot1x();
            des.remoteUserHanding      = src->remoteUserHanding();
            des.systemBackup           = src->systemBackup();
            des.discoveryBye           = src->discoveryBye();
            des.remoteDiscovery        = src->remoteDiscovery();

            // ptz capabilities
            des.ptzAddress = capabilities->ptzXAddr();

            // image capabilities
             des.imagingXAddress = capabilities->imagingXAddr();

            // media capabilities
             des.mediaXAddress = capabilities->mediaXAddr();
             des.rtpMulticast  = capabilities->rtpMulticast();
             des.rtpTcp        = capabilities->rtpTcp();
             des.rtpRtspTcp    = capabilities->rtpRtspTcp();

            emit capabilitiesReceived(d_ptr->idata.capabilities);
        }
            break;
        case MessageType::NetworkInterfaces :
        {
            QScopedPointer<ONVIF::NetworkInterfaces> networkInterfaces(ONVIF::VPtr<ONVIF::NetworkInterfaces>::asPtr(var));

            auto& des = d_ptr->idata.network.interfaces;
            auto& src = networkInterfaces;

            des.networkInfacesEnabled    = src->networkInfacesEnabled();
            des.autoNegotiation          = src->autoNegotiation();
            des.speed                    = src->speed();
            des.mtu                      = src->mtu();
            des.ipv4Enabled              = src->ipv4Enabled();
            des.ipv4ManualAddress        = src->ipv4ManualAddress();
            des.ipv4ManualPrefixLength   = src->ipv4ManualPrefixLength();
            des.ipv4DHCP                 = src->ipv4DHCP();
            des.networkInfacesName       = src->networkInfacesName();
            des.hwAaddress               = src->hwAaddress();
            des.ipv4LinkLocalAddress     = src->ipv4LinkLocalAddress();
            des.ipvLinkLocalPrefixLength = src->ipvLinkLocalPrefixLength();
            des.ipv4FromDHCPAddress      = src->ipv4FromDHCPAddress();
            des.ipv4FromDHCPPrefixLength = src->ipv4FromDHCPPrefixLength();
            des.interfaceToken           = src->interfaceToken();
            des.result                   = src->result();
            des.duplexFull = src->duplex() == ONVIF::NetworkInterfaces::Duplex::Full
                                 ? true
                                 : false;

            emit networkInterfacesReceived(d_ptr->idata.network.interfaces);
        }
            break;
        case MessageType::NetworkProtocols :
        {
            QScopedPointer<ONVIF::NetworkProtocols> networkProtocols(ONVIF::VPtr<ONVIF::NetworkProtocols>::asPtr(var));

            auto& des = d_ptr->idata.network.protocols;
            auto& src = networkProtocols;

            des.networkProtocolsEnabled = src->getNetworkProtocolsEnabled();
            des.networkProtocolsName    = src->getNetworkProtocolsName();
            des.networkProtocolsPort    = src->getNetworkProtocolsPort();

            emit networkProtocolsReceived(d_ptr->idata.network.protocols);
        }
            break;
        case MessageType::NetworkDefaultGateway :
        {
            QScopedPointer<ONVIF::NetworkDefaultGateway> networkDefaultGateway(ONVIF::VPtr<ONVIF::NetworkDefaultGateway>::asPtr(var));

            auto& des = d_ptr->idata.network.defaultGateway;
            auto& src = networkDefaultGateway;

            des.ipv4Address = src->ipv4Address();
            des.ipv6Address = src->ipv6Address();

            emit networkDefaultGatewayReceived(d_ptr->idata.network.defaultGateway);
        }
            break;
        case MessageType::NetworkDiscoveryMode :
        {
            QScopedPointer<ONVIF::NetworkDiscoveryMode> networkDiscoveryMode(ONVIF::VPtr<ONVIF::NetworkDiscoveryMode>::asPtr(var));

            auto& des = d_ptr->idata.network.discoveryMode;
            auto& src = networkDiscoveryMode;

            des.discoveryMode = src->discoveryMode();

            emit networkDiscoveryModeReceived(d_ptr->idata.network.discoveryMode);
        }
            break;
        case MessageType::NetworkDNS :
        {
            QScopedPointer<ONVIF::NetworkDNS> networkDNS(ONVIF::VPtr<ONVIF::NetworkDNS>::asPtr(var));

            auto& des = d_ptr->idata.network.dns;
            auto& src = networkDNS;

            des.dhcp         = src->dhcp();
            des.ipv4Address  = src->ipv4Address();
            des.manualType   = src->manualType();
            des.searchDomain = src->searchDomain();

            emit networkDNSReceived(d_ptr->idata.network.dns);
        }
            break;
        case MessageType::NetworkHostname :
        {
            QScopedPointer<ONVIF::NetworkHostname> networkHostname(ONVIF::VPtr<ONVIF::NetworkHostname>::asPtr(var));

            auto& des = d_ptr->idata.network.hostname;
            auto& src = networkHostname;

            des.dhcp = src->dhcp();
            des.name = src->name();

            emit networkHostnameReceived(d_ptr->idata.network.hostname);
        }
            break;
        case MessageType::NetworkNTP :
        {
            QScopedPointer<ONVIF::NetworkNTP> networkNTP(ONVIF::VPtr<ONVIF::NetworkNTP>::asPtr(var));

            auto& des = d_ptr->idata.network.ntp;
            auto& src = networkNTP;

            des.dhcp        = src->dhcp();
            des.ipv4Address = src->ipv4Address();
            des.ipv6Address = src->ipv6Address();
            des.manualType  = src->manualType();

            emit networkNTPReceived(d_ptr->idata.network.ntp);
        }
            break;
        case MessageType::SetDeviceScopes :
        case MessageType::SetSystemDateAndTime :
        case MessageType::SetUsers :
        case MessageType::SetSystemFactoryDefault :
        case MessageType::SetSystemReboot :
        case MessageType::SetNetworkInterfaces :
        case MessageType::SetNetworkProtocols :
        case MessageType::SetNetworkDefaultGateway :
        case MessageType::SetNetworkDiscoveryMode :
        case MessageType::SetNetworkDNS :
        case MessageType::SetNetworkHostname :
        case MessageType::SetNetworkNTP :
        {
            bool r = var.value<bool>();
            emit setResultReceived(r, messageType);
        }
            break;
        default:
            break;
        }
    });
}

QOnvifDevice::~QOnvifDevice() {}

Data&
QOnvifDevice::data() {
    return d_ptr->idata;
}

void
QOnvifDevice::getDeviceInformation() {
    d_ptr->ideviceManagement->getData(MessageType::DeviceInformation);
}

void
QOnvifDevice::getDeviceScopes() {
    d_ptr->ideviceManagement->getData(MessageType::DeviceScopes);
}

void
QOnvifDevice::getDeviceDateAndTime() {
    d_ptr->ideviceManagement->getData(MessageType::SystemDateAndTime);
}

void
QOnvifDevice::getUsers() {
    d_ptr->ideviceManagement->getData(MessageType::Users);
}

void
QOnvifDevice::getDeviceCapabilities() {
    d_ptr->ideviceManagement->getData(MessageType::Capabilities);
}

void
QOnvifDevice::getInterfaces() {
    d_ptr->ideviceManagement->getData(MessageType::NetworkInterfaces);
}
void
QOnvifDevice::getProtocols() {
    d_ptr->ideviceManagement->getData(MessageType::NetworkProtocols);
}

void
QOnvifDevice::getDefaultGateway() {
    d_ptr->ideviceManagement->getData(MessageType::NetworkDefaultGateway);
}

void
QOnvifDevice::getDiscoveryMode() {
    d_ptr->ideviceManagement->getData(MessageType::NetworkDiscoveryMode);
}

void
QOnvifDevice::getDNS() {
    d_ptr->ideviceManagement->getData(MessageType::NetworkDNS);
}

void
QOnvifDevice::getHostname() {
    d_ptr->ideviceManagement->getData(MessageType::NetworkHostname);
}

void
QOnvifDevice::getNTP() {
    d_ptr->ideviceManagement->getData(MessageType::NetworkNTP);
}

void
QOnvifDevice::setDeviceProbeData(Data::ProbeData _probeData) {
    d_ptr->idata.probeData = _probeData;
}

void
QOnvifDevice::setScopes(QString _name, QString _location) {
    ONVIF::SystemScopes systemScopes;
    systemScopes.setScopes(_name, _location);
    d_ptr->ideviceManagement->setData(
                ONVIF::VPtr<ONVIF::SystemScopes>::asQVariant(&systemScopes),
                MessageType::SetDeviceScopes);
}

void
QOnvifDevice::setDateAndTime(
        QDateTime _dateAndTime,
        QString   _zone,
        bool      _daylightSaving,
        bool      _isLocal) {
    ONVIF::SystemDateAndTime systemDateAndTime;
    systemDateAndTime.setIsLocal(_isLocal);
    if (_isLocal) {
        systemDateAndTime.setlocalTime(_dateAndTime);
    } else {
        systemDateAndTime.setutcTime(_dateAndTime);
    }
    systemDateAndTime.setTz(_zone);
    systemDateAndTime.setDaylightSavings(_daylightSaving);
    d_ptr->ideviceManagement->setData(
                ONVIF::VPtr<ONVIF::SystemDateAndTime>::asQVariant(&systemDateAndTime),
                MessageType::SetSystemDateAndTime);
}

void
QOnvifDevice::setUsers(Data::Users _users) {
    ONVIF::Users users;
    for (int i = 0; i < _users.length(); i++) {
        users.setUserNames(_users[i].username);
        users.setPassWords(_users[i].password);
        users.setUserLevel(_users[i].userLevel);
        users.setIsAddMode(_users[i].isAddMode);
    }
    d_ptr->ideviceManagement->setData(
                ONVIF::VPtr<ONVIF::Users>::asQVariant(&users),
                MessageType::SetUsers);
}

void
QOnvifDevice::setNetworkInterfaces(Data::Network::Interfaces _interfaces) {
    ONVIF::NetworkInterfaces networkInterface;
    auto&                    des = networkInterface;
    des.setAutoNegotiation(_interfaces.autoNegotiation);
    des.setDuplex(
        _interfaces.duplexFull ? ONVIF::NetworkInterfaces::Duplex::Full
                              : ONVIF::NetworkInterfaces::Duplex::Half);

    des.setHwAaddress(_interfaces.hwAaddress);
    des.setIpv4DHCP(_interfaces.ipv4DHCP);
    des.setIpv4Enabled(_interfaces.ipv4Enabled);
    des.setIpv4FromDHCPAddress(_interfaces.ipv4FromDHCPAddress);
    des.setIpv4FromDHCPPrefixLength(_interfaces.ipv4FromDHCPPrefixLength);
    des.setIpv4LinkLocalAddress(_interfaces.ipv4LinkLocalAddress);
    des.setIpv4ManualAddress(_interfaces.ipv4ManualAddress);
    des.setIpv4ManualPrefixLength(_interfaces.ipv4ManualPrefixLength);
    des.setIpvLinkLocalPrefixLength(_interfaces.ipvLinkLocalPrefixLength);
    des.setMtu(_interfaces.mtu);
    des.setNetworkInfacesEnabled(_interfaces.networkInfacesEnabled);
    des.setNetworkInfacesName(_interfaces.networkInfacesName);
    des.setSpeed(_interfaces.speed);
    des.setInterfaceToken(_interfaces.interfaceToken);
    d_ptr->ideviceManagement->setData(
                ONVIF::VPtr<ONVIF::NetworkInterfaces>::asQVariant(&networkInterface),
                MessageType::SetNetworkInterfaces);
}

void
QOnvifDevice::setNetworkProtocols(Data::Network::Protocols _protocols) {
    ONVIF::NetworkProtocols networkProtocols;
    auto& des = networkProtocols;
    for (int i = 0; i < _protocols.networkProtocolsName.length(); i++) {
        des.setNetworkProtocolsEnabled(
            _protocols.networkProtocolsEnabled[i]);
        des.setNetworkProtocolsPort(_protocols.networkProtocolsPort[i]);
        des.setNetworkProtocolsName(_protocols.networkProtocolsName[i]);
    }
    d_ptr->ideviceManagement->setData(
                ONVIF::VPtr<ONVIF::NetworkProtocols>::asQVariant(&networkProtocols),
                MessageType::SetNetworkProtocols);
}

void
QOnvifDevice::setNetworkDefaultGateway(Data::Network::DefaultGateway _defaultGateway) {
    ONVIF::NetworkDefaultGateway networkDefaultGateway;
    networkDefaultGateway.setIpv4Address(_defaultGateway.ipv4Address);
    d_ptr->ideviceManagement->setData(
                ONVIF::VPtr<ONVIF::NetworkDefaultGateway>::asQVariant(&networkDefaultGateway),
                MessageType::SetNetworkDefaultGateway);
}

void
QOnvifDevice::setNetworkDiscoveryMode(Data::Network::DiscoveryMode _discoveryMode) {
    ONVIF::NetworkDiscoveryMode networkDiscoveryMode;
    networkDiscoveryMode.setDiscoveryMode(_discoveryMode.discoveryMode);
    d_ptr->ideviceManagement->setData(
                ONVIF::VPtr<ONVIF::NetworkDiscoveryMode>::asQVariant(&networkDiscoveryMode),
                MessageType::SetNetworkDiscoveryMode);
}

void
QOnvifDevice::setNetworkDNS(Data::Network::DNS _dns) {
    ONVIF::NetworkDNS networkDNS;
    networkDNS.setDhcp(_dns.dhcp);
    foreach (QString ipAddress, _dns.ipv4Address)
        networkDNS.setIpv4Address(ipAddress);
    foreach (QString manualType, _dns.manualType)
        networkDNS.setManualType(manualType);
    networkDNS.setSearchDomain(_dns.searchDomain);
    d_ptr->ideviceManagement->setData(
                ONVIF::VPtr<ONVIF::NetworkDNS>::asQVariant(&networkDNS),
                MessageType::SetNetworkDNS);
}

void
QOnvifDevice::setNetworkHostname(Data::Network::Hostname _hostname) {
    ONVIF::NetworkHostname networkHostname;
    networkHostname.setDhcp(_hostname.dhcp);
    networkHostname.setName(_hostname.name);
    d_ptr->ideviceManagement->setData(
                ONVIF::VPtr<ONVIF::NetworkHostname>::asQVariant(&networkHostname),
                MessageType::SetNetworkHostname);
}

void
QOnvifDevice::setNetworkNTP(Data::Network::NTP _ntp) {
    ONVIF::NetworkNTP networkNTP;
    networkNTP.setDhcp(_ntp.dhcp);
    networkNTP.setIpv4Address(_ntp.ipv4Address);
    networkNTP.setManualType(_ntp.ipv6Address);
    d_ptr->ideviceManagement->setData(
                ONVIF::VPtr<ONVIF::NetworkNTP>::asQVariant(&networkNTP),
                MessageType::SetNetworkNTP);
}

void
QOnvifDevice::resetFactoryDevice(bool isHard) {
    ONVIF::SystemFactoryDefault systemFactoryDefault;
    systemFactoryDefault.setFactoryDefault(
        isHard ? ONVIF::SystemFactoryDefault::Hard
               : ONVIF::SystemFactoryDefault::Soft);
    d_ptr->ideviceManagement->setData(
                ONVIF::VPtr<ONVIF::SystemFactoryDefault>::asQVariant(&systemFactoryDefault),
                MessageType::SetSystemFactoryDefault);
}

void
QOnvifDevice::rebootDevice() {
    ONVIF::SystemReboot systemReboot;
    d_ptr->ideviceManagement->setData(
                ONVIF::VPtr<ONVIF::SystemReboot>::asQVariant(&systemReboot),
                MessageType::SetSystemReboot);
}

bool
QOnvifDevice::setVideoConfig(
    Data::MediaConfig::Video::EncoderConfig _videoConfig) {
    ONVIF::VideoEncoderConfiguration videoConfiguration;
    videoConfiguration.setToken(_videoConfig.token);
    videoConfiguration.setName(_videoConfig.name);
    videoConfiguration.setUseCount(_videoConfig.useCount);
    videoConfiguration.setEncoding(_videoConfig.encoding);
    videoConfiguration.setWidth(_videoConfig.width);
    videoConfiguration.setHeight(_videoConfig.height);
    videoConfiguration.setQuality(_videoConfig.quality);
    videoConfiguration.setFrameRateLimit(_videoConfig.frameRateLimit);
    videoConfiguration.setEncodingInterval(_videoConfig.encodingInterval);
    videoConfiguration.setBitrateLimit(_videoConfig.bitrateLimit);
    videoConfiguration.setGovLength(_videoConfig.govLength);
    videoConfiguration.setH264Profile(_videoConfig.h264Profile);
    videoConfiguration.setType(_videoConfig.type);
    videoConfiguration.setIpv4Address(_videoConfig.ipv4Address);
    videoConfiguration.setPort(_videoConfig.port);
    videoConfiguration.setTtl(_videoConfig.ttl);
    videoConfiguration.setAutoStart(_videoConfig.autoStart);
    videoConfiguration.setSessionTimeout(_videoConfig.sessionTimeout);
    d_ptr->imediaManagement->setVideoEncoderConfiguration(&videoConfiguration);
    return videoConfiguration.result();
}

bool
QOnvifDevice::setDeviceImageSetting(
    Data::MediaConfig::ImageSetting _imageSetting) {
    ONVIF::ImageSetting imageSetting;
    imageSetting.setAutofocusManual(_imageSetting.autofocusManual);
    imageSetting.setBrightness(_imageSetting.brightness);
    imageSetting.setColorSaturation(_imageSetting.colorSaturation);
    imageSetting.setContrast(_imageSetting.contrast);
    imageSetting.setDefaultSpeed(_imageSetting.defaultSpeed);
    imageSetting.setExposureIris(_imageSetting.exposureIris);
    imageSetting.setExposureManual(_imageSetting.exposureManual);
    imageSetting.setForcePersistence(_imageSetting.forcePersistence);
    imageSetting.setSharpness(_imageSetting.sharpness);
    imageSetting.setToken(_imageSetting.token);
    d_ptr->imediaManagement->setImageSettings(&imageSetting);
    return imageSetting.result();
}

bool
QOnvifDevice::refreshVideoConfigs() {
    bool result = true;

    // get video encoder config
    QScopedPointer<ONVIF::VideoEncoderConfigurations>
        videoEncoderConfigurations(
            d_ptr->imediaManagement->getVideoEncoderConfigurations());
    if (videoEncoderConfigurations)
    {
        auto& des = d_ptr->idata.mediaConfig.video.encodingConfigs;
        auto& src = videoEncoderConfigurations;

        des.autoStart        = src->getAutoStart();
        des.bitrateLimit     = src->getBitrateLimit();
        des.encoding         = src->getEncoding();
        des.encodingInterval = src->getEncodingInterval();
        des.frameRateLimit   = src->getFrameRateLimit();
        des.govLength        = src->getGovLength();
        des.h264Profile      = src->getH264Profile();
        des.width            = src->getWidth();
        des.height           = src->getHeight();
        des.ipv4Address      = src->getIpv4Address();
        des.ipv6Address      = src->getIpv6Address();
        des.name             = src->getName();
        des.port             = src->getPort();
        des.quality          = src->getQuality();
        des.sessionTimeout   = src->getSessionTimeout();
        des.token            = src->getToken();
        des.ttl              = src->getTtl();
        des.type             = src->getType();
        des.useCount         = src->getUseCount();

        // get video source config
        QScopedPointer<ONVIF::VideoSourceConfigurations>
                videoSourceConfigurations(
                    d_ptr->imediaManagement->getVideoSourceConfigurations());

        if (videoSourceConfigurations)
        {
            auto& des       = d_ptr->idata.mediaConfig.video.sourceConfig;
            auto& src       = videoSourceConfigurations;
            des.name        = src->getName();
            des.useCount    = src->getUseCount();
            des.sourceToken = src->getSourceToken();
            des.bounds      = src->getBounds();
        }
        else
            result = false;
    }
    else
        result = false;


    refreshVideoConfigsOptions();
    return result;
}

bool
QOnvifDevice::refreshVideoConfigsOptions() {
    d_ptr->idata.mediaConfig.video.encodingConfigs.options.clear();

    // get video encoder options
    auto configToken  = d_ptr->idata.mediaConfig.video.encodingConfigs.token;
    auto profileToken = d_ptr->idata.profiles.toKenPro;
    auto size         = qMin(configToken.length(), profileToken.length());
    for (int i = 0; i < size; i++) {

        QScopedPointer<ONVIF::VideoEncoderConfigurationOptions>
            videoEncoderConfigurationOptions(
                d_ptr->imediaManagement->getVideoEncoderConfigurationOptions(
                    configToken[i], profileToken[i]));

        if (!videoEncoderConfigurationOptions)
            return false;

        Data::MediaConfig::Video::EncoderConfigs::Option encodingOptions;

        auto& des = encodingOptions;
        auto& src = videoEncoderConfigurationOptions;

        des.encodingIntervalRangeMaxH264 =
            src->encodingIntervalRangeMaxH264();
        des.encodingIntervalRangeMinH264 =
            src->encodingIntervalRangeMinH264();
        des.frameRateRangeMaxH264  = src->frameRateRangeMaxH264();
        des.frameRateRangeMinH264  = src->frameRateRangeMinH264();
        des.bitRateRangeMax        = src->bitRateRangeMax();
        des.bitRateRangeMin        = src->bitRateRangeMin();
        des.govLengthRangeMax      = src->govLengthRangeMax();
        des.govLengthRangeMin      = src->govLengthRangeMin();
        des.qualityRangeMin        = src->qualityRangeMin();
        des.qualityRangeMax        = src->qulityRangeMax();
        des.resAvailableHeightH264 = src->resAvailableHeightH264();
        des.resAvailableWidthH264  = src->resAvailableWidthH264();
        des.encodingIntervalRangeMaxJpeg =
            src->encodingIntervalRangeMaxJpeg();
        des.encodingIntervalRangeMinJpeg =
            src->encodingIntervalRangeMinJpeg();
        des.frameRateRangeMaxJpeg  = src->frameRateRangeMaxJpeg();
        des.frameRateRangeMinJpeg  = src->frameRateRangeMinJpeg();
        des.resAvailableHeightJpeg = src->resAvailableHeightJpeg();
        des.resAvailableWidthJpeg  = src->resAvailableWidthJpeg();

        foreach (
            ONVIF::VideoEncoderConfigurationOptions::H264ProfilesSupported
                h264ProfilesSupporte,
            src->getH264ProfilesSupported()) {
            int intCastTemp = static_cast<int>(h264ProfilesSupporte);

            Data::MediaConfig::Video::EncoderConfigs::Option::
                H264ProfilesSupported enumCastTemp =
                    static_cast<Data::MediaConfig::Video::EncoderConfigs::
                                    Option::H264ProfilesSupported>(
                        intCastTemp);

            des.h264ProfilesSupported.append(enumCastTemp);
        }
        d_ptr->idata.mediaConfig.video.encodingConfigs.options.append(des);
    }

    return true;
}

bool
QOnvifDevice::refreshStreamUris() {
    // get video stream uri
    d_ptr->idata.profiles.streamUris.clear();
    for (int i = 0; i < d_ptr->idata.profiles.toKenPro.length(); i++) {
        QScopedPointer<ONVIF::StreamUri> streamUri(
            d_ptr->imediaManagement->getStreamUri(
                d_ptr->idata.profiles.toKenPro.value(i)));
        if (!streamUri)
            return false;
        Data::MediaConfig::Video::StreamUri streamUriTemp;
        streamUriTemp.uri = streamUri->uri();
        streamUriTemp.invalidAfterConnect =
            streamUri->invalidAfterConnect();
        streamUriTemp.invalidAfterReboot = streamUri->invalidAfterReboot();
        streamUriTemp.timeout            = streamUri->timeout();

        if (i == 0) {
            d_ptr->idata.mediaConfig.video.streamUri = streamUriTemp;
        }
        d_ptr->idata.profiles.streamUris.append(streamUriTemp);
    }
    return true;
}

bool
QOnvifDevice::refreshAudioConfigs() {
    // todo: add giving audio options of cameras
    d_ptr->imediaManagement->getAudioEncoderConfigurationOptions();
    d_ptr->imediaManagement->getAudioEncoderConfigurations();
    d_ptr->imediaManagement->getAudioSourceConfigurations();
    return true;
}

bool
QOnvifDevice::refreshProfiles() {
    QScopedPointer<ONVIF::Profiles> profiles(
        d_ptr->imediaManagement->getProfiles());
    if (!profiles)
        return false;
    {
        auto& des = d_ptr->idata.profiles;

        des.analytics           = profiles->m_analytics;
        des.toKenPro            = profiles->m_toKenPro;
        des.fixed               = profiles->m_fixed;
        des.namePro             = profiles->m_namePro;
        des.nameVsc             = profiles->m_nameVsc;
        des.useCountVsc         = profiles->m_useCountVsc;
        des.sourceTokenVsc      = profiles->m_sourceTokenVsc;
        des.boundsVsc           = profiles->m_boundsVsc;
        des.nameVec             = profiles->m_nameVec;
        des.useCountVec         = profiles->m_useCountVec;
        des.encodingVec         = profiles->m_encodingVec;
        des.widthVec            = profiles->m_widthVec;
        des.heightVec           = profiles->m_heightVec;
        des.qualityVec          = profiles->m_qualityVec;
        des.frameRateLimitVec   = profiles->m_frameRateLimitVec;
        des.encodingIntervalVec = profiles->m_encodingIntervalVec;
        des.bitrateLimitVec     = profiles->m_bitrateLimitVec;
        des.govLengthVec        = profiles->m_govLengthVec;
        des.h264ProfileVec      = profiles->m_h264ProfileVec;
        des.typeVec             = profiles->m_typeVec;
        des.ipv4AddressVec      = profiles->m_ipv4AddressVec;
        des.ipv6AddressVec      = profiles->m_ipv6AddressVec;
        des.portVec             = profiles->m_portVec;
        des.ttlVec              = profiles->m_ttlVec;
        des.autoStartVec        = profiles->m_autoStartVec;
        des.sessionTimeoutVec   = profiles->m_sessionTimeoutVec;
        des.namePtz             = profiles->m_namePtz;
        des.useCountPtz         = profiles->m_useCountPtz;
        des.nodeToken           = profiles->m_nodeToken;
        des.panTiltSpace        = profiles->m_panTiltSpace;
        des.panTiltX            = profiles->m_panTiltX;
        des.panTiltY            = profiles->m_panTiltY;
        des.zoomSpace           = profiles->m_zoomSpace;
        des.zoomX               = profiles->m_zoomX;
        des.defaultPTZTimeout   = profiles->m_defaultPTZTimeout;
        des.panTiltUri          = profiles->m_panTiltUri;
        des.xRangeMinPt         = profiles->m_xRangeMinPt;
        des.xRangeMaxPt         = profiles->m_xRangeMaxPt;
        des.yRangeMinPt         = profiles->m_yRangeMinPt;
        des.yRangeMaxPt         = profiles->m_yRangeMaxPt;
        des.zoomUri             = profiles->m_zoomUri;
        des.xRangeMinZm         = profiles->m_xRangeMinZm;
        des.xRangeMaxZm         = profiles->m_xRangeMaxZm;
        des.nameMc              = profiles->m_nameMc;
        des.useCountMc          = profiles->m_useCountMc;
        des.status              = profiles->m_status;
        des.position            = profiles->m_position;
        des.filter              = profiles->m_filter;
        des.subscriptionPolicy  = profiles->m_subscriptionPolicy;
        des.analytics           = profiles->m_analytics;
        des.typeMc              = profiles->m_typeMc;
        des.ipv4AddressMc       = profiles->m_ipv4AddressMc;
        des.ipv6AddressMc       = profiles->m_ipv6AddressMc;
        des.portMc              = profiles->m_portMc;
        des.ttlMc               = profiles->m_ttlMc;
        des.autoStartMc         = profiles->m_autoStartMc;
        des.sessionTimeoutMc    = profiles->m_sessionTimeoutMc;
        des.defaultAbsolutePantTiltPositionSpace =
            profiles->m_defaultAbsolutePantTiltPositionSpace;
        des.defaultAbsoluteZoomPositionSpace =
            profiles->m_defaultAbsoluteZoomPositionSpace;
        des.defaultRelativePantTiltTranslationSpace =
            profiles->m_defaultRelativePantTiltTranslationSpace;
        des.defaultRelativeZoomTranslationSpace =
            profiles->m_defaultRelativeZoomTranslationSpace;
        des.defaultContinuousPantTiltVelocitySpace =
            profiles->m_defaultContinuousPantTiltVelocitySpace;
        des.defaultContinuousZoomVelocitySpace =
            profiles->m_defaultContinuousZoomVelocitySpace;
    }
    return true;
    // todo whats this other profiles (cameras never filled them in tests
    // yet)
    QScopedPointer<ONVIF::Profile> profile720p(
        d_ptr->imediaManagement->getProfile720P());
    if (!profile720p)
        return false;
    auto& des = d_ptr->idata.profile720p;

    des.analytics           = profile720p->m_analytics;
    des.toKenPro            = profile720p->m_toKenPro;
    des.fixed               = profile720p->m_fixed;
    des.namePro             = profile720p->m_namePro;
    des.nameVsc             = profile720p->m_nameVsc;
    des.useCountVsc         = profile720p->m_useCountVsc;
    des.sourceTokenVsc      = profile720p->m_sourceTokenVsc;
    des.boundsVsc           = profile720p->m_boundsVsc;
    des.nameVec             = profile720p->m_nameVec;
    des.useCountVec         = profile720p->m_useCountVec;
    des.encodingVec         = profile720p->m_encodingVec;
    des.widthVec            = profile720p->m_widthVec;
    des.heightVec           = profile720p->m_heightVec;
    des.qualityVec          = profile720p->m_qualityVec;
    des.frameRateLimitVec   = profile720p->m_frameRateLimitVec;
    des.encodingIntervalVec = profile720p->m_encodingIntervalVec;
    des.bitrateLimitVec     = profile720p->m_bitrateLimitVec;
    des.govLengthVec        = profile720p->m_govLengthVec;
    des.h264ProfileVec      = profile720p->m_h264ProfileVec;
    des.typeVec             = profile720p->m_typeVec;
    des.ipv4AddressVec      = profile720p->m_ipv4AddressVec;
    des.ipv6AddressVec      = profile720p->m_ipv6AddressVec;
    des.portVec             = profile720p->m_portVec;
    des.ttlVec              = profile720p->m_ttlVec;
    des.autoStartVec        = profile720p->m_autoStartVec;
    des.sessionTimeoutVec   = profile720p->m_sessionTimeoutVec;
    des.namePtz             = profile720p->m_namePtz;
    des.useCountPtz         = profile720p->m_useCountPtz;
    des.nodeToken           = profile720p->m_nodeToken;
    des.panTiltSpace        = profile720p->m_panTiltSpace;
    des.panTiltX            = profile720p->m_panTiltX;
    des.panTiltY            = profile720p->m_panTiltY;
    des.zoomSpace           = profile720p->m_zoomSpace;
    des.zoomX               = profile720p->m_zoomX;
    des.defaultPTZTimeout   = profile720p->m_defaultPTZTimeout;
    des.panTiltUri          = profile720p->m_panTiltUri;
    des.xRangeMinPt         = profile720p->m_xRangeMinPt;
    des.xRangeMaxPt         = profile720p->m_xRangeMaxPt;
    des.yRangeMinPt         = profile720p->m_yRangeMinPt;
    des.yRangeMaxPt         = profile720p->m_yRangeMaxPt;
    des.zoomUri             = profile720p->m_zoomUri;
    des.xRangeMinZm         = profile720p->m_xRangeMinZm;
    des.xRangeMaxZm         = profile720p->m_xRangeMaxZm;
    des.nameMc              = profile720p->m_nameMc;
    des.useCountMc          = profile720p->m_useCountMc;
    des.status              = profile720p->m_status;
    des.position            = profile720p->m_position;
    des.filter              = profile720p->m_filter;
    des.subscriptionPolicy  = profile720p->m_subscriptionPolicy;
    des.analytics           = profile720p->m_analytics;
    des.typeMc              = profile720p->m_typeMc;
    des.ipv4AddressMc       = profile720p->m_ipv4AddressMc;
    des.ipv6AddressMc       = profile720p->m_ipv6AddressMc;
    des.portMc              = profile720p->m_portMc;
    des.ttlMc               = profile720p->m_ttlMc;
    des.autoStartMc         = profile720p->m_autoStartMc;
    des.sessionTimeoutMc    = profile720p->m_sessionTimeoutMc;
    des.defaultAbsolutePantTiltPositionSpace =
        profile720p->m_defaultAbsolutePantTiltPositionSpace;
    des.defaultAbsoluteZoomPositionSpace =
        profile720p->m_defaultAbsoluteZoomPositionSpace;
    des.defaultRelativePantTiltTranslationSpace =
        profile720p->m_defaultRelativePantTiltTranslationSpace;
    des.defaultRelativeZoomTranslationSpace =
        profile720p->m_defaultRelativeZoomTranslationSpace;
    des.defaultContinuousPantTiltVelocitySpace =
        profile720p->m_defaultContinuousPantTiltVelocitySpace;
    des.defaultContinuousZoomVelocitySpace =
        profile720p->m_defaultContinuousZoomVelocitySpace;

    QScopedPointer<ONVIF::Profile> profileD1(
        d_ptr->imediaManagement->getProfileD1());
    if (!profileD1)
        return false;
    d_ptr->idata.profileD1.analytics           = profileD1->m_analytics;
    d_ptr->idata.profileD1.toKenPro            = profileD1->m_toKenPro;
    d_ptr->idata.profileD1.fixed               = profileD1->m_fixed;
    d_ptr->idata.profileD1.namePro             = profileD1->m_namePro;
    d_ptr->idata.profileD1.nameVsc             = profileD1->m_nameVsc;
    d_ptr->idata.profileD1.useCountVsc         = profileD1->m_useCountVsc;
    d_ptr->idata.profileD1.sourceTokenVsc      = profileD1->m_sourceTokenVsc;
    d_ptr->idata.profileD1.boundsVsc           = profileD1->m_boundsVsc;
    d_ptr->idata.profileD1.nameVec             = profileD1->m_nameVec;
    d_ptr->idata.profileD1.useCountVec         = profileD1->m_useCountVec;
    d_ptr->idata.profileD1.encodingVec         = profileD1->m_encodingVec;
    d_ptr->idata.profileD1.widthVec            = profileD1->m_widthVec;
    d_ptr->idata.profileD1.heightVec           = profileD1->m_heightVec;
    d_ptr->idata.profileD1.qualityVec          = profileD1->m_qualityVec;
    d_ptr->idata.profileD1.frameRateLimitVec   = profileD1->m_frameRateLimitVec;
    d_ptr->idata.profileD1.encodingIntervalVec = profileD1->m_encodingIntervalVec;
    d_ptr->idata.profileD1.bitrateLimitVec     = profileD1->m_bitrateLimitVec;
    d_ptr->idata.profileD1.govLengthVec        = profileD1->m_govLengthVec;
    d_ptr->idata.profileD1.h264ProfileVec      = profileD1->m_h264ProfileVec;
    d_ptr->idata.profileD1.typeVec             = profileD1->m_typeVec;
    d_ptr->idata.profileD1.ipv4AddressVec      = profileD1->m_ipv4AddressVec;
    d_ptr->idata.profileD1.ipv6AddressVec      = profileD1->m_ipv6AddressVec;
    d_ptr->idata.profileD1.portVec             = profileD1->m_portVec;
    d_ptr->idata.profileD1.ttlVec              = profileD1->m_ttlVec;
    d_ptr->idata.profileD1.autoStartVec        = profileD1->m_autoStartVec;
    d_ptr->idata.profileD1.sessionTimeoutVec   = profileD1->m_sessionTimeoutVec;
    d_ptr->idata.profileD1.namePtz             = profileD1->m_namePtz;
    d_ptr->idata.profileD1.useCountPtz         = profileD1->m_useCountPtz;
    d_ptr->idata.profileD1.nodeToken           = profileD1->m_nodeToken;
    d_ptr->idata.profileD1.panTiltSpace        = profileD1->m_panTiltSpace;
    d_ptr->idata.profileD1.panTiltX            = profileD1->m_panTiltX;
    d_ptr->idata.profileD1.panTiltY            = profileD1->m_panTiltY;
    d_ptr->idata.profileD1.zoomSpace           = profileD1->m_zoomSpace;
    d_ptr->idata.profileD1.zoomX               = profileD1->m_zoomX;
    d_ptr->idata.profileD1.defaultPTZTimeout   = profileD1->m_defaultPTZTimeout;
    d_ptr->idata.profileD1.panTiltUri          = profileD1->m_panTiltUri;
    d_ptr->idata.profileD1.xRangeMinPt         = profileD1->m_xRangeMinPt;
    d_ptr->idata.profileD1.xRangeMaxPt         = profileD1->m_xRangeMaxPt;
    d_ptr->idata.profileD1.yRangeMinPt         = profileD1->m_yRangeMinPt;
    d_ptr->idata.profileD1.yRangeMaxPt         = profileD1->m_yRangeMaxPt;
    d_ptr->idata.profileD1.zoomUri             = profileD1->m_zoomUri;
    d_ptr->idata.profileD1.xRangeMinZm         = profileD1->m_xRangeMinZm;
    d_ptr->idata.profileD1.xRangeMaxZm         = profileD1->m_xRangeMaxZm;
    d_ptr->idata.profileD1.nameMc              = profileD1->m_nameMc;
    d_ptr->idata.profileD1.useCountMc          = profileD1->m_useCountMc;
    d_ptr->idata.profileD1.status              = profileD1->m_status;
    d_ptr->idata.profileD1.position            = profileD1->m_position;
    d_ptr->idata.profileD1.filter              = profileD1->m_filter;
    d_ptr->idata.profileD1.subscriptionPolicy  = profileD1->m_subscriptionPolicy;
    d_ptr->idata.profileD1.analytics           = profileD1->m_analytics;
    d_ptr->idata.profileD1.typeMc              = profileD1->m_typeMc;
    d_ptr->idata.profileD1.ipv4AddressMc       = profileD1->m_ipv4AddressMc;
    d_ptr->idata.profileD1.ipv6AddressMc       = profileD1->m_ipv6AddressMc;
    d_ptr->idata.profileD1.portMc              = profileD1->m_portMc;
    d_ptr->idata.profileD1.ttlMc               = profileD1->m_ttlMc;
    d_ptr->idata.profileD1.autoStartMc         = profileD1->m_autoStartMc;
    d_ptr->idata.profileD1.sessionTimeoutMc    = profileD1->m_sessionTimeoutMc;
    d_ptr->idata.profileD1.defaultAbsolutePantTiltPositionSpace =
        profileD1->m_defaultAbsolutePantTiltPositionSpace;
    d_ptr->idata.profileD1.defaultAbsoluteZoomPositionSpace =
        profileD1->m_defaultAbsoluteZoomPositionSpace;
    d_ptr->idata.profileD1.defaultRelativePantTiltTranslationSpace =
        profileD1->m_defaultRelativePantTiltTranslationSpace;
    d_ptr->idata.profileD1.defaultRelativeZoomTranslationSpace =
        profileD1->m_defaultRelativeZoomTranslationSpace;
    d_ptr->idata.profileD1.defaultContinuousPantTiltVelocitySpace =
        profileD1->m_defaultContinuousPantTiltVelocitySpace;
    d_ptr->idata.profileD1.defaultContinuousZoomVelocitySpace =
        profileD1->m_defaultContinuousZoomVelocitySpace;
    return true;
}

bool
QOnvifDevice::refreshPtzConfiguration() {
    ONVIF::Configuration* config = new ONVIF::Configuration;
    d_ptr->iptzManagement->getConfiguration(config);
    auto& des = d_ptr->idata.ptz.config;

    des.name                  = config->name();
    des.useCount              = config->useCount();
    des.nodeToken             = config->nodeToken();
    des.panTiltX              = config->panTiltX();
    des.panTiltY              = config->panTiltY();
    des.zoomSpace             = config->zoomSpace();
    des.defaultPTZTimeout     = config->defaultPTZTimeout();
    des.panTiltUri            = config->panTiltUri();
    des.panTiltXRangeMin      = config->panTiltXRangeMin();
    des.panTiltXRangeMax      = config->panTiltXRangeMax();
    des.panTiltYRangeMin      = config->panTiltXRangeMin();
    des.panTiltYRangeMax      = config->panTiltYRangeMax();
    des.zoomUri               = config->zoomUri();
    des.zoomXRangeMin         = config->zoomXRangeMin();
    des.zoomXRangeMax         = config->zoomXRangeMax();
    des.ptzConfigurationToken = config->ptzConfigurationToken();
    des.panTiltSpace          = config->panTiltSpace();
    des.zoomX                 = config->zoomX();

    des.defaultAbsolutePantTiltPositionSpace =
        config->defaultAbsolutePantTiltPositionSpace();
    des.defaultAbsoluteZoomPositionSpace =
        config->defaultAbsoluteZoomPositionSpace();
    des.defaultRelativePanTiltTranslationSpace =
        config->defaultRelativePanTiltTranslationSpace();
    des.defaultRelativeZoomTranslationSpace =
        config->defaultRelativeZoomTranslationSpace();
    des.defaultContinuousPanTiltVelocitySpace =
        config->defaultContinuousPanTiltVelocitySpace();

    delete config;
    return true;
}

bool
QOnvifDevice::refreshImageSetting() {
    refreshImageSettingOptions();

    QScopedPointer<ONVIF::ImageSetting> imageSetting(
        d_ptr->imediaManagement->getImageSetting(
            d_ptr->idata.profiles.sourceTokenVsc[0])); // todo

    if (!imageSetting)
        return false;

    auto& des = d_ptr->idata.mediaConfig.imageSetting;

    des.autofocusManual = imageSetting->autofocusManual();
    des.brightness      = imageSetting->brightness();
    des.colorSaturation = imageSetting->colorSaturation();
    des.contrast        = imageSetting->contrast();
    des.defaultSpeed    = imageSetting->defaultSpeed();
    des.sharpness       = imageSetting->sharpness();
    return true;
}
bool
QOnvifDevice::refreshImageSettingOptions() {
    QScopedPointer<ONVIF::ImageSettingOptions> imageSettingOptions(
        d_ptr->imediaManagement->getImageSettingOptions(
            d_ptr->idata.profiles.sourceTokenVsc[0])); // todo
    if (!imageSettingOptions)
        return false;

    auto& des = d_ptr->idata.mediaConfig.imageSetting.options;

    des.brightnessMax      = imageSettingOptions->brightnessMax();
    des.brightnessMin      = imageSettingOptions->brightnessMin();
    des.colorSaturationMax = imageSettingOptions->colorSaturationMax();
    des.colorSaturationMin = imageSettingOptions->colorSaturationMin();
    des.contrastMax        = imageSettingOptions->contrastMax();
    des.contrastMin        = imageSettingOptions->contrastMin();
    des.defaultSpeedMax    = imageSettingOptions->defaultSpeedMax();
    des.defaultSpeedMin    = imageSettingOptions->defaultSpeedMin();
    des.sharpnessMax       = imageSettingOptions->sharpnessMax();
    des.sharpnessMin       = imageSettingOptions->sharpnessMin();
    return true;
}

bool
QOnvifDevice::refreshPresets() {
    ONVIF::Presets* presets = new ONVIF::Presets;
    presets->setProfileToken("MediaProfile000");
    d_ptr->iptzManagement->getPresets(presets);
    delete presets;
    return true;
}

bool
QOnvifDevice::goHomePosition() {
    ONVIF::GotoHomePosition* goHomePose = new ONVIF::GotoHomePosition;
    goHomePose->setProfileToken("MediaProfile000");
    d_ptr->iptzManagement->gotoHomePosition(goHomePose);
    delete goHomePose;
    return true;
}

bool
QOnvifDevice::setHomePosition() {
    ONVIF::HomePosition* homePosition = new ONVIF::HomePosition;
    homePosition->setProfileToken("MediaProfile000");
    d_ptr->iptzManagement->setHomePosition(homePosition);
    delete homePosition;
    return true;
}

bool
QOnvifDevice::continuousMove(const float x, const float y, const float z) {
    ONVIF::ContinuousMove* continuousMove = new ONVIF::ContinuousMove;
    continuousMove->setProfileToken("MediaProfile000");
    continuousMove->setPanTiltX(x);
    continuousMove->setPanTiltY(y);
    continuousMove->setZoomX(z);
    d_ptr->iptzManagement->continuousMove(continuousMove);
    delete continuousMove;
    return true;
}

bool
QOnvifDevice::stopMovement() {
    ONVIF::Stop* stop = new ONVIF::Stop;
    stop->setProfileToken("MediaProfile000");
    stop->setPanTilt(true);
    stop->setZoom(true);
    d_ptr->iptzManagement->stop(stop);
    delete stop;
    return true;
}

///////////////////////////////////////////////////////////////////////////////
} // namespace device
///////////////////////////////////////////////////////////////////////////////
