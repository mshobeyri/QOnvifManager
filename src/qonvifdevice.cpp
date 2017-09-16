#include "qonvifdevice.hpp"
#include "devicemanagement.h"
#include "mediamanagement.h"
#include "ptzmanagement.h"
#include <QEventLoop>
#include <QQueue>
#include <QString>
#include <QTimer>

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

    void addRequest(MessageType _messageType, QVariant _data) {
        requestQueue.enqueue(qMakePair(_messageType, _data));
        if (requestQueue.count() == 1)
            sendRequest();
    }

    void sendRequest() {

        if (requestQueue.isEmpty())
            return;

        auto& request = requestQueue.first();

        switch (request.first) {
        case MessageType::Information:
        case MessageType::Scopes:
        case MessageType::DateAndTime:
        case MessageType::Users:
        case MessageType::Capabilities:
        case MessageType::NetworkInterfaces:
        case MessageType::NetworkProtocols:
        case MessageType::NetworkDefaultGateway:
        case MessageType::NetworkDiscoveryMode:
        case MessageType::NetworkDNS:
        case MessageType::NetworkHostname:
        case MessageType::NetworkNTP:
            ideviceManagement->getData(request.first);
            break;
        case MessageType::SetScopes:
        case MessageType::SetDateAndTime:
        case MessageType::SetUsers:
        case MessageType::SetNetworkInterfaces:
        case MessageType::SetNetworkProtocols:
        case MessageType::SetNetworkDefaultGateway:
        case MessageType::SetNetworkDiscoveryMode:
        case MessageType::SetNetworkDNS:
        case MessageType::SetNetworkHostname:
        case MessageType::SetNetworkNTP:
        case MessageType::SetSystemFactoryDefault:
        case MessageType::SetSystemReboot:
            ideviceManagement->setData(request.first, request.second);
            break;
        case MessageType::Profiles:
        case MessageType::Profile720p:
        case MessageType::ProfileD1:
        case MessageType::VideoEncoderConfigurations:
        case MessageType::VideoSourceConfigurations:
        case MessageType::VideoEncoderConfigurationOptions:
        case MessageType::StreamUri:
        case MessageType::ImageSetting:
        case MessageType::ImageSettingOptions:
            imediaManagement->getData(request.first, request.second.toList());
            break;
        case MessageType::SetVideoEncoderConfiguration:
        case MessageType::SetImageSettings:
            imediaManagement->setData(request.first, request.second);
            break;
        case MessageType::Configuration:
        case MessageType::Presets:
            iptzManagement->getData(request.first, request.second.toList());
            break;
        case MessageType::GotoHomePosition:
        case MessageType::SetHomePosition:
        case MessageType::ContinuousMove:
        case MessageType::Stop:
            iptzManagement->setData(request.first, request.second);
            break;
        default:
            break;
        }
    }

    // onvif managers
    ONVIF::DeviceManagement* ideviceManagement;
    ONVIF::MediaManagement*  imediaManagement;
    ONVIF::PtzManagement*    iptzManagement;

    QQueue<QPair<MessageType, QVariant>> requestQueue;
};

// QOnvifDevice::QOnvifDevice() {}

