#include "client.h"
#include <QEventLoop>
#include <QUrl>
#include <QDebug>
#include <QTimer>
#include <QThread>
#include <QNetworkAccessManager>
#include <QUrlQuery>

using namespace ONVIF;

Client::Client(const QString &url)
{
    mUrl = url;
}

QString Client::sendData(const QString &data)
{

    QNetworkAccessManager* networkManager = new QNetworkAccessManager(this);

    QUrl url(mUrl);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"Content-Type: text/xml");

    QNetworkReply *reply = networkManager->post(request, data.toLatin1());
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    return reply->readAll();
}
