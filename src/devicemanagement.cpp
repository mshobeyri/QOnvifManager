#include "devicemanagement.h"
#include <QDebug>

using namespace ONVIF;

DeviceManagement::DeviceManagement(
    const QString& wsdlUrl, const QString& username, const QString& password)
    : Service(wsdlUrl, username, password) {
    connect(
        this,
        &DeviceManagement::messageParserReceived,
        this,
        &DeviceManagement::onMessageParserReceived);
}

Message*
DeviceManagement::newMessage() {
    QHash<QString, QString> names;
    names.insert("wsdl", "http://www.onvif.org/ver10/device/wsdl");
    names.insert("sch", "http://www.onvif.org/ver10/schema");
    return createMessage(names);
}

QHash<QString, QString>
DeviceManagement::namespaces(const QString& key) {
    QHash<QString, QString> names;
    Q_UNUSED(key);
    names.insert("SOAP-ENV", "http://www.w3.org/2003/05/soap-envelope");
    names.insert("SOAP-ENC", "http://www.w3.org/2003/05/soap-encoding");
    names.insert("xsi", "http://www.w3.org/2001/XMLSchema-instance");
    names.insert("xsd", "http://www.w3.org/2001/XMLSchema");
    names.insert("c14n", "http://www.w3.org/2001/10/xml-exc-c14n#");
    names.insert(
        "wsu",
        "http://docs.oasis-open.org/wss/2004/01/"
        "oasis-200401-wss-wssecurity-utility-1.0.xsd");
    names.insert("xenc", "http://www.w3.org/2001/04/xmlenc#");
    names.insert("ds", "http://www.w3.org/2000/09/xmldsig#");
    names.insert(
        "wsse",
        "http://docs.oasis-open.org/wss/2004/01/"
        "oasis-200401-wss-wssecurity-secext-1.0.xsd");
    names.insert("wsa5", "http://www.w3.org/2005/08/addressing");
    names.insert("xmime", "http://tempuri.org/xmime.xsd");
    names.insert("xop", "http://www.w3.org/2004/08/xop/include");
    names.insert("wsa", "http://schemas.xmlsoap.org/ws/2004/08/addressing");
    names.insert("tt", "http://www.onvif.org/ver10/schema");
    names.insert("wsbf", "http://docs.oasis-open.org/wsrf/bf-2");
    names.insert("wstop", "http://docs.oasis-open.org/wsn/t-1");
    names.insert("d", "http://schemas.xmlsoap.org/ws/2005/04/discovery");
    names.insert("wsr", "http://docs.oasis-open.org/wsrf/r-2");
    names.insert(
        "dndl",
        "http://www.onvif.org/ver10/network/wsdl/DiscoveryLookupBinding");
    names.insert(
        "dnrd",
        "http://www.onvif.org/ver10/network/wsdl/RemoteDiscoveryBinding");
    names.insert("dn", "http://www.onvif.org/ver10/network/wsdl");
    names.insert("tad", "http://www.onvif.org/ver10/analyticsdevice/wsdl");
    names.insert(
        "tanae",
        "http://www.onvif.org/ver20/analytics/wsdl/AnalyticsEngineBinding");
    names.insert(
        "tanre", "http://www.onvif.org/ver20/analytics/wsdl/RuleEngineBinding");
    names.insert("tan", "http://www.onvif.org/ver20/analytics/wsdl");
    names.insert("tds", "http://www.onvif.org/ver10/device/wsdl");
    names.insert(
        "tetcp",
        "http://www.onvif.org/ver10/events/wsdl/CreatePullPointBinding");
    names.insert("tete", "http://www.onvif.org/ver10/events/wsdl/EventBinding");
    names.insert(
        "tetnc",
        "http://www.onvif.org/ver10/events/wsdl/NotificationConsumerBinding");
    names.insert(
        "tetnp",
        "http://www.onvif.org/ver10/events/wsdl/NotificationProducerBinding");
    names.insert(
        "tetpp", "http://www.onvif.org/ver10/events/wsdl/PullPointBinding");
    names.insert(
        "tetpps",
        "http://www.onvif.org/ver10/events/wsdl/PullPointSubscriptionBinding");
    names.insert("tev", "http://www.onvif.org/ver10/events/wsdl");
    names.insert(
        "tetps",
        "http://www.onvif.org/ver10/events/wsdl/"
        "PausableSubscriptionManagerBinding");
    names.insert("wsnt", "http://docs.oasis-open.org/wsn/b-2");
    names.insert(
        "tetsm",
        "http://www.onvif.org/ver10/events/wsdl/SubscriptionManagerBinding");
    names.insert("timg", "http://www.onvif.org/ver20/imaging/wsdl");
    names.insert("timg10", "http://www.onvif.org/ver10/imaging/wsdl");
    names.insert("tls", "http://www.onvif.org/ver10/display/wsdl");
    names.insert("tmd", "http://www.onvif.org/ver10/deviceIO/wsdl");
    names.insert("tptz", "http://www.onvif.org/ver20/ptz/wsdl");
    names.insert("trc", "http://www.onvif.org/ver10/recording/wsdl");
    names.insert("trp", "http://www.onvif.org/ver10/replay/wsdl");
    names.insert("trt", "http://www.onvif.org/ver10/media/wsdl");
    names.insert("trv", "http://www.onvif.org/ver10/receiver/wsdl");
    names.insert("tse", "http://www.onvif.org/ver10/search/wsdl");
    names.insert("tns1", "http://www.onvif.org/ver10/schema");
    names.insert("tnsn", "http://www.eventextension.com/2011/event/topics");
    names.insert("tnsavg", "http://www.avigilon.com/onvif/ver10/topics");

    return names;
}