QOnvifDevice::QOnvifDevice(
    QString  _serviceAddress,
    QString  _userName,
    QString  _password,
    QObject* _parent)
    : QObject(_parent),
      d_ptr{new QOnvifDevicePrivate{_serviceAddress, _userName, _password}} {

    connect(
        d_ptr->ideviceManagement,
        &ONVIF::DeviceManagement::resultReceived,
        this,
        [this](QVariant var, MessageType messageType) {

            switch (messageType) {
            case MessageType::Information: {
                QHash<QString, QString> deviceInformationHash =
                    var.value<QHash<QString, QString>>();
                d_ptr->idata.information.manufacturer =
                    deviceInformationHash.value("mf");
                d_ptr->idata.information.model =
                    deviceInformationHash.value("model");
                d_ptr->idata.information.firmwareVersion =
                    deviceInformationHash.value("firmware_version");
                d_ptr->idata.information.serialNumber =
                    deviceInformationHash.value("serial_number");
                d_ptr->idata.information.hardwareId =
                    deviceInformationHash.value("hardware_id");

                emit informationReceived(d_ptr->idata.information);
                emit getResultReceived(d_ptr->idata, messageType);
            } break;
            case MessageType::Scopes: {
                QHash<QString, QString> deviceScopesHash =
                    var.value<QHash<QString, QString>>();
                d_ptr->idata.scopes.name = deviceScopesHash.value("name");
                d_ptr->idata.scopes.location =
                    deviceScopesHash.value("location");
                d_ptr->idata.scopes.hardware =
                    deviceScopesHash.value("hardware");

                emit scopesReceived(d_ptr->idata.scopes);
                emit getResultReceived(d_ptr->idata, messageType);
            } break;
            case MessageType::DateAndTime: {
                QScopedPointer<ONVIF::SystemDateAndTime> systemDateAndTime(
                    toPtr<ONVIF::SystemDateAndTime>(var));

                d_ptr->idata.dateTime.localTime =
                    systemDateAndTime->localTime();
                d_ptr->idata.dateTime.utcTime  = systemDateAndTime->utcTime();
                d_ptr->idata.dateTime.timeZone = systemDateAndTime->tz();
                d_ptr->idata.dateTime.daylightSaving =
                    systemDateAndTime->daylightSavings();

                emit dateAndTimeReceived(d_ptr->idata.dateTime);
                emit getResultReceived(d_ptr->idata, messageType);
            } break;
            case MessageType::Users: {
                QScopedPointer<ONVIF::Users> users(toPtr<ONVIF::Users>(var));

                d_ptr->idata.users.clear();
                for (int i = 0; i < users->userNames().length(); i++) {
                    Data::User user;
                    user.username  = users->userNames().value(i);
                    user.password  = users->passWord().value(i);
                    user.userLevel = users->userLevel().value(i);
                    d_ptr->idata.users.append(user);
                }

                emit usersReceived(d_ptr->idata.users);
                emit getResultReceived(d_ptr->idata, messageType);
            } break;
            case MessageType::Capabilities: {
                QScopedPointer<ONVIF::Capabilities> capabilities(
                    toPtr<ONVIF::Capabilities>(var));

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
                emit getResultReceived(d_ptr->idata, messageType);
            } break;
            case MessageType::NetworkInterfaces: {
                QScopedPointer<ONVIF::NetworkInterfaces> networkInterfaces(
                    toPtr<ONVIF::NetworkInterfaces>(var));

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
                des.duplexFull =
                    src->duplex() == ONVIF::NetworkInterfaces::Duplex::Full
                        ? true
                        : false;

                emit networkInterfacesReceived(d_ptr->idata.network.interfaces);
                emit getResultReceived(d_ptr->idata, messageType);
            } break;
            case MessageType::NetworkProtocols: {
                QScopedPointer<ONVIF::NetworkProtocols> networkProtocols(
                    toPtr<ONVIF::NetworkProtocols>(var));

                auto& des = d_ptr->idata.network.protocols;
                auto& src = networkProtocols;

                des.networkProtocolsEnabled = src->getNetworkProtocolsEnabled();
                des.networkProtocolsName    = src->getNetworkProtocolsName();
                des.networkProtocolsPort    = src->getNetworkProtocolsPort();

                emit networkProtocolsReceived(d_ptr->idata.network.protocols);
                emit getResultReceived(d_ptr->idata, messageType);
            } break;
            case MessageType::NetworkDefaultGateway: {
                QScopedPointer<ONVIF::NetworkDefaultGateway>
                    networkDefaultGateway(
                        toPtr<ONVIF::NetworkDefaultGateway>(var));

                auto& des = d_ptr->idata.network.defaultGateway;
                auto& src = networkDefaultGateway;

                des.ipv4Address = src->ipv4Address();
                des.ipv6Address = src->ipv6Address();

                emit networkDefaultGatewayReceived(
                    d_ptr->idata.network.defaultGateway);
                emit getResultReceived(d_ptr->idata, messageType);
            } break;
            case MessageType::NetworkDiscoveryMode: {
                QScopedPointer<ONVIF::NetworkDiscoveryMode>
                    networkDiscoveryMode(
                        toPtr<ONVIF::NetworkDiscoveryMode>(var));

                auto& des = d_ptr->idata.network.discoveryMode;
                auto& src = networkDiscoveryMode;

                des.discoveryMode = src->discoveryMode();

                emit networkDiscoveryModeReceived(
                    d_ptr->idata.network.discoveryMode);
                emit getResultReceived(d_ptr->idata, messageType);
            } break;
            case MessageType::NetworkDNS: {
                QScopedPointer<ONVIF::NetworkDNS> networkDNS(
                    toPtr<ONVIF::NetworkDNS>(var));

                auto& des = d_ptr->idata.network.dns;
                auto& src = networkDNS;

                des.dhcp         = src->dhcp();
                des.ipv4Address  = src->ipv4Address();
                des.manualType   = src->manualType();
                des.searchDomain = src->searchDomain();

                emit networkDNSReceived(d_ptr->idata.network.dns);
                emit getResultReceived(d_ptr->idata, messageType);
            } break;
            case MessageType::NetworkHostname: {
                QScopedPointer<ONVIF::NetworkHostname> networkHostname(
                    toPtr<ONVIF::NetworkHostname>(var));

                auto& des = d_ptr->idata.network.hostname;
                auto& src = networkHostname;

                des.dhcp = src->dhcp();
                des.name = src->name();

                emit networkHostnameReceived(d_ptr->idata.network.hostname);
                emit getResultReceived(d_ptr->idata, messageType);
            } break;
            case MessageType::NetworkNTP: {
                QScopedPointer<ONVIF::NetworkNTP> networkNTP(
                    toPtr<ONVIF::NetworkNTP>(var));

                auto& des = d_ptr->idata.network.ntp;
                auto& src = networkNTP;

                des.dhcp        = src->dhcp();
                des.name        = src->name();
                des.ipv4Address = src->ipv4Address();
                des.ipv6Address = src->ipv6Address();
                des.manualType  = src->manualType();

                emit networkNTPReceived(d_ptr->idata.network.ntp);
                emit getResultReceived(d_ptr->idata, messageType);
            } break;
            case MessageType::SetScopes:
            case MessageType::SetDateAndTime:
            case MessageType::SetUsers:
            case MessageType::SetSystemFactoryDefault:
            case MessageType::SetSystemReboot:
            case MessageType::SetNetworkInterfaces:
            case MessageType::SetNetworkProtocols:
            case MessageType::SetNetworkDefaultGateway:
            case MessageType::SetNetworkDiscoveryMode:
            case MessageType::SetNetworkDNS:
            case MessageType::SetNetworkHostname:
            case MessageType::SetNetworkNTP: {
                bool r = var.value<bool>();
                emit setResultReceived(r, messageType);
            } break;
            default:
                break;
            }

            d_ptr->requestQueue.dequeue();
            d_ptr->sendRequest();
        });

    connect(
        d_ptr->imediaManagement,
        &ONVIF::MediaManagement::resultReceived,
        this,
        [this](QVariant var, MessageType messageType) {

            switch (messageType) {
            case MessageType::Profiles: {
                QScopedPointer<ONVIF::Profiles> profiles(
                    toPtr<ONVIF::Profiles>(var));

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

                emit profilesReceived(d_ptr->idata.profiles);
                emit getResultReceived(d_ptr->idata, messageType);
            } break;
            case MessageType::Profile720p: {
                QScopedPointer<ONVIF::Profile> profile720p(
                    toPtr<ONVIF::Profile>(var));

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

                emit profile720pReceived(d_ptr->idata.profile720p);
                emit getResultReceived(d_ptr->idata, messageType);
            } break;
            case MessageType::ProfileD1: {
                QScopedPointer<ONVIF::Profile> profileD1(
                    toPtr<ONVIF::Profile>(var));

                d_ptr->idata.profileD1.analytics   = profileD1->m_analytics;
                d_ptr->idata.profileD1.toKenPro    = profileD1->m_toKenPro;
                d_ptr->idata.profileD1.fixed       = profileD1->m_fixed;
                d_ptr->idata.profileD1.namePro     = profileD1->m_namePro;
                d_ptr->idata.profileD1.nameVsc     = profileD1->m_nameVsc;
                d_ptr->idata.profileD1.useCountVsc = profileD1->m_useCountVsc;
                d_ptr->idata.profileD1.sourceTokenVsc =
                    profileD1->m_sourceTokenVsc;
                d_ptr->idata.profileD1.boundsVsc   = profileD1->m_boundsVsc;
                d_ptr->idata.profileD1.nameVec     = profileD1->m_nameVec;
                d_ptr->idata.profileD1.useCountVec = profileD1->m_useCountVec;
                d_ptr->idata.profileD1.encodingVec = profileD1->m_encodingVec;
                d_ptr->idata.profileD1.widthVec    = profileD1->m_widthVec;
                d_ptr->idata.profileD1.heightVec   = profileD1->m_heightVec;
                d_ptr->idata.profileD1.qualityVec  = profileD1->m_qualityVec;
                d_ptr->idata.profileD1.frameRateLimitVec =
                    profileD1->m_frameRateLimitVec;
                d_ptr->idata.profileD1.encodingIntervalVec =
                    profileD1->m_encodingIntervalVec;
                d_ptr->idata.profileD1.bitrateLimitVec =
                    profileD1->m_bitrateLimitVec;
                d_ptr->idata.profileD1.govLengthVec = profileD1->m_govLengthVec;
                d_ptr->idata.profileD1.h264ProfileVec =
                    profileD1->m_h264ProfileVec;
                d_ptr->idata.profileD1.typeVec = profileD1->m_typeVec;
                d_ptr->idata.profileD1.ipv4AddressVec =
                    profileD1->m_ipv4AddressVec;
                d_ptr->idata.profileD1.ipv6AddressVec =
                    profileD1->m_ipv6AddressVec;
                d_ptr->idata.profileD1.portVec      = profileD1->m_portVec;
                d_ptr->idata.profileD1.ttlVec       = profileD1->m_ttlVec;
                d_ptr->idata.profileD1.autoStartVec = profileD1->m_autoStartVec;
                d_ptr->idata.profileD1.sessionTimeoutVec =
                    profileD1->m_sessionTimeoutVec;
                d_ptr->idata.profileD1.namePtz      = profileD1->m_namePtz;
                d_ptr->idata.profileD1.useCountPtz  = profileD1->m_useCountPtz;
                d_ptr->idata.profileD1.nodeToken    = profileD1->m_nodeToken;
                d_ptr->idata.profileD1.panTiltSpace = profileD1->m_panTiltSpace;
                d_ptr->idata.profileD1.panTiltX     = profileD1->m_panTiltX;
                d_ptr->idata.profileD1.panTiltY     = profileD1->m_panTiltY;
                d_ptr->idata.profileD1.zoomSpace    = profileD1->m_zoomSpace;
                d_ptr->idata.profileD1.zoomX        = profileD1->m_zoomX;
                d_ptr->idata.profileD1.defaultPTZTimeout =
                    profileD1->m_defaultPTZTimeout;
                d_ptr->idata.profileD1.panTiltUri  = profileD1->m_panTiltUri;
                d_ptr->idata.profileD1.xRangeMinPt = profileD1->m_xRangeMinPt;
                d_ptr->idata.profileD1.xRangeMaxPt = profileD1->m_xRangeMaxPt;
                d_ptr->idata.profileD1.yRangeMinPt = profileD1->m_yRangeMinPt;
                d_ptr->idata.profileD1.yRangeMaxPt = profileD1->m_yRangeMaxPt;
                d_ptr->idata.profileD1.zoomUri     = profileD1->m_zoomUri;
                d_ptr->idata.profileD1.xRangeMinZm = profileD1->m_xRangeMinZm;
                d_ptr->idata.profileD1.xRangeMaxZm = profileD1->m_xRangeMaxZm;
                d_ptr->idata.profileD1.nameMc      = profileD1->m_nameMc;
                d_ptr->idata.profileD1.useCountMc  = profileD1->m_useCountMc;
                d_ptr->idata.profileD1.status      = profileD1->m_status;
                d_ptr->idata.profileD1.position    = profileD1->m_position;
                d_ptr->idata.profileD1.filter      = profileD1->m_filter;
                d_ptr->idata.profileD1.subscriptionPolicy =
                    profileD1->m_subscriptionPolicy;
                d_ptr->idata.profileD1.analytics = profileD1->m_analytics;
                d_ptr->idata.profileD1.typeMc    = profileD1->m_typeMc;
                d_ptr->idata.profileD1.ipv4AddressMc =
                    profileD1->m_ipv4AddressMc;
                d_ptr->idata.profileD1.ipv6AddressMc =
                    profileD1->m_ipv6AddressMc;
                d_ptr->idata.profileD1.portMc      = profileD1->m_portMc;
                d_ptr->idata.profileD1.ttlMc       = profileD1->m_ttlMc;
                d_ptr->idata.profileD1.autoStartMc = profileD1->m_autoStartMc;
                d_ptr->idata.profileD1.sessionTimeoutMc =
                    profileD1->m_sessionTimeoutMc;
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

                emit profileD1Received(d_ptr->idata.profileD1);
                emit getResultReceived(d_ptr->idata, messageType);
            } break;
            case MessageType::VideoEncoderConfigurations: {
                QScopedPointer<ONVIF::VideoEncoderConfigurations>
                    videoEncoderConfigurations(
                        toPtr<ONVIF::VideoEncoderConfigurations>(var));

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

                emit videoEncoderConfigurationsReceived(
                    d_ptr->idata.mediaConfig.video.encodingConfigs);
                emit getResultReceived(d_ptr->idata, messageType);

                getVideoEncoderConfigurationOptions();
            } break;
            case MessageType::VideoSourceConfigurations: {
                QScopedPointer<ONVIF::VideoSourceConfigurations>
                    videoSourceConfigurations(
                        toPtr<ONVIF::VideoSourceConfigurations>(var));

                auto& des       = d_ptr->idata.mediaConfig.video.sourceConfig;
                auto& src       = videoSourceConfigurations;
                des.name        = src->getName();
                des.useCount    = src->getUseCount();
                des.sourceToken = src->getSourceToken();
                des.bounds      = src->getBounds();

                emit videoSourceConfigurationsReceived(
                    d_ptr->idata.mediaConfig.video.sourceConfig);
                emit getResultReceived(d_ptr->idata, messageType);
            } break;
            case MessageType::VideoEncoderConfigurationOptions: {
                QScopedPointer<ONVIF::VideoEncoderConfigurationOptions>
                    videoEncoderConfigurationOptions(
                        toPtr<ONVIF::VideoEncoderConfigurationOptions>(var));

                Data::MediaConfig::Video::EncoderConfigs::Option
                    encodingOptions;

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

                for (const auto& h264ProfilesSupported :
                     src->getH264ProfilesSupported()) {
                    int intCastTemp = static_cast<int>(h264ProfilesSupported);

                    Data::MediaConfig::Video::EncoderConfigs::Option::
                        H264ProfilesSupported enumCastTemp = static_cast<
                            Data::MediaConfig::Video::EncoderConfigs::Option::
                                H264ProfilesSupported>(intCastTemp);

                    des.h264ProfilesSupported.append(enumCastTemp);
                }
                d_ptr->idata.mediaConfig.video.encodingConfigs.options.append(
                    des);

                emit videoEncoderConfigurationOptionReceived(des);

                auto configToken =
                    d_ptr->idata.mediaConfig.video.encodingConfigs.token;
                auto profileToken = d_ptr->idata.profiles.toKenPro;
                auto size = qMin(configToken.length(), profileToken.length());
                if (d_ptr->idata.mediaConfig.video.encodingConfigs.options
                        .count() >= size)
                    emit getResultReceived(d_ptr->idata, messageType);
            } break;
            case MessageType::StreamUri: {
                QScopedPointer<ONVIF::StreamUri> streamUri(
                    toPtr<ONVIF::StreamUri>(var));

                Data::MediaConfig::Video::StreamUri streamUriTemp;
                streamUriTemp.uri = streamUri->uri();
                streamUriTemp.invalidAfterConnect =
                    streamUri->invalidAfterConnect();
                streamUriTemp.invalidAfterReboot =
                    streamUri->invalidAfterReboot();
                streamUriTemp.timeout = streamUri->timeout();

                if (d_ptr->idata.profiles.streamUris.isEmpty())
                    d_ptr->idata.mediaConfig.video.streamUri = streamUriTemp;

                d_ptr->idata.profiles.streamUris.append(streamUriTemp);
                emit streamUrisReceived(streamUriTemp);
                if (d_ptr->idata.profiles.streamUris.count() >=
                    d_ptr->idata.profiles.toKenPro.length())
                    emit getResultReceived(d_ptr->idata, messageType);
            } break;
            case MessageType::ImageSetting: {
                QScopedPointer<ONVIF::ImageSetting> imageSetting(
                    toPtr<ONVIF::ImageSetting>(var));

                auto& des = d_ptr->idata.mediaConfig.imageSetting;

                des.autofocusManual = imageSetting->autofocusManual();
                des.brightness      = imageSetting->brightness();
                des.colorSaturation = imageSetting->colorSaturation();
                des.contrast        = imageSetting->contrast();
                des.defaultSpeed    = imageSetting->defaultSpeed();
                des.sharpness       = imageSetting->sharpness();

                emit imageSettingReceived(
                    d_ptr->idata.mediaConfig.imageSetting);
                emit getResultReceived(d_ptr->idata, messageType);
            } break;
            case MessageType::ImageSettingOptions: {
                QScopedPointer<ONVIF::ImageSettingOptions> imageSettingOptions(
                    toPtr<ONVIF::ImageSettingOptions>(var));

                auto& des = d_ptr->idata.mediaConfig.imageSetting.options;

                des.brightnessMax = imageSettingOptions->brightnessMax();
                des.brightnessMin = imageSettingOptions->brightnessMin();
                des.colorSaturationMax =
                    imageSettingOptions->colorSaturationMax();
                des.colorSaturationMin =
                    imageSettingOptions->colorSaturationMin();
                des.contrastMax     = imageSettingOptions->contrastMax();
                des.contrastMin     = imageSettingOptions->contrastMin();
                des.defaultSpeedMax = imageSettingOptions->defaultSpeedMax();
                des.defaultSpeedMin = imageSettingOptions->defaultSpeedMin();
                des.sharpnessMax    = imageSettingOptions->sharpnessMax();
                des.sharpnessMin    = imageSettingOptions->sharpnessMin();

                emit imageSettingOptionsReceived(
                    d_ptr->idata.mediaConfig.imageSetting.options);
                emit getResultReceived(d_ptr->idata, messageType);
            } break;
            case MessageType::SetVideoEncoderConfiguration:
            case MessageType::SetImageSettings: {
                bool r = var.value<bool>();
                emit setResultReceived(r, messageType);
            } break;
            default:
                break;
            }

            d_ptr->requestQueue.dequeue();
            d_ptr->sendRequest();
        });

    connect(
        d_ptr->iptzManagement,
        &ONVIF::PtzManagement::resultReceived,
        this,
        [this](QVariant var, MessageType messageType) {

            switch (messageType) {
            case MessageType::Configurations: {
                QScopedPointer<ONVIF::Configurations> config(
                    toPtr<ONVIF::Configurations>(var));
            } break;
            case MessageType::Configuration: {
                QScopedPointer<ONVIF::Configuration> config(
                    toPtr<ONVIF::Configuration>(var));

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

                emit ptzConfigurationReceived(d_ptr->idata.ptz.config);
                emit getResultReceived(d_ptr->idata, messageType);
            } break;
            case MessageType::Nodes: {
                QScopedPointer<ONVIF::Nodes> nodes(toPtr<ONVIF::Nodes>(var));
            } break;
            case MessageType::Node: {
                QScopedPointer<ONVIF::Node> node(toPtr<ONVIF::Node>(var));
            } break;
            case MessageType::Presets: {
                QScopedPointer<ONVIF::Presets> presets(
                    toPtr<ONVIF::Presets>(var));
            } break;
            case MessageType::RemovePreset:
            case MessageType::SetPreset:
            case MessageType::ContinuousMove:
            case MessageType::AbsoluteMove:
            case MessageType::RelativeMove:
            case MessageType::Stop:
            case MessageType::GotoPreset:
            case MessageType::GotoHomePosition:
            case MessageType::SetHomePosition: {
                bool r = var.value<bool>();
                emit setResultReceived(r, messageType);
            } break;
            default:
                break;
            }

            d_ptr->requestQueue.dequeue();
            d_ptr->sendRequest();
        });
}

