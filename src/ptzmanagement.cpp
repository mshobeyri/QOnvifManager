#include "ptzmanagement.h"
#include <QDebug>

using namespace ONVIF;


PtzManagement::PtzManagement(
    const QString& wsdlUrl, const QString& username, const QString& password)
    : Service(wsdlUrl, username, password) {
    connect(
        this,
        &PtzManagement::messageParserReceived,
        this,
        &PtzManagement::onMessageParserReceived);
}

Message*
PtzManagement::newMessage() {
    QHash<QString, QString> names;
    names.insert("wsdl", "http://www.onvif.org/ver20/ptz/wsdl");
    names.insert("sch", "http://www.onvif.org/ver10/schema");
    names.insert("tptz", "http://www.onvif.org/ver20/ptz/wsdl");

    return createMessage(names);
}

QHash<QString, QString>
PtzManagement::namespaces(const QString& key) {
    QHash<QString, QString> names;
    Q_UNUSED(key)
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
PtzManagement::onMessageParserReceived(
    MessageParser* result, device::MessageType messageType) {
    if (result == NULL)
        return;

    QVariant var;

    switch (messageType) {
    case device::MessageType::Configurations: {
        Configurations* configurations = new Configurations();
        QXmlQuery*      query          = result->query();
        QString         value, xml;
        QDomDocument    doc;
        QDomNodeList    itemNodeList;
        QDomNode        node;
        QXmlResultItems items;
        QXmlItem        item;
        query->setQuery(
            result->nameSpace() + "doc($inputDocument)//tptz:PTZConfiguration");
        query->evaluateTo(&items);
        item = items.next();
        while (!item.isNull()) {
            query->setFocus(item);
            query->setQuery(result->nameSpace() + ".");
            query->evaluateTo(&xml);
            doc.setContent(xml);
            itemNodeList = doc.elementsByTagName("tptz:PTZConfiguration");
            for (int i = 0; i < itemNodeList.size(); i++) {
                node  = itemNodeList.at(i);
                value = node.toElement().attribute("token");
                configurations->setToken(value.trimmed());
            }

            query->setQuery(result->nameSpace() + "./tt:Name/string()");
            query->evaluateTo(&value);
            configurations->setName(value.trimmed());

            query->setQuery(result->nameSpace() + "./tt:UseCount/string()");
            query->evaluateTo(&value);
            configurations->setUseCount(value.trimmed().toInt());

            query->setQuery(result->nameSpace() + "./tt:NodeToken/string()");
            query->evaluateTo(&value);
            configurations->setNodeToken(value.trimmed());

            query->setQuery(
                result->nameSpace() +
                "./tt:DefaultAbsolutePantTiltPositionSpace/string()");
            query->evaluateTo(&value);
            configurations->setDefaultAbsolutePantTiltPositionSpace(
                value.trimmed());

            query->setQuery(
                result->nameSpace() +
                "./tt:DefaultAbsoluteZoomPositionSpace/string()");
            query->evaluateTo(&value);
            configurations->setDefaultAbsoluteZoomPositionSpace(
                value.trimmed());

            query->setQuery(
                result->nameSpace() +
                "./tt:DefaultRelativePanTiltTranslationSpace/string()");
            query->evaluateTo(&value);
            configurations->setDefaultRelativePanTiltTranslationSpace(
                value.trimmed());

            query->setQuery(
                result->nameSpace() +
                "./tt:DefaultRelativeZoomTranslationSpace/string()");
            query->evaluateTo(&value);
            configurations->setDefaultRelativeZoomTranslationSpace(
                value.trimmed());

            query->setQuery(
                result->nameSpace() +
                "./tt:DefaultContinuousPanTiltVelocitySpace/string()");
            query->evaluateTo(&value);
            configurations->setDefaultContinuousPanTiltVelocitySpace(
                value.trimmed());

            query->setQuery(
                result->nameSpace() +
                "./tt:DefaultContinuousZoomVelocitySpace/string()");
            query->evaluateTo(&value);
            configurations->setDefaultContinuousZoomVelocitySpace(
                value.trimmed());

            query->setQuery(
                result->nameSpace() + "./tt:DefaultPTZSpeed/tt:PanTilt");
            query->evaluateTo(&xml);
            doc.setContent(xml);
            itemNodeList = doc.elementsByTagName("tt:PanTilt");
            for (int i = 0; i < itemNodeList.size(); i++) {
                node  = itemNodeList.at(i);
                value = node.toElement().attribute("space");
                configurations->setPanTiltSpace(value.trimmed());

                value = node.toElement().attribute("y");
                configurations->setPanTiltY(value.trimmed().toFloat());

                value = node.toElement().attribute("x");
                configurations->setPanTiltX(value.trimmed().toFloat());
            }

            query->setQuery(
                result->nameSpace() + "./tt:DefaultPTZSpeed/tt:Zoom");
            query->evaluateTo(&xml);
            doc.setContent(xml);
            itemNodeList = doc.elementsByTagName("tt:Zoom");
            for (int i = 0; i < itemNodeList.size(); i++) {
                node  = itemNodeList.at(i);
                value = node.toElement().attribute("space");
                configurations->setZoomSpace(value.trimmed());

                value = node.toElement().attribute("x");
                configurations->setZoomX(value.trimmed().toFloat());
            }

            query->setQuery(
                result->nameSpace() + "./tt:DefaultPTZTimeout/string()");
            query->evaluateTo(&value);
            configurations->setDefaultPTZTimeout(value.trimmed());

            query->setQuery(
                result->nameSpace() +
                "./tt:PanTiltLimits/tt:Range/tt:URI/string()");
            query->evaluateTo(&value);
            configurations->setPanTiltRangeUri(value.trimmed());

            query->setQuery(
                result->nameSpace() +
                "./tt:PanTiltLimits/tt:Range/tt:XRange/tt:Min/string()");
            query->evaluateTo(&value);
            configurations->setPanTiltXRangeMin(value.trimmed().toFloat());

            query->setQuery(
                result->nameSpace() +
                "./tt:PanTiltLimits/tt:Range/tt:XRange/tt:Max/string()");
            query->evaluateTo(&value);
            configurations->setPanTiltXRangeMax(value.trimmed().toFloat());

            query->setQuery(
                result->nameSpace() +
                "./tt:PanTiltLimits/tt:Range/tt:YRange/tt:Min/string()");
            query->evaluateTo(&value);
            configurations->setPanTiltYRangeMin(value.trimmed().toFloat());

            query->setQuery(
                result->nameSpace() +
                "./tt:PanTiltLimits/tt:Range/tt:YRange/tt:Max/string()");
            query->evaluateTo(&value);
            configurations->setPanTiltYRangeMax(value.trimmed().toFloat());

            query->setQuery(
                result->nameSpace() +
                "./tt:ZoomLimits/tt:Range/tt:URI/string()");
            query->evaluateTo(&value);
            configurations->setZoomRangeUri(value.trimmed());

            query->setQuery(
                result->nameSpace() +
                "./tt:ZoomLimits/tt:Range/tt:XRange/tt:Min/string()");
            query->evaluateTo(&value);
            configurations->setZoomXRangeMin(value.trimmed().toFloat());

            query->setQuery(
                result->nameSpace() +
                "./tt:ZoomLimits/tt:Range/tt:XRange/tt:Max/string()");
            query->evaluateTo(&value);
            configurations->setZoomXRangeMax(value.trimmed().toFloat());

            item = items.next();
        }
        var = toQVariant<Configurations>(configurations);
    } break;
    case device::MessageType::Configuration: {
        Configuration* configuration = new Configuration();
        QXmlQuery*     query         = result->query();
        QDomNodeList   itemNodeList;
        QDomNode       node;
        QDomDocument   doc;
        QString        value, xml;
        query->setQuery(
            result->nameSpace() + "doc($inputDocument)//tptz:PTZConfiguration");
        query->evaluateTo(&xml);
        doc.setContent(xml);
        itemNodeList = doc.elementsByTagName("tptz:PTZConfiguration");
        for (int i = 0; i < itemNodeList.size(); i++) {
            node  = itemNodeList.at(i);
            value = node.toElement().attribute("token");
            configuration->setPtzConfigurationToken(value.trimmed());
        }
        configuration->setName(result->getValue("//tt:Name").trimmed());
        configuration->setUseCount(
            result->getValue("//tt:UseCount").trimmed().toInt());
        configuration->setNodeToken(
            result->getValue("//tt:NodeToken").trimmed());
        configuration->setDefaultAbsolutePantTiltPositionSpace(
            result->getValue("//tt:DefaultAbsolutePantTiltPositionSpace")
                .trimmed());
        configuration->setDefaultAbsoluteZoomPositionSpace(
            result->getValue("//tt:DefaultAbsoluteZoomPositionSpace")
                .trimmed());
        configuration->setDefaultContinuousPanTiltVelocitySpace(
            result->getValue("//DefaultContinuousPanTiltVelocitySpace")
                .trimmed());
        configuration->setDefaultContinuousZoomVelocitySpace(
            result->getValue("//tt:DefaultContinuousZoomVelocitySpace")
                .trimmed());
        configuration->setDefaultRelativePanTiltTranslationSpace(
            result->getValue("//tt:DefaultRelativePanTiltTranslationSpace")
                .trimmed());
        configuration->setDefaultRelativeZoomTranslationSpace(
            result->getValue("//tt:DefaultRelativeZoomTranslationSpace")
                .trimmed());
        query->setQuery(
            result->nameSpace() +
            "doc($inputDocument)//tt:DefaultPTZSpeed/tt:PanTilt");
        query->evaluateTo(&xml);
        doc.setContent(xml);
        itemNodeList = doc.elementsByTagName("tt:PanTilt");
        for (int i = 0; i < itemNodeList.size(); i++) {
            node  = itemNodeList.at(i);
            value = node.toElement().attribute("space");
            configuration->setPanTiltSpace(value.trimmed());
            value = node.toElement().attribute("y");
            configuration->setPanTiltY(value.trimmed().toFloat());
            value = node.toElement().attribute("x");
            configuration->setPanTiltX(value.trimmed().toFloat());
        }

        query->setQuery(
            result->nameSpace() +
            "doc($inputDocument)//tt:DefaultPTZSpeed/tt:Zoom");
        query->evaluateTo(&xml);
        doc.setContent(xml);
        itemNodeList = doc.elementsByTagName("tt:Zoom");
        for (int i = 0; i < itemNodeList.size(); i++) {
            node  = itemNodeList.at(i);
            value = node.toElement().attribute("space");
            configuration->setZoomSpace(value.trimmed());
            value = node.toElement().attribute("x");
            configuration->setZoomX(value.trimmed().toFloat());
        }
        configuration->setDefaultPTZTimeout(
            result->getValue("//tt:DefaultPTZTimeout").trimmed());
        configuration->setPanTiltUri(
            result->getValue("//tt:PanTiltLimits/tt:Range/tt:URI").trimmed());
        configuration->setPanTiltXRangeMin(
            result->getValue("//tt:PanTiltLimits/tt:Range/tt:XRange/tt:Min")
                .trimmed()
                .toFloat());
        configuration->setPanTiltXRangeMax(
            result->getValue("//tt:PanTiltLimits/tt:Range/tt:XRange/tt:Max")
                .trimmed()
                .toFloat());
        configuration->setPanTiltYRangeMax(
            result->getValue("//tt:PanTiltLimits/tt:Range/tt:YRange/tt:Min")
                .trimmed()
                .toFloat());
        configuration->setPanTiltYRangeMax(
            result->getValue("//tt:PanTiltLimits/tt:Range/tt:YRange/tt:Max")
                .trimmed()
                .toFloat());
        configuration->setZoomUri(
            result->getValue("//tt:ZoomLimits/tt:Range/tt:URI").trimmed());
        configuration->setZoomXRangeMin(
            result->getValue("//tt:ZoomLimits/tt:Range/tt:XRange/tt:Min")
                .trimmed()
                .toFloat());
        configuration->setZoomXRangeMax(
            result->getValue("//tt:ZoomLimits/tt:Range/tt:XRange/tt:Max")
                .trimmed()
                .toFloat());
        var = toQVariant<Configuration>(configuration);
    } break;
    case device::MessageType::Nodes: {
        Nodes*          nodes = new Nodes();
        QXmlQuery*      query = result->query();
        QXmlResultItems items;
        QXmlItem        item;
        QDomDocument    doc;
        QDomNodeList    itemNodeList;
        QDomNode        node;
        QString         value, xml;
        query->setQuery(
            result->nameSpace() + "doc($inputDocument)//tptz:PTZNode");
        query->evaluateTo(&items);
        item = items.next();
        while (!item.isNull()) {
            query->setFocus(item);
            query->setQuery(result->nameSpace() + ".");
            query->evaluateTo(&xml);
            doc.setContent(xml);
            itemNodeList = doc.elementsByTagName("tptz:PTZNode");
            for (int i = 0; i < itemNodeList.size(); i++) {
                node  = itemNodeList.at(i);
                value = node.toElement().attribute("token");
                nodes->setPtzNodeToken(value.trimmed());
            }
            query->setQuery(result->nameSpace() + "./tt:Name/string()");
            query->evaluateTo(&value);
            nodes->setName(value.trimmed());

            query->setQuery(
                result->nameSpace() + "./tt:SupportedPTZSpaces/"
                                      "tt:"
                                      "AbsolutePanTiltPositionSpace"
                                      "/tt:URI/string()");
            query->evaluateTo(&value);
            nodes->setAppsUri(value.trimmed());

            query->setQuery(
                result->nameSpace() + "./tt:SupportedPTZSpaces/"
                                      "tt:"
                                      "AbsolutePanTiltPositionSpace"
                                      "/tt:XRange/tt:Min/string()");
            query->evaluateTo(&value);
            nodes->setAppsXRangeMin(value.trimmed().toFloat());

            query->setQuery(
                result->nameSpace() + "./tt:SupportedPTZSpaces/"
                                      "tt:"
                                      "AbsolutePanTiltPositionSpace"
                                      "/tt:XRange/tt:Max/string()");
            query->evaluateTo(&value);
            nodes->setAppsXRangeMax(value.trimmed().toFloat());

            query->setQuery(
                result->nameSpace() + "./tt:SupportedPTZSpaces/"
                                      "tt:"
                                      "AbsolutePanTiltPositionSpace"
                                      "/tt:YRange/tt:Min/string()");
            query->evaluateTo(&value);
            nodes->setAppsYRangeMin(value.trimmed().toFloat());

            query->setQuery(
                result->nameSpace() + "./tt:SupportedPTZSpaces/"
                                      "tt:"
                                      "AbsolutePanTiltPositionSpace"
                                      "/tt:YRange/tt:Max/string()");
            query->evaluateTo(&value);
            nodes->setAppsYRangeMax(value.trimmed().toFloat());

            query->setQuery(
                result->nameSpace() + "./tt:SupportedPTZSpaces/"
                                      "tt:"
                                      "AbsoluteZoomPositionSpace/"
                                      "tt:URI/string()");
            query->evaluateTo(&value);
            nodes->setAzpsUri(value.trimmed());

            query->setQuery(
                result->nameSpace() + "./tt:SupportedPTZSpaces/"
                                      "tt:"
                                      "AbsoluteZoomPositionSpace/"
                                      "tt:XRange/tt:Min/string()");
            query->evaluateTo(&value);
            nodes->setAzpsXRangeMin(value.trimmed().toFloat());

            query->setQuery(
                result->nameSpace() + "./tt:SupportedPTZSpaces/"
                                      "tt:"
                                      "AbsoluteZoomPositionSpace/"
                                      "tt:XRange/tt:Max/string()");
            query->evaluateTo(&value);
            nodes->setAzpsXRangeMax(value.trimmed().toFloat());

            query->setQuery(
                result->nameSpace() + "./tt:SupportedPTZSpaces/"
                                      "tt:"
                                      "RelativePanTiltTranslationSp"
                                      "ace/tt:URI/string()");
            query->evaluateTo(&value);
            nodes->setRptsUri(value.trimmed());

            query->setQuery(
                result->nameSpace() + "./tt:SupportedPTZSpaces/"
                                      "tt:RelativePanTiltTranslationSpace/"
                                      "tt:XRange/tt:Min/string()");
            query->evaluateTo(&value);
            nodes->setRptsXRangeMin(value.trimmed().toFloat());

            query->setQuery(
                result->nameSpace() + "./tt:SupportedPTZSpaces/"
                                      "tt:RelativePanTiltTranslationSpace/"
                                      "tt:XRange/tt:Max/string()");
            query->evaluateTo(&value);
            nodes->setRptsXRangeMax(value.trimmed().toFloat());

            query->setQuery(
                result->nameSpace() + "./tt:SupportedPTZSpaces/"
                                      "tt:RelativePanTiltTranslationSpace/"
                                      "tt:YRange/tt:Min/string()");
            query->evaluateTo(&value);
            nodes->setRptsYRangeMin(value.trimmed().toFloat());

            query->setQuery(
                result->nameSpace() + "./tt:SupportedPTZSpaces/"
                                      "tt:RelativePanTiltTranslationSpace/"
                                      "tt:YRange/tt:Max/string()");
            query->evaluateTo(&value);
            nodes->setRptsYRangeMax(value.trimmed().toFloat());

            query->setQuery(
                result->nameSpace() + "./tt:SupportedPTZSpaces/"
                                      "tt:"
                                      "RelativeZoomTranslationSpace"
                                      "/tt:URI/string()");
            query->evaluateTo(&value);
            nodes->setRztsUri(value.trimmed());

            query->setQuery(
                result->nameSpace() + "./tt:SupportedPTZSpaces/"
                                      "tt:"
                                      "RelativeZoomTranslationSpace"
                                      "/tt:XRange/tt:Min/string()");
            query->evaluateTo(&value);
            nodes->setRztsXRangeMin(value.trimmed().toFloat());

            query->setQuery(
                result->nameSpace() + "./tt:SupportedPTZSpaces/"
                                      "tt:"
                                      "RelativeZoomTranslationSpace"
                                      "/tt:XRange/tt:Max/string()");
            query->evaluateTo(&value);
            nodes->setRztsXRangeMax(value.trimmed().toFloat());

            query->setQuery(
                result->nameSpace() + "./tt:SupportedPTZSpaces/"
                                      "tt:"
                                      "ContinuousPanTiltVelocitySpa"
                                      "ce/tt:URI/string()");
            query->evaluateTo(&value);
            nodes->setCpvsUri(value.trimmed());

            query->setQuery(
                result->nameSpace() + "./tt:SupportedPTZSpaces/"
                                      "tt:ContinuousPanTiltVelocitySpace/"
                                      "tt:XRange/tt:Min/string()");
            query->evaluateTo(&value);
            nodes->setCpvsXRangeMin(value.trimmed().toFloat());

            query->setQuery(
                result->nameSpace() + "./tt:SupportedPTZSpaces/"
                                      "tt:ContinuousPanTiltVelocitySpace/"
                                      "tt:XRange/tt:Max/string()");
            query->evaluateTo(&value);
            nodes->setCpvsXRangeMax(value.trimmed().toFloat());

            query->setQuery(
                result->nameSpace() + "./tt:SupportedPTZSpaces/"
                                      "tt:ContinuousPanTiltVelocitySpace/"
                                      "tt:YRange/tt:Min/string()");
            query->evaluateTo(&value);
            nodes->setCpvsYRangeMin(value.trimmed().toFloat());

            query->setQuery(
                result->nameSpace() + "./tt:SupportedPTZSpaces/"
                                      "tt:ContinuousPanTiltVelocitySpace/"
                                      "tt:YRange/tt:Max/string()");
            query->evaluateTo(&value);
            nodes->setCpvsYRangeMax(value.trimmed().toFloat());

            query->setQuery(
                result->nameSpace() + "./tt:SupportedPTZSpaces/"
                                      "tt:"
                                      "ContinuousZoomVelocitySpace/"
                                      "tt:URI/string()");
            query->evaluateTo(&value);
            nodes->setCzvsUri(value.trimmed());

            query->setQuery(
                result->nameSpace() + "./tt:SupportedPTZSpaces/"
                                      "tt:"
                                      "ContinuousZoomVelocitySpace/"
                                      "tt:XRange/tt:Min/string()");
            query->evaluateTo(&value);
            nodes->setCzvsXRangeMin(value.trimmed().toFloat());

            query->setQuery(
                result->nameSpace() + "./tt:SupportedPTZSpaces/"
                                      "tt:"
                                      "ContinuousZoomVelocitySpace/"
                                      "tt:XRange/tt:Max/string()");
            query->evaluateTo(&value);
            nodes->setCzvsXRangeMax(value.trimmed().toFloat());

            query->setQuery(
                result->nameSpace() +
                "./tt:SupportedPTZSpaces/tt:PanTiltSpeedSpace/tt:URI/string()");
            query->evaluateTo(&value);
            nodes->setPssUri(value.trimmed());

            query->setQuery(
                result->nameSpace() + "./tt:SupportedPTZSpaces/"
                                      "tt:PanTiltSpeedSpace/"
                                      "tt:XRange/tt:Min/string()");
            query->evaluateTo(&value);
            nodes->setPssXRangeMin(value.trimmed().toFloat());

            query->setQuery(
                result->nameSpace() + "./tt:SupportedPTZSpaces/"
                                      "tt:PanTiltSpeedSpace/"
                                      "tt:XRange/tt:Max/string()");
            query->evaluateTo(&value);
            nodes->setPssXRangeMax(value.trimmed().toFloat());

            query->setQuery(
                result->nameSpace() +
                "./tt:SupportedPTZSpaces/tt:ZoomSpeedSpace/tt:URI/string()");
            query->evaluateTo(&value);
            nodes->setZssUri(value.trimmed());

            query->setQuery(
                result->nameSpace() + "./tt:SupportedPTZSpaces/"
                                      "tt:ZoomSpeedSpace/tt:XRange/"
                                      "tt:Min/string()");
            query->evaluateTo(&value);
            nodes->setZssXRangeMin(value.trimmed().toFloat());

            query->setQuery(
                result->nameSpace() + "./tt:SupportedPTZSpaces/"
                                      "tt:ZoomSpeedSpace/tt:XRange/"
                                      "tt:Max/string()");
            query->evaluateTo(&value);
            nodes->setZssXRangeMax(value.trimmed().toFloat());

            query->setQuery(
                result->nameSpace() + "./tt:MaximumNumberOfPresets/string()");
            query->evaluateTo(&value);
            nodes->setMaximumNumberOfPresets(value.trimmed().toInt());

            query->setQuery(
                result->nameSpace() + "./tt:HomeSupported/string()");
            query->evaluateTo(&value);
            nodes->setHomeSupported(value.trimmed() == "true" ? true : false);
            item = items.next();
        }
        var = toQVariant<Nodes>(nodes);
    } break;
    case device::MessageType::Node: {
        Node*        node  = new Node();
        QXmlQuery*   query = result->query();
        QDomNodeList itemNodeList;
        QDomNode     node1;
        QDomDocument doc;
        QString      value, xml;
        query->setQuery(
            result->nameSpace() + "doc($inputDocument)//tptz:PTZNode");
        query->evaluateTo(&xml);
        doc.setContent(xml);
        itemNodeList = doc.elementsByTagName("tptz:PTZNode");
        for (int i = 0; i < itemNodeList.size(); i++) {
            node1 = itemNodeList.at(i);
            value = node1.toElement().attribute("token");
            node->setPtzNodeToken(value.trimmed());
        }

        node->setName(result->getValue("//tt:Name").trimmed());
        node->setAbsolutePanTiltPositionSpaceUri(
            result
                ->getValue("//tt:SupportedPTZSpaces/"
                           "tt:AbsolutePanTiltPositionSpace/tt:URI")
                .trimmed());
        node->setAbsolutePanTiltPositionSpaceXRangeMin(
            result
                ->getValue("//tt:SupportedPTZSpaces/"
                           "tt:AbsolutePanTiltPositionSpace/tt:XRange/tt:Min")
                .trimmed()
                .toInt());
        node->setAbsolutePanTiltPositionSpaceXRangeMax(
            result
                ->getValue("//tt:SupportedPTZSpaces/"
                           "tt:AbsolutePanTiltPositionSpace/tt:XRange/tt:Max")
                .trimmed()
                .toInt());
        node->setAbsolutePanTiltPositionSpaceYRangeMin(
            result
                ->getValue("//tt:SupportedPTZSpaces/"
                           "tt:AbsolutePanTiltPositionSpace/tt:YRange/tt:Min")
                .trimmed()
                .toInt());
        node->setAbsolutePanTiltPositionSpaceYRangeMax(
            result
                ->getValue("//tt:SupportedPTZSpaces/"
                           "tt:AbsolutePanTiltPositionSpace/tt:YRange/tt:Max")
                .trimmed()
                .toInt());
        node->setAbsoluteZoomPositionSpaceUri(
            result
                ->getValue("//tt:SupportedPTZSpaces/"
                           "tt:AbsoluteZoomPositionSpace/tt:URI")
                .trimmed());
        node->setAbsoluteZoomPositionSpaceXRangeMin(
            result
                ->getValue("//tt:SupportedPTZSpaces/"
                           "tt:AbsoluteZoomPositionSpace/tt:XRange/tt:Min")
                .trimmed()
                .toInt());
        node->setAbsoluteZoomPositionSpaceXRangeMax(
            result
                ->getValue("//tt:SupportedPTZSpaces/"
                           "tt:AbsoluteZoomPositionSpace/tt:XRange/tt:Max")
                .trimmed()
                .toInt());
        node->setRelativePanTiltTranslationSpaceUri(
            result
                ->getValue("//tt:SupportPTZSpaces/"
                           "tt:RelativePanTiltTranslationSpaces/tt:URI")
                .trimmed());
        node->setRelativePanTiltTranslationSpaceXRangeMin(
            result
                ->getValue("//tt:SupportPTZSpace/"
                           "tt:RelativePanTiltTranslationSpaces/tt:XRange/"
                           "tt:Min")
                .trimmed()
                .toInt());
        node->setRelativePanTiltTranslationSpaceXRangeMax(
            result
                ->getValue("//tt:SupportPTZSpace/"
                           "tt:RelativePanTiltTranslationSpaces/tt:XRange/"
                           "tt:Max")
                .trimmed()
                .toInt());
        node->setRelativePanTiltTranslationSpaceYRangeMin(
            result
                ->getValue("//tt:SupportPTZSpace/"
                           "tt:RelativePanTiltTranslationSpaces/tt:YRange/"
                           "tt:Min")
                .trimmed()
                .toInt());
        node->setRelativePanTiltTranslationSpaceYRangeMax(
            result
                ->getValue("//tt:SupportPTZSpace/"
                           "tt:RelativePanTiltTranslationSpaces/tt:YRange/"
                           "tt:Max")
                .trimmed()
                .toInt());
        node->setRelativeZoomTranslationSpaceUri(
            result
                ->getValue("//tt:SupportPTZSpace/"
                           "tt:RelativePanTiltTranslationSpaces/tt:URI")
                .trimmed());
        node->setRelativeZoomTranslationSpaceXRangeMin(
            result
                ->getValue("//tt:SupportPTZSpace/"
                           "tt:RelativePanTiltTranslationSpaces/tt:XRange/"
                           "tt:Min")
                .trimmed()
                .toInt());
        node->setRelativeZoomTranslationSpaceXRangeMax(
            result
                ->getValue("//tt:SupportPTZSpace/"
                           "tt:RelativePanTiltTranslationSpaces/tt:XRange/"
                           "tt:Max")
                .trimmed()
                .toInt());
        node->setContinuousPanTiltVelocityUri(
            result
                ->getValue("//tt:SupportPTZSpace/"
                           "tt:ContinuousPanTiltVelocitySpace/tt:URI")
                .trimmed());
        node->setContinuousPanTiltVelocityXRangeMin(
            result
                ->getValue("//tt:SupportPTZSpace/"
                           "tt:ContinuousPanTiltVelocitySpace/tt:XRange/tt:Min")
                .trimmed()
                .toInt());
        node->setContinuousPanTiltVelocityXRangeMax(
            result
                ->getValue("//tt:SupportPTZSpace/"
                           "tt:ContinuousPanTiltVelocitySpace/tt:XRange/tt:Max")
                .trimmed()
                .toInt());
        node->setContinuousPanTiltVelocityYRangeMin(
            result
                ->getValue("//tt:SupportPTZSpace/"
                           "tt:ContinuousPanTiltVelocitySpace/tt:YRange/tt:Min")
                .trimmed()
                .toInt());
        node->setContinuousPanTiltVelocityYRangeMax(
            result
                ->getValue("//tt:SupportPTZSpace/"
                           "tt:ContinuousPanTiltVelocitySpace/tt:YRange/tt:Max")
                .trimmed()
                .toInt());
        node->setContinuousZoomVelocitySpaceUri(
            result
                ->getValue("//tt:SupportPTZSpace/"
                           "tt:ContinuousZoomVelocitySpace/tt:URI")
                .trimmed());
        node->setContinuousZoomVelocitySpaceXRangeMin(
            result
                ->getValue("//tt:SupportPTZSpace/"
                           "tt:ContinuousZoomVelocitySpace/tt:XRange/tt:Min")
                .toInt());
        node->setContinuousZoomVelocitySpaceXRangeMax(
            result
                ->getValue("//tt:SupportPTZSpace/"
                           "tt:ContinuousZoomVelocitySpace/tt:XRange/tt:Max")
                .toInt());
        node->setPanTiltSpeedSpaceUri(
            result->getValue("//tt:SupportPTZSpace/tt:PanTiltSpeedSpace/tt:URI")
                .trimmed());
        node->setPanTiltSpeedSpaceXRangeMin(
            result
                ->getValue(
                    "//tt:SupportPTZSpace/tt:PanTiltSpeedSpace/XRange/tt:Min")
                .trimmed()
                .toInt());
        node->setPanTiltSpeedSpaceXRangeMax(
            result
                ->getValue(
                    "//tt:SupportPTZSpace/tt:PanTiltSpeedSpace/XRange/tt:Max")
                .trimmed()
                .toInt());
        node->setZoomSpeedSpaceUri(
            result->getValue("//tt:SupportPTZSpace/tt:ZoomSpeedSpace/tt:URI")
                .trimmed());
        node->setZoomSpeedSpaceXRangeMin(
            result->getValue("//tt:SupportPTZSpace/tt:ZoomSpeedSpace/tt:Min")
                .trimmed()
                .toInt());
        node->setZoomSpeedSpaceXRangeMax(
            result->getValue("//tt:SupportPTZSpace/tt:ZoomSpeedSpace/tt:Max")
                .trimmed()
                .toInt());
        node->setMaximumNumberOfPresets(
            result->getValue("//tt:MaximumNumberOfPresets").trimmed().toInt());
        node->setHomeSupport(
            result->getValue("//tt:HomeSupported").trimmed() == "true" ? true
                                                                       : false);
        var = toQVariant<Node>(node);
    } break;
    case device::MessageType::Presets: {
        Presets*        presets = new Presets();
        QXmlQuery*      query   = result->query();
        QXmlResultItems items;
        QXmlItem        item;
        QString         value, xml;
        QDomDocument    doc;
        QDomNodeList    itemNodeList;
        QDomNode        node;
        query->setQuery(
            result->nameSpace() + "doc($inputDocument)//tptz:Preset");
        query->evaluateTo(&items);
        item = items.next();
        while (!item.isNull()) {
            query->setFocus(item);
            query->setQuery(result->nameSpace() + ".");
            query->evaluateTo(&xml);
            doc.setContent(xml);
            itemNodeList = doc.elementsByTagName("tptz:Preset");
            for (int i = 0; i < itemNodeList.size(); i++) {
                node  = itemNodeList.at(i);
                value = node.toElement().attribute("token");
                presets->setToken(value.trimmed());
            }
            query->setQuery(result->nameSpace() + "./tt:Name/string()");
            query->evaluateTo(&value);
            presets->setName(value.trimmed());
            item = items.next();
        }
        var = toQVariant<Presets>(presets);
    } break;
    case device::MessageType::RemovePreset: {
        bool r = false;
        if (result->find("//tptz:RemovePresetResponse"))
            r = true;
        var   = qVariantFromValue(r);
    } break;
    case device::MessageType::SetPreset: {
        bool r = false;
        if (result->find("//tptz:SetPresetResponse"))
            r = true;
        var   = qVariantFromValue(r);
    } break;
    case device::MessageType::ContinuousMove: {
        bool r = false;
        if (result->find("//tptz:ContinuousMoveResponse"))
            r = true;
        var   = qVariantFromValue(r);
    } break;
    case device::MessageType::AbsoluteMove: {
        bool r = false;
        if (result->find("//tptz:AbsoluteMoveResponse"))
            r = true;
        var   = qVariantFromValue(r);
    } break;
    case device::MessageType::RelativeMove: {
        bool r = false;
        if (result->find("//tptz:RelativeMoveResponse"))
            r = true;
        var   = qVariantFromValue(r);
    } break;
    case device::MessageType::Stop: {
        bool r = false;
        if (result->find("//tptz:StopResponse"))
            r = true;
        var   = qVariantFromValue(r);
    } break;
    case device::MessageType::GotoPreset: {
        bool r = false;
        if (result->find("//tptz:GotoPresetResponse"))
            r = true;
        var   = qVariantFromValue(r);
    } break;
    case device::MessageType::GotoHomePosition: {
        bool r = false;
        if (result->find("//tptz:GotoHomePositionResponse"))
            r = true;
        var   = qVariantFromValue(r);
    } break;
    case device::MessageType::SetHomePosition: {
        bool r = false;
        if (result->find("//tptz:SetHomePositionResponse"))
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
PtzManagement::getData(
    device::MessageType messageType, QVariantList parameters) {
    Message* msg = newMessage();

    switch (messageType) {
    case device::MessageType::Configurations:

        msg->appendToBody(newElement("wsdl:GetConfigurations"));

        break;
    case device::MessageType::Configuration: {
        QString token = parameters.isEmpty() ? "" : parameters.at(0).toString();
        QDomElement getConfiguration = newElement("wsdl:GetConfiguration");
        QDomElement ptzConfigurationToken =
            newElement("wsdl:PTZConfigurationToken", token);
        getConfiguration.appendChild(ptzConfigurationToken);
        msg->appendToBody(getConfiguration);
    } break;
    case device::MessageType::Nodes:

        msg->appendToBody(newElement("wsdl:GetNodes"));

        break;
    case device::MessageType::Node: {
        QString ptzNodeToken =
            parameters.isEmpty() ? "" : parameters.at(0).toString();
        QDomElement getNode   = newElement("wsdl:GetNode");
        QDomElement nodeToken = newElement("wsdl:NodeToken", ptzNodeToken);
        getNode.appendChild(nodeToken);
        msg->appendToBody(getNode);
    } break;
    case device::MessageType::Presets: {
        QString token = parameters.isEmpty() ? "" : parameters.at(0).toString();
        QDomElement getPresets   = newElement("wsdl:GetPresets");
        QDomElement profileToken = newElement("wsdl:ProfileToken", token);
        getPresets.appendChild(profileToken);
        msg->appendToBody(getPresets);
    } break;
    default:
        msg->deleteLater();
        return;
    }

    sendMessage(msg, messageType);
    msg->deleteLater();
}

void
PtzManagement::setData(device::MessageType messageType, QVariant data) {
    Message*    msg = newMessage();
    QDomElement domElement;

    switch (messageType) {
    case device::MessageType::RemovePreset: {
        RemovePreset* d = toPtr<ONVIF::RemovePreset>(data);
        domElement      = d->toxml();
        d->deleteLater();
    } break;
    case device::MessageType::SetPreset: {
        Preset* d  = toPtr<ONVIF::Preset>(data);
        domElement = d->toxml();
        d->deleteLater();
    } break;
    case device::MessageType::ContinuousMove: {
        ContinuousMove* d = toPtr<ONVIF::ContinuousMove>(data);
        domElement        = d->toxml();
        d->deleteLater();
    } break;
    case device::MessageType::AbsoluteMove: {
        AbsoluteMove* d = toPtr<ONVIF::AbsoluteMove>(data);
        domElement      = d->toxml();
        d->deleteLater();
    } break;
    case device::MessageType::RelativeMove: {
        RelativeMove* d = toPtr<ONVIF::RelativeMove>(data);
        domElement      = d->toxml();
        d->deleteLater();
    } break;
    case device::MessageType::Stop: {
        Stop* d    = toPtr<ONVIF::Stop>(data);
        domElement = d->toxml();
        d->deleteLater();
    } break;
    case device::MessageType::GotoPreset: {
        GotoPreset* d = toPtr<ONVIF::GotoPreset>(data);
        domElement    = d->toxml();
        d->deleteLater();
    } break;
    case device::MessageType::GotoHomePosition: {
        GotoHomePosition* d = toPtr<ONVIF::GotoHomePosition>(data);
        domElement          = d->toxml();
        d->deleteLater();
    } break;
    case device::MessageType::SetHomePosition: {
        HomePosition* d = toPtr<ONVIF::HomePosition>(data);
        domElement      = d->toxml();
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
