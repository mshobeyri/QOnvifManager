#ifndef ONVIF_SERVICE_H
#define ONVIF_SERVICE_H

#include <QNetworkAccessManager>
#include "message.h"
#include "messageparser.h"
#include "qonvifdevice.hpp"

namespace ONVIF {

template <class T> class VPtr
{
public:
    static T* asPtr(QVariant v)
    {
        return  (T *) v.value<void *>();
//        QObject *object = qvariant_cast<QObject*>(v);
//        return qobject_cast<T*>(object);
    }

    static QVariant asQVariant(T* ptr)
    {
        return qVariantFromValue((void *) ptr);
    }
};

class Service : public QObject {
    Q_OBJECT

public:
    explicit Service(const QString & wsdlUrl, const QString &username, const QString &password);

    ~Service();
    void sendMessage(Message &message, device::MessageType messageType, const QString &namespaceKey = "");
    void sendMessage(Message *message, device::MessageType messageType, const QString &namespaceKey = "");

signals:

    void messageParserReceived(MessageParser*, device::MessageType messageType);

protected:
    virtual QHash<QString, QString> namespaces(const QString &key) = 0;
    Message *createMessage(QHash<QString, QString> &namespaces);
private:
    QString mUsername, mPassword;
    QNetworkAccessManager networkManager;
    QString mUrl;
};
}


#endif // ONVIF_SERVICE_H