void
DeviceManagement::onMessageParserReceived(
    MessageParser* result, device::MessageType messageType) {
    if (result == NULL)
        return;

    QVariant var;

    switch (messageType) {
    case device::MessageType::Information: {
        QHash<QString, QString> device_info;
        device_info.insert("mf", result->getValue("//tds:Manufacturer"));
        device_info.insert("model", result->getValue("//tds:Model"));
        device_info.insert(
            "firmware_version", result->getValue("//tds:FirmwareVersion"));
        device_info.insert(
            "serial_number", result->getValue("//tds:SerialNumber"));
        device_info.insert("hardware_id", result->getValue("//tds:HardwareId"));
        var = qVariantFromValue(device_info);
    } break;
    case device::MessageType::Scopes: {
        QHash<QString, QString> device_scopes;
        device_scopes.insert(
            "name",
            result->getValue(
                "//tds:GetScopesResponse/tds:Scopes[./"
                "tt:ScopeDef[./text()='Configurable']]/"
                "/tt:ScopeItem[starts-with(text(),'odm:name:') or "
                "starts-with(text(),'onvif://www.onvif.org/name')]"));
        device_scopes.insert(
            "location",
            result->getValue(
                "//tds:GetScopesResponse/tds:Scopes[./"
                "tt:ScopeDef[./text()='Configurable']]/"
                "/tt:ScopeItem[starts-with(text(),'odm:location:') or "
                "starts-with(text(),'onvif://www.onvif.org/location/')]"));

        device_scopes.insert(
            "hardware",
            result
                ->getValue(
                    "//tds:GetScopesResponse/tds:Scopes[./"
                    "tt:ScopeDef[./text()='Fixed']]/"
                    "/tt:ScopeItem[starts-with(text(),'odm:hardware:') or "
                    "starts-with(text(),'onvif://www.onvif.org/hardware/')]")
                .remove(0, 31));
        var = qVariantFromValue(device_scopes);
    } break;
    case device::MessageType::DateAndTime: {
        SystemDateAndTime* systemDateAndTime = new SystemDateAndTime();
        systemDateAndTime->setProperty(
            "dateTimeType", result->getValue("//tt:DateTimeType"));
        systemDateAndTime->setDaylightSavings(
            result->getValue("//tt:DaylightSavings") == "true");
        systemDateAndTime->setTz(result->getValue("//tt:TimeZone/tt:TZ"));
        systemDateAndTime->setUtcTime(
            result->getValue("//tt:UTCDateTime/tt:Date/tt:Year").toInt(),
            result->getValue("//tt:UTCDateTime/tt:Date/tt:Month").toInt(),
            result->getValue("//tt:UTCDateTime/tt:Date/tt:Day").toInt(),
            result->getValue("//tt:UTCDateTime/tt:Time/tt:Hour").toInt(),
            result->getValue("//tt:UTCDateTime/tt:Time/tt:Minute").toInt(),
            result->getValue("//tt:UTCDateTime/tt:Time/tt:Second").toInt());
        systemDateAndTime->setLocalTime(
            result->getValue("//tt:LocalDateTime/tt:Date/tt:Year").toInt(),
            result->getValue("//tt:LocalDateTime/tt:Date/tt:Month").toInt(),
            result->getValue("//tt:LocalDateTime/tt:Date/tt:Day").toInt(),
            result->getValue("//tt:LocalDateTime/tt:Time/tt:Hour").toInt(),
            result->getValue("//tt:LocalDateTime/tt:Time/tt:Minute").toInt(),
            result->getValue("//tt:LocalDateTime/tt:Time/tt:Second").toInt());
        var = toQVariant<SystemDateAndTime>(systemDateAndTime);
    } break;
    case device::MessageType::Users: {
        Users* user = new Users();

        //        user->setProperty("userName",
        //        result->getValue("//tt:Username"));
        //        user->setProperty("passWord",
        //        result->getValue("//tt:Password"));
        //        user->setProperty("userLevel",
        //        result->getValue("//tt:UserLevel"));
        QXmlQuery* query = result->query();
        query->setQuery(result->nameSpace() + "doc($inputDocument)//tds:User");
        QXmlResultItems items;
        query->evaluateTo(&items);
        QXmlItem item = items.next();
        QString  username, userLevel;
        while (!item.isNull()) {
            query->setFocus(item);
            query->setQuery(result->nameSpace() + "./tt:Username/string()");
            query->evaluateTo(&username);
            user->setUserNames(username.trimmed());

            query->setQuery(result->nameSpace() + "./tt:UserLevel/string()");
            query->evaluateTo(&userLevel);
            QString levelStr = userLevel.trimmed();

            user->setUserLevel(userLevel.trimmed());
            item = items.next();
        }
        var = toQVariant<Users>(user);
    } break;
    case device::MessageType::Capabilities: {
        Capabilities* capabilities = new Capabilities();
        // PTZ
        capabilities->setProperty(
            "ptzXAddr", result->getValue("//tt:PTZ/tt:XAddr"));
        // Imaging
        capabilities->setProperty(
            "imagingXAddr", result->getValue("//tt:Imaging/tt:XAddr"));
        capabilities->setProperty(
            "mediaXAddr", result->getValue("//tt:Media/tt:XAddr"));
        capabilities->setProperty(
            "rtpMulticast",
            result->getValue("//tt:RTPMulticast") == "true" ? true : false);
        capabilities->setProperty(
            "rtpTcp",
            result->getValue("//tt:RTP_TCP") == "true" ? true : false);
        capabilities->setProperty(
            "rtpRtspTcp",
            result->getValue("//tt:RTP_RTSP_TCP") == "true" ? true : false);
        // Device
        capabilities->setProperty(
            "deviceXAddr", result->getValue("//tt:Device/tt:XAddr"));
        capabilities->setProperty(
            "iPFilter",
            result->getValue("//tt:IPFilter") == "true" ? true : false);
        capabilities->setProperty(
            "zeroConfiguration",
            result->getValue("//tt:ZeroConfiguration") == "true" ? true
                                                                 : false);
        capabilities->setProperty(
            "iPVersion6",
            result->getValue("//tt:IPVersion6") == "true" ? true : false);
        capabilities->setProperty(
            "dynDNS", result->getValue("//tt:DynDNS") == "true" ? true : false);
        capabilities->setProperty(
            "discoveryResolve",
            result->getValue("//tt:DiscoveryResolve") == "true" ? true : false);
        capabilities->setProperty(
            "discoveryBye",
            result->getValue("//tt:DiscoveryBye") == "true" ? true : false);
        capabilities->setProperty(
            "remoteDiscovery",
            result->getValue("//tt:RemoteDiscovery") == "true" ? true : false);
        capabilities->setProperty(
            "systemBackup",
            result->getValue("//tt:SystemBackup") == "true" ? true : false);
        capabilities->setProperty(
            "systemLogging",
            result->getValue("//tt:SystemLogging") == "true" ? true : false);
        capabilities->setProperty(
            "firmwareUpgrade",
            result->getValue("//tt:FirmwareUpgrade") == "true" ? true : false);
        capabilities->setProperty(
            "major", result->getValue("//tt:Major").toInt());
        capabilities->setProperty(
            "minor", result->getValue("//tt:Minor").toInt());
        capabilities->setProperty(
            "httpFirmwareUpgrade",
            result->getValue("//tt:HttpFirmwareUpgrade") == "true" ? true
                                                                   : false);
        capabilities->setProperty(
            "httpSystemBackup",
            result->getValue("//tt:HttpSystemBackup") == "true" ? true : false);
        capabilities->setProperty(
            "httpSystemLogging",
            result->getValue("//tt:HttpSystemLogging") == "true" ? true
                                                                 : false);
        capabilities->setProperty(
            "httpSupportInformation",
            result->getValue("//tt:HttpSupportInformation") == "true" ? true
                                                                      : false);
        capabilities->setProperty(
            "inputConnectors",
            result->getValue("//tt:InputConnectors").toInt());
        capabilities->setProperty(
            "relayOutputs", result->getValue("//tt:RelayOutputs").toInt());
        capabilities->setProperty(
            "tls11", result->getValue("//tt:TLS1.1") == "true" ? true : false);
        capabilities->setProperty(
            "tls12", result->getValue("//tt:TLS1.2") == "true" ? true : false);
        capabilities->setProperty(
            "onboardKeyGeneration",
            result->getValue("//tt:OnboardKeyGeneration") == "true" ? true
                                                                    : false);
        capabilities->setProperty(
            "accessPolicyConfig",
            result->getValue("//tt:AccessPolicyConfig") == "true" ? true
                                                                  : false);
        capabilities->setProperty(
            "x509Token",
            result->getValue("//tt:X.509Token") == "true" ? true : false);
        capabilities->setProperty(
            "samlToken",
            result->getValue("//tt:SAMLToken") == "true" ? true : false);
        capabilities->setProperty(
            "kerberosToken",
            result->getValue("//tt:KerberosToken") == "true" ? true : false);
        capabilities->setProperty(
            "relToken",
            result->getValue("//tt:RELToken") == "true" ? true : false);
        capabilities->setProperty(
            "tls10", result->getValue("//tt:TLS1.0") == "true" ? true : false);
        capabilities->setProperty(
            "dot1x", result->getValue("//tt:Dot1x") == "true" ? true : false);
        capabilities->setProperty(
            "remoteUserHanding",
            result->getValue("//tt:RemoteUserHanding") == "true" ? true
                                                                 : false);
        var = toQVariant<Capabilities>(capabilities);
    } break;
    case device::MessageType::NetworkInterfaces: {
        NetworkInterfaces* networkInterfaces = new NetworkInterfaces();
        networkInterfaces->setProperty(
            "interfaceToken",
            result->getValue("//tds:NetworkInterfaces/@token"));
        networkInterfaces->setProperty(
            "networkInfacesEnabled",
            result->getValue("//tds:NetworkInterfaces/tt:Enabled"));
        networkInterfaces->setProperty(
            "networkInfacesName", result->getValue("//tt:Name"));
        networkInterfaces->setProperty(
            "hwAaddress", result->getValue("//tt:HwAddress"));
        networkInterfaces->setProperty(
            "mtu", result->getValue("//tt:MTU").toInt());
        networkInterfaces->setProperty(
            "ipv4esult != NULL)Enabled",
            result->getValue("//tt:IPv4/tt:Enabled"));
        networkInterfaces->setProperty(
            "ipv4ManualAddress", result->getValue("//tt:Manual/tt:Address"));
        networkInterfaces->setProperty(
            "ipv4ManualPrefixLength",
            result->getValue("//tt:Manual/tt:PrefixLength").toInt());
        networkInterfaces->setProperty(
            "ipv4LinkLocalAddress",
            result->getValue("//tt:LinkLocal/tt:Address"));
        networkInterfaces->setProperty(
            "ipvLinkLocalPrefixLength",
            result->getValue("//tt:LinkLocal/tt:PrefixLength").toInt());
        networkInterfaces->setProperty(
            "ipv4FromDHCPAddress",
            result->getValue("//tt:FromDHCP/tt:Address"));
        networkInterfaces->setProperty(
            "ipv4FromDHCPPrefixLength",
            result->getValue("//tt:FromDHCP/tt:PrefixLength").toInt());
        networkInterfaces->setProperty(
            "ipv4DHCP", result->getValue("//tt:DHCP"));
        var = toQVariant<NetworkInterfaces>(networkInterfaces);
    } break;
    case device::MessageType::NetworkProtocols: {
        NetworkProtocols* networkProtocols = new NetworkProtocols();

        QXmlQuery* query = result->query();
        query->setQuery(
            result->nameSpace() + "doc($inputDocument)//tds:NetworkProtocols");
        QXmlResultItems items;
        query->evaluateTo(&items);
        QXmlItem item = items.next();
        QString  protocolsName, protocolsEnabled, protocolsPort;
        while (!item.isNull()) {
            query->setFocus(item);
            query->setQuery(result->nameSpace() + "./tt:Name/string()");
            query->evaluateTo(&protocolsName);
            networkProtocols->setNetworkProtocolsName(protocolsName.trimmed());

            query->setQuery(result->nameSpace() + "./tt:Enabled/string()");
            query->evaluateTo(&protocolsEnabled);
            networkProtocols->setNetworkProtocolsEnabled(
                protocolsEnabled.trimmed() == "true" ? true : false);

            query->setQuery(result->nameSpace() + "./tt:Port/string()");
            query->evaluateTo(&protocolsPort);
            networkProtocols->setNetworkProtocolsPort(
                protocolsPort.trimmed().toInt());
            item = items.next();
        }
        var = toQVariant<NetworkProtocols>(networkProtocols);
    } break;
    case device::MessageType::NetworkDefaultGateway: {
        NetworkDefaultGateway* networkDefaultGateway =
            new NetworkDefaultGateway();
        networkDefaultGateway->setProperty(
            "ipv4Address",
            result->getValue("//tds:NetworkGateway/tt:IPv4Address"));
        networkDefaultGateway->setProperty(
            "ipv6Address",
            result->getValue("//tds:NetworkGateway/tt:IPv6Address"));
        var = toQVariant<NetworkDefaultGateway>(networkDefaultGateway);
    } break;
    case device::MessageType::NetworkDiscoveryMode: {
        NetworkDiscoveryMode* networkDiscoveryMode = new NetworkDiscoveryMode();
        networkDiscoveryMode->setProperty(
            "discoveryMode", result->getValue("//tds:DiscoveryMode"));
        var = toQVariant<NetworkDiscoveryMode>(networkDiscoveryMode);
    } break;
    case device::MessageType::NetworkDNS: {
        NetworkDNS* networkDNS = new NetworkDNS();
        networkDNS->setProperty(
            "dhcp", result->getValue("//tds:DNSInformation/tt:FromDHCP"));
        networkDNS->setProperty(
            "searchDomain",
            result->getValue("//tds:DNSInformation/tt:SearchDomain"));

        QXmlQuery* query = result->query();
        query->setQuery(
            result->nameSpace() +
            "doc($inputDocument)//tds:DNSInformation/tt:DNSManual");

        QXmlResultItems items;
        query->evaluateTo(&items);
        QXmlItem item = items.next();
        QString  dnsType, dnsIPv4Address;
        while (!item.isNull()) {
            query->setFocus(item);
            query->setQuery(result->nameSpace() + "./tt:Type/string()");
            query->evaluateTo(&dnsType);
            networkDNS->setManualType(dnsType.trimmed());

            query->setQuery(result->nameSpace() + "./tt:IPv4Address/string()");
            query->evaluateTo(&dnsIPv4Address);
            networkDNS->setIpv4Address(dnsIPv4Address.trimmed());
            item = items.next();
        }
        var = toQVariant<NetworkDNS>(networkDNS);
    } break;
    case device::MessageType::NetworkHostname: {
        NetworkHostname* networkHostname = new NetworkHostname();
        networkHostname->setProperty(
            "dhcp", result->getValue("//tds:HostnameInformation/tt:FromDHCP"));
        networkHostname->setProperty(
            "name", result->getValue("//tds:HostnameInformation/tt:Name"));
        var = toQVariant<NetworkHostname>(networkHostname);
    } break;
    case device::MessageType::NetworkNTP: {
        NetworkNTP* networkNTP = new NetworkNTP();
        networkNTP->setProperty(
            "dhcp", result->getValue("//tds:NTPInformation/tt:fromDHCP"));
        networkNTP->setProperty(
            "manualType",
            result->getValue("//tds:NTPInformation/tt:NTPManual/tt:Type"));
        networkNTP->setProperty(
            "name",
            result->getValue("//tds:NTPInformation/tt:NTPManual/tt:DNSname"));
        networkNTP->setProperty(
            "ipv4Address",
            result->getValue(
                "//tds:NTPInformation/tt:NTPManual/tt:IPv4Address"));
        networkNTP->setProperty(
            "ipv6Address",
            result->getValue(
                "//tds:NTPInformation/tt:NTPManual/tt:IPv6Address"));
        var = toQVariant<NetworkNTP>(networkNTP);
    } break;
    case device::MessageType::SetScopes: {
        bool r = false;
        if (result->find("//tds:SetScopesResponse"))
            r = true;
        var   = qVariantFromValue(r);
    } break;
    case device::MessageType::SetDateAndTime: {
        bool r = false;
        if (result->find("//tds:SetSystemDateAndTimeResponse"))
            r = true;
        var   = qVariantFromValue(r);
    } break;
    case device::MessageType::SetUsers: {
        bool r = false;
        if (result->find("//tds:CreateUsersResponse") ||
            result->find("//tds:SetUserResponse"))
            r = true;
        var   = qVariantFromValue(r);
    } break;
    case device::MessageType::SetSystemFactoryDefault: {
        bool r = false;
        if (result->find("//tds:SetSystemFactoryDefaultResponse"))
            r = true;
        var   = qVariantFromValue(r);
    } break;
    case device::MessageType::SetSystemReboot: {
        bool r = false;
        if (result->find("//tds:SystemRebootResponse"))
            r = true;
        var   = qVariantFromValue(r);
    } break;
    case device::MessageType::SetNetworkInterfaces: {
        bool r = false;
        if (result->find("//tds:SetNetworkInterfacesResponse"))
            r = true;
        var   = qVariantFromValue(r);
    } break;
    case device::MessageType::SetNetworkProtocols: {
        bool r = false;
        if (result->find("//tds:SetNetworkProtocolsResponse"))
            r = true;
        var   = qVariantFromValue(r);
    } break;
    case device::MessageType::SetNetworkDefaultGateway: {
        bool r = false;
        if (result->find("//tds:SetNetworkDefaultGatewayResponse"))
            r = true;
        var   = qVariantFromValue(r);
    } break;
    case device::MessageType::SetNetworkDiscoveryMode: {
        bool r = false;
        if (result->find("//tds:SetDiscoveryModeResponse"))
            r = true;
        var   = qVariantFromValue(r);
    } break;
    case device::MessageType::SetNetworkDNS: {
        bool r = false;
        if (result->find("//tds:SetDNSResponse"))
            r = true;
        var   = qVariantFromValue(r);
    } break;
    case device::MessageType::SetNetworkHostname: {
        bool r = false;
        if (result->find("//tds:SetHostnameResponse"))
            r = true;
        var   = qVariantFromValue(r);
    } break;
    case device::MessageType::SetNetworkNTP: {
        bool r = false;
        if (result->find("//tds:SetNTPResponse"))
            r = true;
        var   = qVariantFromValue(r);
    } break;
    default:
        break;
    }

    emit resultReceived(var, messageType);

    result->deleteLater();
}

