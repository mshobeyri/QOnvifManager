#include "message.h"
#include <QCryptographicHash>
#include <QDateTime>
#include <QDebug>
#include <QStringList>
#include <QTime>
#include <QUuid>
#include <time.h>

using namespace ONVIF;


QDomElement
ONVIF::hashToXml(const QString& name, const QHash<QString, QString>& hash) {
    QDomElement element = newElement(name);
    QHashIterator<QString, QString> i(hash);
    while (i.hasNext()) {
        i.next();
        element.appendChild(newElement(i.key(), i.value()));
    }
    return element;
}

QDomElement
ONVIF::listToXml(
    const QString& name, const QString& itemName, const QStringList& list) {
    QDomElement element = newElement(name);
    for (int i = 0; i < list.length(); i++) {
        element.appendChild(newElement(itemName, list.at(i)));
    }
    return element;
}

QDomElement
ONVIF::newElement(const QString& name, const QString& value) {
    QDomDocument doc;
    QDomElement  element = doc.createElement(name);
    if (value != "") {
        QDomText textNode = doc.createTextNode(value);
        element.appendChild(textNode);
    }
    doc.appendChild(element);
    return doc.firstChildElement();
}


Message*
Message::getOnvifSearchMessage() {
    QHash<QString, QString> namespaces;
    namespaces.insert("a", "http://schemas.xmlsoap.org/ws/2004/08/addressing");
    namespaces.insert("s", "http://www.w3.org/2003/05/soap-envelope");
    namespaces.insert("d", "http://schemas.xmlsoap.org/ws/2005/04/discovery");
    namespaces.insert("dn", "http://www.onvif.org/ver10/network/wsdl");
    namespaces.insert("dn", "http://www.onvif.org/ver10/network/wsdl");
    Message*    msg    = new Message(namespaces);
    QDomElement action = newElement(
        "a:Action", "http://schemas.xmlsoap.org/ws/2005/04/discovery/Probe");
    action.setAttribute("s:mustUnderstand","1");
    QDomElement message_id = newElement("a:MessageID", "uuid:" + msg->uuid());
    QDomElement replyTo = newElement("a:ReplyTo");
    QDomElement address = newElement("a:Address","http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous");
    replyTo.appendChild(address);
    QDomElement to =
        newElement("a:To", "urn:schemas-xmlsoap-org:ws:2005:04:discovery");
    to.setAttribute("s:mustUnderstand","1");
    msg->appendToHeader(action);
    msg->appendToHeader(message_id);
    msg->appendToHeader(replyTo);
    msg->appendToHeader(to);

    QDomElement probe = newElement("d:Probe");
    probe.setAttribute("xmlns","http://schemas.xmlsoap.org/ws/2005/04/discovery");
    QDomElement type = newElement("d:Types", "dn:NetworkVideoTransmitter");
    type.setAttribute("xmlns:d","http://schemas.xmlsoap.org/ws/2005/04/discovery");
    type.setAttribute("xmlns:dp0","http://www.onvif.org/ver10/network/wsdl");
    probe.appendChild(type);
//    probe.appendChild(newElement("d:Scopes"));
    msg->appendToBody(probe);

    return msg;
}
// QString
// base64_encode(QByteArray ba) {
//    return ba.toBase64();
//}

// QByteArray
// base64_decode(QByteArray ba) {
//    return QByteArray::fromBase64(ba);
//}

#define SOAP_WSSE_NONCELEN (20)

QString
nonceCalc() {
    int  nonceInt = qrand();
    char buf[SOAP_WSSE_NONCELEN];
    memset(buf, 1, SOAP_WSSE_NONCELEN);
    memcpy(buf, &nonceInt, sizeof(nonceInt));
    QByteArray nonceByteArray(buf, SOAP_WSSE_NONCELEN);
    QString    nonce(nonceByteArray.toBase64());
    return nonce;
}

QByteArray
sha1(QByteArray resBytes) {
    QCryptographicHash sha(QCryptographicHash::Sha1);
    sha.addData(resBytes);
    return sha.result();
}

QString
passwordDigest(QString& nonce, QString& dateTime, QString& password) {
    QByteArray res = QString(nonce + dateTime + password).toUtf8();
    return sha1(res).toBase64();
}