QOnvifDevice::~QOnvifDevice() {}

Data&
QOnvifDevice::data() {
    return d_ptr->idata;
}

void
QOnvifDevice::getInformation() {
    d_ptr->addRequest(MessageType::Information, QVariant());
}

void
QOnvifDevice::getScopes() {
    d_ptr->addRequest(MessageType::Scopes, QVariant());
}

void
QOnvifDevice::getDateAndTime() {
    d_ptr->addRequest(MessageType::DateAndTime, QVariant());
}

void
QOnvifDevice::getUsers() {
    d_ptr->addRequest(MessageType::Users, QVariant());
}

void
QOnvifDevice::getCapabilities() {
    d_ptr->addRequest(MessageType::Capabilities, QVariant());
}

void
QOnvifDevice::getInterfaces() {
    d_ptr->addRequest(MessageType::NetworkInterfaces, QVariant());
}
void
QOnvifDevice::getProtocols() {
    d_ptr->addRequest(MessageType::NetworkProtocols, QVariant());
}

void
QOnvifDevice::getDefaultGateway() {
    d_ptr->addRequest(MessageType::NetworkDefaultGateway, QVariant());
}

void
QOnvifDevice::getDiscoveryMode() {
    d_ptr->addRequest(MessageType::NetworkDiscoveryMode, QVariant());
}

