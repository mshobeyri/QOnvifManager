#include "client.h"
#include <QEventLoop>
#include <QUrl>
#include <QDebug>
#include <QTimer>
#include <QThread>
#include <QNetworkAccessManager>
#include <QUrlQuery>

using namespace ONVIF;

Client::Client(const QString &url) {
    mUrl = url;
}
/*
QString Client::sendData(const QString &data) {
    QHttp http;

    http.ignoreSslErrors();
    QUrl url(mUrl);
    if (url.port() >= 655535 || url.port() <= 0)
    {
        http.setHost(url.host());
    }else
    {
        http.setHost(url.host(), url.port());
    }
    http.post(url.path(), data.toUtf8());
    waitForFinish(http);

    if(http.error() != QHttp::NoError || mTimerIsTrue == true) {
        return "";
    }

    return QString(http.readAll());
}

void Client::waitForFinish(const QHttp &http) {
    QEventLoop loop;
    QTimer timer;
    timer.setSingleShot(true);
    mTimerIsTrue = false;
    connect(&http, SIGNAL(done(bool)), &loop, SLOT(quit()));
    connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    timer.start(2000);
    loop.exec();
    if (timer.isActive())
    {
        mTimerIsTrue  = false;
    }else
    {
        mTimerIsTrue  = true;
    }
}
*/


QString Client::sendData(const QString &data) {


//    QFile file("/home/mehrdad/Desktop/file8");
//    if(!file.open(QIODevice::ReadOnly)) {
//        qDebug() << "err";
//    }

    QNetworkAccessManager* networkManager = new QNetworkAccessManager(this);

//    connect(networkManager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyReadall(QNetworkReply*)));

    QUrl url(mUrl);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"Content-Type: text/xml");

    QNetworkReply *reply = networkManager->post(request, data.toLatin1());

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    return reply->readAll();
}

//void Client::replyReadall(QNetworkReply *rp)
//{
//    qDebug()<<"sss:" << rp->readAll();
//}

//void Client::waitForFinish(const QHttp &http) {
//    QEventLoop loop;
//    QTimer timer;
//    timer.setSingleShot(true);
//    mTimerIsTrue = false;
//    connect(&http, SIGNAL(done(bool)), &loop, SLOT(quit()));
//    connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
//    timer.start(2000);
//    loop.exec();
//    if (timer.isActive())
//    {
//        mTimerIsTrue  = false;
//    }else
//    {
//        mTimerIsTrue  = true;
//    }
//}
