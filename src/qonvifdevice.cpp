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
    QScopedPointer <ONVIF::Capabilities> capabilitiesDevice (ideviceManagement->getCapabilitiesDevice());

    ideviceCapabilities.accessPolicyConfig = capabilitiesDevice->accessPolicyConfig();
    ideviceCapabilities.deviceXAddr = capabilitiesDevice->deviceXAddr();
    ideviceCapabilities.iPFilter = capabilitiesDevice->iPFilter();
    ideviceCapabilities.zeroConfiguration = capabilitiesDevice->zeroConfiguration();
    ideviceCapabilities.iPVersion6 = capabilitiesDevice->iPVersion6();
    ideviceCapabilities.dynDNS = capabilitiesDevice->dynDNS();
    ideviceCapabilities.discoveryResolve = capabilitiesDevice->discoveryResolve();
    ideviceCapabilities.systemLogging = capabilitiesDevice->systemLogging();
    ideviceCapabilities.firmwareUpgrade = capabilitiesDevice->firmwareUpgrade();
    ideviceCapabilities.major = capabilitiesDevice->major();
    ideviceCapabilities.minor = capabilitiesDevice->minor();
    ideviceCapabilities.httpFirmwareUpgrade = capabilitiesDevice->httpFirmwareUpgrade();
    ideviceCapabilities.httpSystemBackup = capabilitiesDevice->httpSystemBackup();
    ideviceCapabilities.httpSystemLogging = capabilitiesDevice->httpSystemLogging();
    ideviceCapabilities.httpSupportInformation = capabilitiesDevice->httpSupportInformation();
    ideviceCapabilities.inputConnectors = capabilitiesDevice->inputConnectors();
    ideviceCapabilities.relayOutputs = capabilitiesDevice->relayOutputs();
    ideviceCapabilities.tls11 = capabilitiesDevice->tls11();
    ideviceCapabilities.tls22 = capabilitiesDevice->tls22();
    ideviceCapabilities.onboardKeyGeneration = capabilitiesDevice->onboardKeyGeneration();
    ideviceCapabilities.accessPolicyConfig = capabilitiesDevice->accessPolicyConfig();
    ideviceCapabilities.x509Token = capabilitiesDevice->x509Token();
    ideviceCapabilities.samlToken = capabilitiesDevice->samlToken();
    ideviceCapabilities.kerberosToken = capabilitiesDevice->kerberosToken();
    ideviceCapabilities.relToken = capabilitiesDevice->relToken();
    ideviceCapabilities.tls10 = capabilitiesDevice->tls10();
    ideviceCapabilities.dot1x = capabilitiesDevice->dot1x();
    ideviceCapabilities.remoteUserHanding = capabilitiesDevice->remoteUserHanding();
    ideviceCapabilities.systemBackup = capabilitiesDevice->systemBackup();
    ideviceCapabilities.discoveryBye = capabilitiesDevice->discoveryBye();
    ideviceCapabilities.remoteDiscovery = capabilitiesDevice->remoteDiscovery();

    //ptz capabilities
    QScopedPointer <ONVIF::Capabilities> capabilitiesPtz (ideviceManagement->getCapabilitiesDevice());

    ideviceCapabilities.ptzAddress = capabilitiesPtz->ptzXAddr();

    //image capabilities
    QScopedPointer <ONVIF::Capabilities> capabilitiesImage (ideviceManagement->getCapabilitiesDevice());

    ideviceCapabilities.imagingXAddress = capabilitiesImage->imagingXAddr();

    //media capabilities
    QScopedPointer <ONVIF::Capabilities> capabilitiesMedia (ideviceManagement->getCapabilitiesDevice());

    ideviceCapabilities.mediaXAddress = capabilitiesMedia->mediaXAddr();
    ideviceCapabilities.rtpMulticast = capabilitiesMedia->rtpMulticast();
    ideviceCapabilities.rtpTcp = capabilitiesMedia->rtpTcp();
    ideviceCapabilities.rtpRtspTcp = capabilitiesMedia->rtpRtspTcp();

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