void
QOnvifDevice::getDNS() {
    d_ptr->addRequest(MessageType::NetworkDNS, QVariant());
}

void
QOnvifDevice::getHostname() {
    d_ptr->addRequest(MessageType::NetworkHostname, QVariant());
}

void
QOnvifDevice::getNTP() {
    d_ptr->addRequest(MessageType::NetworkNTP, QVariant());
}

void
QOnvifDevice::setProbeData(Data::ProbeData _probeData) {
    d_ptr->idata.probeData = _probeData;
}

void
QOnvifDevice::setScopes(QString _name, QString _location) {
    auto data = new ONVIF::SystemScopes;
    data->setScopes(_name, _location);

    d_ptr->addRequest(
        MessageType::SetScopes, toQVariant<ONVIF::SystemScopes>(data));
}

void
QOnvifDevice::setDateAndTime(
    QDateTime _dateAndTime,
    QString   _zone,
    bool      _daylightSaving,
    bool      _isLocal) {
    auto data = new ONVIF::SystemDateAndTime;
    data->setIsLocal(_isLocal);
    if (_isLocal) {
        data->setlocalTime(_dateAndTime);
    } else {
        data->setutcTime(_dateAndTime);
    }
    data->setTz(_zone);
    data->setDaylightSavings(_daylightSaving);

    d_ptr->addRequest(
        MessageType::SetDateAndTime,
        toQVariant<ONVIF::SystemDateAndTime>(data));
}

