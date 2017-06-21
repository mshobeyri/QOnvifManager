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
    QHash<QString, QString> getDeviceInformation();
    QHash<QString, QString> getDeviceScopes();
    SystemDateAndTime* getSystemDateAndTime();
    void setSystemDateAndTime(SystemDateAndTime* systemDateAndTime);
    void setDeviceScopes(SystemScopes* systemScopes);
    void setSystemFactoryDefault(SystemFactoryDefault* systemFactoryDefault);
    void systemReboot(SystemReboot* systemReboot);
    Users*                 getUsers();
    NetworkInterfaces*     getNetworkInterfaces();
    NetworkProtocols*      getNetworkProtocols();
    NetworkDefaultGateway* getNetworkDefaultGateway();
    NetworkDiscoveryMode*  getNetworkDiscoverMode();
    NetworkDNS*            getNetworkDNS();
    NetworkHostname*       getNetworkHostname();
    NetworkNTP*            getNetworkNTP();

    void setNetworkInterfaces(NetworkInterfaces* networkInterfaces);
    void setNetworkProtocols(NetworkProtocols* networkProtocols);
    void setDefaultGateway(NetworkDefaultGateway* networkDefaultGateway);
    void setDiscoveryMode(NetworkDiscoveryMode* networkDiscoveryMode);
    void setDNS(NetworkDNS* networkDns);
    void setHostname(NetworkHostname* networkHostname);
    void setNTP(NetworkNTP* networkNtp);
    Capabilities* getCapabilitiesPtz();
    Capabilities* getCapabilitiesImaging();
    Capabilities* getCapabilitiesMedia();
    Capabilities* getCapabilitiesDevice();

protected:
    Message* newMessage();
    QHash<QString, QString> namespaces(const QString& key);
};
}


#endif // DEVICEMANAGEMENT_H
