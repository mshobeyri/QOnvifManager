#ifndef ONVIF_DEVICEMANAGEMENT_H
#define ONVIF_DEVICEMANAGEMENT_H

#include "device_management/capabilities.h"
#include "device_management/networkdefaultgateway.h"
#include "device_management/networkdiscoverymode.h"
#include "device_management/networkdns.h"
#include "device_management/networkhostname.h"
#include "device_management/networkinterfaces.h"
#include "device_management/networkntp.h"
#include "device_management/networkprotocols.h"
#include "device_management/systemdateandtime.h"
#include "device_management/systemfactorydefault.h"
#include "device_management/systemreboot.h"
#include "device_management/systemscopes.h"
#include "device_management/user.h"
#include "service.h"
#include <QDateTime>

namespace ONVIF {
class DeviceManagement : public Service
{
    Q_OBJECT
public:
    explicit DeviceManagement(
        const QString& wsdlUrl,
        const QString& username,
        const QString& password);

    void getData(device::MessageType);
    void setData(device::MessageType, QVariant);

signals:

    void resultReceived(QVariant, device::MessageType);

protected:
    Message* newMessage();
    QHash<QString, QString> namespaces(const QString& key);

    void onMessageParserReceived(MessageParser*, device::MessageType);
};
}


#endif // DEVICEMANAGEMENT_H