void
QOnvifDevice::setUsers(Data::Users _users) {
    auto data = new ONVIF::Users;
    for (int i = 0; i < _users.length(); i++) {
        data->setUserNames(_users[i].username);
        data->setPassWords(_users[i].password);
        data->setUserLevel(_users[i].userLevel);
        data->setActionMode(_users[i].actionMode);
    }

    d_ptr->addRequest(MessageType::SetUsers, toQVariant<ONVIF::Users>(data));
}

void
QOnvifDevice::setNetworkInterfaces(Data::Network::Interfaces _interfaces) {
    auto data = new ONVIF::NetworkInterfaces;
    data->setAutoNegotiation(_interfaces.autoNegotiation);
    data->setDuplex(
        _interfaces.duplexFull ? ONVIF::NetworkInterfaces::Duplex::Full
                               : ONVIF::NetworkInterfaces::Duplex::Half);

    data->setHwAaddress(_interfaces.hwAaddress);
    data->setIpv4DHCP(_interfaces.ipv4DHCP);
    data->setIpv4Enabled(_interfaces.ipv4Enabled);
    data->setIpv4FromDHCPAddress(_interfaces.ipv4FromDHCPAddress);
    data->setIpv4FromDHCPPrefixLength(_interfaces.ipv4FromDHCPPrefixLength);
    data->setIpv4LinkLocalAddress(_interfaces.ipv4LinkLocalAddress);
    data->setIpv4ManualAddress(_interfaces.ipv4ManualAddress);
    data->setIpv4ManualPrefixLength(_interfaces.ipv4ManualPrefixLength);
    data->setIpvLinkLocalPrefixLength(_interfaces.ipvLinkLocalPrefixLength);
    data->setMtu(_interfaces.mtu);
    data->setNetworkInfacesEnabled(_interfaces.networkInfacesEnabled);
    data->setNetworkInfacesName(_interfaces.networkInfacesName);
    data->setSpeed(_interfaces.speed);
    data->setInterfaceToken(_interfaces.interfaceToken);

    d_ptr->addRequest(
        MessageType::SetNetworkInterfaces,
        toQVariant<ONVIF::NetworkInterfaces>(data));
}

