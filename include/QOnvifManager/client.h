#ifndef ONVIF_CLIENT_H
#define ONVIF_CLIENT_H

#include <QObject>
#include <QNetworkReply>
namespace ONVIF
{
class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(const QString &url);
    QString sendData(const QString &data);
private:
    QString mUrl;
    bool mTimerIsTrue;
};
}

#endif // ONVIF_CLIENT_H