void
DeviceManagement::getData(device::MessageType messageType) {
    Message* msg = newMessage();

    switch (messageType) {
    case device::MessageType::Information:

        msg->appendToBody(newElement("wsdl:GetDeviceInformation"));

        break;
    case device::MessageType::Scopes:

        msg->appendToBody(newElement(
            "wsdl:GetScopes xmlns=\"http://www.onvif.org/ver10/device/wsdl\""));

        break;
    case device::MessageType::DateAndTime:

        msg->appendToBody(newElement("wsdl:GetSystemDateAndTime"));

        break;
    case device::MessageType::Users:

        msg->appendToBody(newElement("wsdl:GetUsers"));

        break;
    case device::MessageType::Capabilities: {
        QDomElement cap = newElement("wsdl:GetCapabilities");
        cap.appendChild(newElement("wsdl:Category", "All"));
        msg->appendToBody(cap);
    } break;
    case device::MessageType::NetworkInterfaces:

        msg->appendToBody(newElement("wsdl:GetNetworkInterfaces"));

        break;
    case device::MessageType::NetworkProtocols:

        msg->appendToBody(newElement("wsdl:GetNetworkProtocols"));

        break;
    case device::MessageType::NetworkDefaultGateway:

        msg->appendToBody(newElement("wsdl:GetNetworkDefaultGateway"));

        break;
    case device::MessageType::NetworkDiscoveryMode:

        msg->appendToBody(newElement("wsdl:GetDiscoveryMode"));

        break;
    case device::MessageType::NetworkDNS:

        msg->appendToBody(newElement("wsdl:GetDNS"));

        break;
    case device::MessageType::NetworkHostname:

        msg->appendToBody(newElement("wsdl:GetHostname"));

        break;
    case device::MessageType::NetworkNTP:

        msg->appendToBody(newElement("wsdl:GetNTP"));

        break;
    default:
        msg->deleteLater();
        return;
    }

    sendMessage(msg, messageType);
    msg->deleteLater();
}