void
QOnvifDevice::setNetworkProtocols(Data::Network::Protocols _protocols) {
    auto data = new ONVIF::NetworkProtocols;
    for (int i = 0; i < _protocols.networkProtocolsName.length(); i++) {
        data->setNetworkProtocolsEnabled(_protocols.networkProtocolsEnabled[i]);
        data->setNetworkProtocolsPort(_protocols.networkProtocolsPort[i]);
        data->setNetworkProtocolsName(_protocols.networkProtocolsName[i]);
    }

    d_ptr->addRequest(
        MessageType::SetNetworkProtocols,
        toQVariant<ONVIF::NetworkProtocols>(data));
}

void
QOnvifDevice::setNetworkDefaultGateway(
    Data::Network::DefaultGateway _defaultGateway) {
    auto data = new ONVIF::NetworkDefaultGateway;
    data->setIpv4Address(_defaultGateway.ipv4Address);

    d_ptr->addRequest(
        MessageType::SetNetworkDefaultGateway,
        toQVariant<ONVIF::NetworkDefaultGateway>(data));
}

void
QOnvifDevice::setNetworkDiscoveryMode(
    Data::Network::DiscoveryMode _discoveryMode) {
    auto data = new ONVIF::NetworkDiscoveryMode;
    data->setDiscoveryMode(_discoveryMode.discoveryMode);

    d_ptr->addRequest(
        MessageType::SetNetworkDiscoveryMode,
        toQVariant<ONVIF::NetworkDiscoveryMode>(data));
}

