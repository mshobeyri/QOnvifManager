#include "qonvifdevice.hpp"
#include "devicemanagement.h"

QOnvifDevice::QOnvifDevice()
{
}

QOnvifDevice::QOnvifDevice(QString _serviceAddress, QString _userName, QString _password, QObject *_parent):
    QObject(_parent), iuserName(_userName), ipassword(_password)

{
    ideviceManagement = new ONVIF::DeviceManagement(
        _serviceAddress, iuserName, ipassword);
}

QOnvifDevice::~QOnvifDevice()
{
    delete ideviceManagement;
}

QOnvifDevice::DeviceProbeData QOnvifDevice::deviceProbeData()
{
    return ideviceProbeData;
}

void QOnvifDevice::setDeviceProbeData(QOnvifDevice::DeviceProbeData _probeData)
{
    ideviceProbeData = _probeData;
}

QOnvifDevice::DateTime
QOnvifDevice::deviceDateAndTime()
{
    QScopedPointer <ONVIF::SystemDateAndTime> systemDateAndTime(ideviceManagement->getSystemDateAndTime());
    idateAndTime.localTime = systemDateAndTime->localTime();
    idateAndTime.utcTime = systemDateAndTime->utcTime();
    return idateAndTime;
}

bool
QOnvifDevice::setDeviceDateAndTime(QDateTime _dateAndTime)
{
    ONVIF::SystemDateAndTime systemDateAndTime;
    systemDateAndTime.setlocalTime(_dateAndTime);
    ideviceManagement->setSystemDateAndTime(&systemDateAndTime);
    return true;
}

bool
QOnvifDevice::refreshDeviceCapabilities()
{
//    ONVIF::Capabilities* capabilities;
    QScopedPointer <ONVIF::Capabilities> capabilities (ideviceManagement->getCapabilitiesDevice());
    capabilities(*ideviceManagement->getCapabilitiesPtz());
//    capabilities  = ideviceManagement->getCapabilitiesDevice();
//    capabilities  = ideviceManagement->getCapabilitiesPtz();
//    capabilities  = ideviceManagement->getCapabilitiesImaging();
//    capabilities  = ideviceManagement->getCapabilitiesMedia();

    if (!capabilities)
        return false;

    ideviceCapabilities.accessPolicyConfig = capabilities->accessPolicyConfig();

    //ptz capabilities
    ideviceCapabilities.ptzAddress = capabilities->ptzXAddr();

    //image capabilities
    ideviceCapabilities.imagingXAddress = capabilities->imagingXAddr();

    //media capabilities
    ideviceCapabilities.mediaXAddress = capabilities->mediaXAddr();
    ideviceCapabilities.rtpMulticast = capabilities->rtpMulticast();
    ideviceCapabilities.rtpTcp = capabilities->rtpTcp();
    ideviceCapabilities.rtpRtspTcp = capabilities->rtpRtspTcp();

    //device capabilities
    ideviceCapabilities.deviceXAddr = capabilities->deviceXAddr();
    ideviceCapabilities.iPFilter = capabilities->iPFilter();
    ideviceCapabilities.zeroConfiguration = capabilities->zeroConfiguration();
    ideviceCapabilities.iPVersion6 = capabilities->iPVersion6();
    ideviceCapabilities.dynDNS = capabilities->dynDNS();
    ideviceCapabilities.discoveryResolve = capabilities->discoveryResolve();
    ideviceCapabilities.systemLogging = capabilities->systemLogging();
    ideviceCapabilities.firmwareUpgrade = capabilities->firmwareUpgrade();
    ideviceCapabilities.major = capabilities->major();
    ideviceCapabilities.minor = capabilities->minor();
    ideviceCapabilities.httpFirmwareUpgrade = capabilities->httpFirmwareUpgrade();
    ideviceCapabilities.httpSystemBackup = capabilities->httpSystemBackup();
    ideviceCapabilities.httpSystemLogging = capabilities->httpSystemLogging();
    ideviceCapabilities.httpSupportInformation = capabilities->httpSupportInformation();
    ideviceCapabilities.inputConnectors = capabilities->inputConnectors();
    ideviceCapabilities.relayOutputs = capabilities->relayOutputs();
    ideviceCapabilities.tls11 = capabilities->tls11();
    ideviceCapabilities.tls22 = capabilities->tls22();
    ideviceCapabilities.onboardKeyGeneration = capabilities->onboardKeyGeneration();
    ideviceCapabilities.accessPolicyConfig = capabilities->accessPolicyConfig();
    ideviceCapabilities.x509Token = capabilities->x509Token();
    ideviceCapabilities.samlToken = capabilities->samlToken();
    ideviceCapabilities.kerberosToken = capabilities->kerberosToken();
    ideviceCapabilities.relToken = capabilities->relToken();
    ideviceCapabilities.tls10 = capabilities->tls10();
    ideviceCapabilities.dot1x = capabilities->dot1x();
    ideviceCapabilities.remoteUserHanding = capabilities->remoteUserHanding();
    ideviceCapabilities.systemBackup = capabilities->systemBackup();
    ideviceCapabilities.discoveryBye = capabilities->discoveryBye();
    ideviceCapabilities.remoteDiscovery = capabilities->remoteDiscovery();

    return true;
}

bool QOnvifDevice::refreshDeviceInformation()
{
    QHash<QString, QString>  deviceInformationHash = ideviceManagement->getDeviceInformation();
    ideviceInformation.manufacturer = deviceInformationHash.value("mf");
    ideviceInformation.model = deviceInformationHash.value("model");
    ideviceInformation.firmwareVersion = deviceInformationHash.value("firmware_version");
    ideviceInformation.serialNumber = deviceInformationHash.value("serial_number");
    ideviceInformation.hardwareId = deviceInformationHash.value("hardware_id");
    return true;
}

bool
QOnvifDevice::resetFactoryDevice()
{
    return true;
}

bool
QOnvifDevice::rebootDevice()
{
    return true;
}
