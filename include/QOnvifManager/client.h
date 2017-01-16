#ifndef ONVIF_CLIENT_H
#define ONVIF_CLIENT_H

#include <QObject>
#include <QNetworkReply>
namespace ONVIF {
    class Client : public QObject {
        Q_OBJECT
    public:
        explicit Client(const QString &url);
        QString sendData(const QString &data);
    private:
//        void waitForFinish(const QHttp &http);
        QString mUrl;
        bool mTimerIsTrue;

//    private slots:
//        void replyReadall(QNetworkReply* rp);
    };
}

#endif // ONVIF_CLIENT_H