void
QOnvifDevice::setNetworkDNS(Data::Network::DNS _dns) {
    auto data = new ONVIF::NetworkDNS;
    data->setDhcp(_dns.dhcp);
    for (const auto& ipAddress : _dns.ipv4Address)
        data->setIpv4Address(ipAddress);
    for (const auto& manualType : _dns.manualType)
        data->setManualType(manualType);
    data->setSearchDomain(_dns.searchDomain);

    d_ptr->addRequest(
        MessageType::NetworkDNS, toQVariant<ONVIF::NetworkDNS>(data));
}

void
QOnvifDevice::setNetworkHostname(Data::Network::Hostname _hostname) {
    auto data = new ONVIF::NetworkHostname;
    data->setDhcp(_hostname.dhcp);
    data->setName(_hostname.name);

    d_ptr->addRequest(
        MessageType::SetNetworkHostname,
        toQVariant<ONVIF::NetworkHostname>(data));
}

void
QOnvifDevice::setNetworkNTP(Data::Network::NTP _ntp) {
    auto data = new ONVIF::NetworkNTP;
    data->setDhcp(_ntp.dhcp);
    data->setIpv4Address(_ntp.ipv4Address);
    data->setManualType(_ntp.ipv6Address);

    d_ptr->addRequest(
        MessageType::SetNetworkNTP, toQVariant<ONVIF::NetworkNTP>(data));
}

void
QOnvifDevice::resetFactory(bool isHard) {
    auto data = new ONVIF::SystemFactoryDefault;
    data->setFactoryDefault(
        isHard ? ONVIF::SystemFactoryDefault::Hard
               : ONVIF::SystemFactoryDefault::Soft);

    d_ptr->addRequest(
        MessageType::SetSystemFactoryDefault,
        toQVariant<ONVIF::SystemFactoryDefault>(data));
}

void
QOnvifDevice::reboot() {
    auto data = new ONVIF::SystemReboot;

    d_ptr->addRequest(
        MessageType::SetSystemReboot, toQVariant<ONVIF::SystemReboot>(data));
}

void
QOnvifDevice::getProfiles() {
    d_ptr->addRequest(MessageType::Profiles, QVariant());
}

void
QOnvifDevice::getProfile720p() {
    d_ptr->addRequest(MessageType::Profile720p, QVariant());
}

void
QOnvifDevice::getProfileD1() {
    d_ptr->addRequest(MessageType::ProfileD1, QVariant());
}

void
QOnvifDevice::getVideoEncoderConfigurations() {
    d_ptr->addRequest(MessageType::VideoEncoderConfigurations, QVariant());
}

void
QOnvifDevice::getVideoSourceConfigurations() {
    d_ptr->addRequest(MessageType::VideoSourceConfigurations, QVariant());
}

void
QOnvifDevice::getVideoEncoderConfigurationOptions() {

    if (d_ptr->idata.profiles.toKenPro.isEmpty()) {
        getProfiles();

        QTimer timer;
        timer.setSingleShot(true);
        QEventLoop loop;
        connect(
            this, &QOnvifDevice::profilesReceived, &loop, &QEventLoop::quit);
        connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
        timer.start(3000);
        loop.exec();

        if (!timer.isActive())
            return;
    }
    if (d_ptr->idata.mediaConfig.video.encodingConfigs.token.isEmpty()) {
        getVideoEncoderConfigurations();

        QTimer timer;
        timer.setSingleShot(true);
        QEventLoop loop;
        connect(
            this,
            &QOnvifDevice::videoEncoderConfigurationsReceived,
            &loop,
            &QEventLoop::quit);
        connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
        timer.start(3000);
        loop.exec();

        if (!timer.isActive())
            return;
    }

    // get video encoder options
    d_ptr->idata.mediaConfig.video.encodingConfigs.options.clear();
    auto configToken  = d_ptr->idata.mediaConfig.video.encodingConfigs.token;
    auto profileToken = d_ptr->idata.profiles.toKenPro;
    auto size         = qMin(configToken.length(), profileToken.length());

    for (int i = 0; i < size; ++i) {

        QVariantList parameters;
        parameters.append(configToken[i]);
        parameters.append(profileToken[i]);
        d_ptr->addRequest(
            MessageType::VideoEncoderConfigurationOptions, parameters);
    }
}

void
QOnvifDevice::getStreamUris() {

    if (d_ptr->idata.profiles.toKenPro.isEmpty()) {
        getProfiles();

        QTimer timer;
        timer.setSingleShot(true);
        QEventLoop loop;
        connect(
            this, &QOnvifDevice::profilesReceived, &loop, &QEventLoop::quit);
        connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
        timer.start(3000);
        loop.exec();

        if (!timer.isActive())
            return;
    }

    d_ptr->idata.profiles.streamUris.clear();

    for (int i = 0; i < d_ptr->idata.profiles.toKenPro.length(); ++i) {
        QVariantList parameters;
        parameters.append(d_ptr->idata.profiles.toKenPro.value(i));
        d_ptr->addRequest(MessageType::StreamUri, parameters);
    }
}

