#include "service.h"
#include <QFile>
#include <QNetworkReply>
#include <QUrl>

using namespace ONVIF;

Service::Service(
    const QString& wsdlUrl, const QString& username, const QString& password) {
    mUrl      = wsdlUrl;
    mUsername = username;
    mPassword = password;
}

Service::~Service() {}

void
Service::sendMessage(
    Message&            message,
    device::MessageType messageType,
    const QString&      namespaceKey) {
    sendMessage(&message, messageType, namespaceKey);
}

void
Service::sendMessage(
    Message*            message,
    device::MessageType messageType,
    const QString&      namespaceKey) {
    QString data = message->toXmlStr();

    QUrl            url(mUrl);
    QNetworkRequest request(url);
    request.setHeader(
        QNetworkRequest::ContentTypeHeader, "Content-Type: text/xml");
    QNetworkReply* reply = networkManager.post(request, data.toUtf8());
    connect(
        reply,
        &QNetworkReply::finished,
        reply,
        [this, reply, namespaceKey, messageType]() {
            QString result = reply->readAll();

            if (result != "") {
                QHash<QString, QString> names = namespaces(namespaceKey);
                emit messageParserReceived(
                    new MessageParser(result, names), messageType);
            }

            reply->deleteLater();
        });
}

Message*
Service::createMessage(QHash<QString, QString>& namespaces) {
    return Message::getMessageWithUserInfo(namespaces, mUsername, mPassword);
}