Message*
Message::getMessageWithUserInfo(
    QHash<QString, QString>& namespaces,
    const QString& name,
    const QString& passwd) {
    namespaces.insert(
        "wsse",
        "http://docs.oasis-open.org/wss/2004/01/"
        "oasis-200401-wss-wssecurity-secext-1.0.xsd");
    namespaces.insert(
        "wsu",
        "http://docs.oasis-open.org/wss/2004/01/"
        "oasis-200401-wss-wssecurity-utility-1.0.xsd");
    Message*    msg      = new Message(namespaces);
    QDomElement security = newElement("Security");
    security.setAttribute("s:mustUnderstand", "1");
    security.setAttribute(
        "xmlns",
        "http://docs.oasis-open.org/wss/2004/01/"
        "oasis-200401-wss-wssecurity-secext-1.0."
        "xsd");

    QDomElement usernameToken = newElement("wsse:UsernameToken");
    // usernameToken.setAttribute("wsu:Id", "UsernameToken-1");
    // QDateTime current = QDateTime::currentDateTime();
    QDateTime current = QDateTime::currentDateTime();
// current.setTime_t(0);
#if 0 /* PasswordText */
    QDomElement username = newElement("wsse:Username", name);
    QDomElement password = newElement("wsse:Password", passwd);
    password.setAttribute("Type", "http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-username-token-profile-1.0#PasswordText");
    usernameToken.appendChild(username);
    usernameToken.appendChild(password);
    usernameToken.appendChild(newElement("wsu:Created", current.toTimeSpec(Qt::UTC).toString("yyyy-MM-ddThh:mm:ss")));
#else /* PasswordDigest  */
    //    QDomElement username = newElement("wsse:Username", name);todo: i
    //    remove this line and add next line to handle not respond cams proble,

    QDomElement username = newElement("Username", name);
    usernameToken.appendChild(username);

    QString createdStr =
        QDateTime::currentDateTime().toTimeSpec(Qt::UTC).toString(
            "yyyy-MM-ddThh:mm:sssZ");
    usernameToken.appendChild(newElement("wsu:Created", createdStr));

    QString     nonceStr       = nonceCalc();
    QString     nonceBase64Str = nonceStr.toUtf8().toBase64();
    QDomElement nonceB64       = newElement("wsse:Nonce", nonceBase64Str);
    usernameToken.appendChild(nonceB64);

    QString passwordStr     = passwd;
    QString passwdDigestStr = passwordDigest(nonceStr, createdStr, passwordStr);

    QDomElement password = newElement("wsse:Password", passwdDigestStr);
    password.setAttribute(
        "Type",
        "http://docs.oasis-open.org/wss/2004/01/"
        "oasis-200401-wss-username-token-profile-1.0#"
        "PasswordDigest");
    usernameToken.appendChild(password);

#endif
#if 0
    QDomElement timestamp = newElement("wsu:Timestamp");
    timestamp.setAttribute("wsu:Id", "Timestamp-2");
    timestamp.appendChild(newElement("wsu:Created", current.toTimeSpec(Qt::UTC).toString("yyyy-MM-ddThh:mm:ss")));
    timestamp.appendChild(newElement("wsu:Expires", current.toTimeSpec(Qt::UTC).addSecs(10).toString("yyyy-MM-ddThh:mm:ss")));
#endif
    security.appendChild(usernameToken);
    // security.appendChild(timestamp);
    msg->appendToHeader(security);
    return msg;
}


      Message::Message(
          const QHash<QString, QString>& namespaces, QObject* parent)
    : QObject(parent) {
    this->mNamespaces = namespaces;
    mDoc.appendChild(mDoc.createProcessingInstruction(
        "xml", "version=\"1.0\" encoding=\"UTF-8\""));
    mEnv = mDoc.createElementNS(
        "http://www.w3.org/2003/05/soap-envelope", "s:Envelope");
    mHeader = mDoc.createElement("s:Header");
    mBody   = mDoc.createElement("s:Body");
}

QString
Message::toXmlStr() {
    QHashIterator<QString, QString> i(mNamespaces);
    while (i.hasNext()) {
        i.next();
        mEnv.setAttribute("xmlns:" + i.key(), i.value());
    }
    mEnv.appendChild(mHeader);
    mEnv.appendChild(mBody);
    mDoc.appendChild(mEnv);
    return mDoc.toString();
}

QString
Message::uuid() {
    QUuid id = QUuid::createUuid();
    return id.toString();
}

void
Message::appendToBody(const QDomElement& body) {
    mBody.appendChild(body);
}

void
Message::appendToHeader(const QDomElement& header) {
    mHeader.appendChild(header);
}