void
QOnvifDevice::getImageSetting() {
    getImageSettingOptions();

    QVariantList parameters;
    parameters.append(d_ptr->idata.profiles.sourceTokenVsc[0]);

    d_ptr->addRequest(MessageType::ImageSetting, parameters);
}

void
QOnvifDevice::getImageSettingOptions() {
    if (d_ptr->idata.profiles.sourceTokenVsc.isEmpty()) {
        getProfiles();

        QTimer timer;
        timer.setSingleShot(true);
        QEventLoop loop;
        connect(
            this, &QOnvifDevice::profilesReceived, &loop, &QEventLoop::quit);
        connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
        timer.start(3000);
        loop.exec();

        if (!timer.isActive())
            return;
    }

    QVariantList parameters;
    parameters.append(d_ptr->idata.profiles.sourceTokenVsc[0]);

    d_ptr->addRequest(MessageType::ImageSettingOptions, parameters);
}

void
QOnvifDevice::setVideoEncoderConfiguration(
    Data::MediaConfig::Video::EncoderConfig _videoConfig) {
    auto data = new ONVIF::VideoEncoderConfiguration;
    data->setToken(_videoConfig.token);
    data->setName(_videoConfig.name);
    data->setUseCount(_videoConfig.useCount);
    data->setEncoding(_videoConfig.encoding);
    data->setWidth(_videoConfig.width);
    data->setHeight(_videoConfig.height);
    data->setQuality(_videoConfig.quality);
    data->setFrameRateLimit(_videoConfig.frameRateLimit);
    data->setEncodingInterval(_videoConfig.encodingInterval);
    data->setBitrateLimit(_videoConfig.bitrateLimit);
    data->setGovLength(_videoConfig.govLength);
    data->setH264Profile(_videoConfig.h264Profile);
    data->setType(_videoConfig.type);
    data->setIpv4Address(_videoConfig.ipv4Address);
    data->setPort(_videoConfig.port);
    data->setTtl(_videoConfig.ttl);
    data->setAutoStart(_videoConfig.autoStart);
    data->setSessionTimeout(_videoConfig.sessionTimeout);

    d_ptr->addRequest(
        MessageType::SetVideoEncoderConfiguration,
        toQVariant<ONVIF::VideoEncoderConfiguration>(data));
}

void
QOnvifDevice::setImageSetting(Data::MediaConfig::ImageSetting _imageSetting) {
    auto data = new ONVIF::ImageSetting;
    data->setAutofocusManual(_imageSetting.autofocusManual);
    data->setBrightness(_imageSetting.brightness);
    data->setColorSaturation(_imageSetting.colorSaturation);
    data->setContrast(_imageSetting.contrast);
    data->setDefaultSpeed(_imageSetting.defaultSpeed);
    data->setExposureIris(_imageSetting.exposureIris);
    data->setExposureManual(_imageSetting.exposureManual);
    data->setForcePersistence(_imageSetting.forcePersistence);
    data->setSharpness(_imageSetting.sharpness);
    data->setToken(_imageSetting.token);

    d_ptr->addRequest(
        MessageType::SetImageSettings, toQVariant<ONVIF::ImageSetting>(data));
}

void
QOnvifDevice::getPtzConfiguration() {
    d_ptr->addRequest(MessageType::Configuration, QVariant());
}

void
QOnvifDevice::getPresets() {
    QVariantList parameters;
    parameters.append("MediaProfile000");
    d_ptr->addRequest(MessageType::Presets, parameters);
}

void
QOnvifDevice::goHomePosition() {
    auto data = new ONVIF::GotoHomePosition;
    data->setProfileToken("MediaProfile000");

    d_ptr->addRequest(
        MessageType::GotoHomePosition,
        toQVariant<ONVIF::GotoHomePosition>(data));
}

void
QOnvifDevice::setHomePosition() {
    auto data = new ONVIF::HomePosition;
    data->setProfileToken("MediaProfile000");

    d_ptr->addRequest(
        MessageType::SetHomePosition, toQVariant<ONVIF::HomePosition>(data));
}

void
QOnvifDevice::continuousMove(const float x, const float y, const float z) {
    auto data = new ONVIF::ContinuousMove;
    data->setProfileToken("MediaProfile000");
    data->setPanTiltX(x);
    data->setPanTiltY(y);
    data->setZoomX(z);

    d_ptr->addRequest(
        MessageType::ContinuousMove, toQVariant<ONVIF::ContinuousMove>(data));
}

void
QOnvifDevice::stopMovement() {
    auto data = new ONVIF::Stop;
    data->setProfileToken("MediaProfile000");
    data->setPanTilt(true);
    data->setZoom(true);

    d_ptr->addRequest(MessageType::Stop, toQVariant<ONVIF::Stop>(data));
}

///////////////////////////////////////////////////////////////////////////////
} // namespace device
///////////////////////////////////////////////////////////////////////////////