void
DeviceManagement::setData(device::MessageType messageType, QVariant data) {
    Message*    msg = newMessage();
    QDomElement domElement;

    switch (messageType) {
    case device::MessageType::SetScopes: {
        SystemScopes* d = toPtr<ONVIF::SystemScopes>(data);
        domElement      = d->toxml();
        d->deleteLater();
    } break;
    case device::MessageType::SetDateAndTime: {
        SystemDateAndTime* d =toPtr <ONVIF::SystemDateAndTime> (data);
        domElement           = d->toxml();
        d->deleteLater();
    } break;
    case device::MessageType::SetUsers: {
        Users* d   = toPtr<ONVIF::Users> (data);
        domElement = d->toxml();
        d->deleteLater();
    } break;
    case device::MessageType::SetSystemFactoryDefault: {
        SystemFactoryDefault* d = toPtr<ONVIF::SystemFactoryDefault> (data);
        domElement              = d->toxml();
        d->deleteLater();
    } break;
    case device::MessageType::SetSystemReboot: {
        SystemReboot* d = toPtr<ONVIF::SystemReboot> (data);
        domElement      = d->toxml();
        d->deleteLater();
    } break;
    case device::MessageType::SetNetworkInterfaces: {
        NetworkInterfaces* d = toPtr<ONVIF::NetworkInterfaces> (data);
        domElement           = d->toxml();
        d->deleteLater();
    } break;
    case device::MessageType::SetNetworkProtocols: {
        NetworkProtocols* d = toPtr<ONVIF::NetworkProtocols> (data);
        domElement          = d->toxml();
        d->deleteLater();
    } break;
    case device::MessageType::SetNetworkDefaultGateway: {
        NetworkDefaultGateway* d = toPtr<ONVIF::NetworkDefaultGateway> (data);
        domElement               = d->toxml();
        d->deleteLater();
    } break;
    case device::MessageType::SetNetworkDiscoveryMode: {
        NetworkDiscoveryMode* d = toPtr<ONVIF::NetworkDiscoveryMode> (data);
        domElement              = d->toxml();
        d->deleteLater();
    } break;
    case device::MessageType::SetNetworkDNS: {
        NetworkDNS* d = toPtr<ONVIF::NetworkDNS> (data);
        domElement    = d->toxml();
        d->deleteLater();
    } break;
    case device::MessageType::SetNetworkHostname: {
        NetworkHostname* d = toPtr<ONVIF::NetworkHostname> (data);
        domElement         = d->toxml();
        d->deleteLater();
    } break;
    case device::MessageType::SetNetworkNTP: {
        NetworkNTP* d = toPtr<ONVIF::NetworkNTP> (data);
        domElement    = d->toxml();
        d->deleteLater();
    } break;
    default:
        msg->deleteLater();
        return;
    }

    msg->appendToBody(domElement);
    sendMessage(msg, messageType);
    msg->deleteLater();
}
