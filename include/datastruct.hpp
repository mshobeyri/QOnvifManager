#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <QDateTime>
#include <QRect>
#include <qstring.h>

struct Data {
    struct ProbeData {
        QString endPointAddress;
        QString types;
        QString deviceIp;
        QString deviceServiceAddress;
        QString scopes;
        QString metadataVersion;
    } probeData;

    // device management
    struct Information {
        QString manufacturer;
        QString model;
        QString firmwareVersion;
        QString serialNumber;
        QString hardwareId;
    } information;

    struct Scopes {
        QString name;
        QString location;
        QString hardware;
    } scopes;

    struct Capabilities {
        // ptz capabilities
        QString ptzAddress;

        // imaging capabilities
        QString imagingXAddress;

        // media capabilities
        QString mediaXAddress;
        bool    rtpMulticast;
        bool    rtpTcp;
        bool    rtpRtspTcp;

        // public capabilities
        QString deviceXAddr;
        bool    iPFilter;
        bool    zeroConfiguration;
        bool    iPVersion6;
        bool    dynDNS;
        bool    discoveryResolve;
        bool    systemLogging;
        bool    firmwareUpgrade;
        int     major;
        bool    minor;
        bool    httpFirmwareUpgrade;
        bool    httpSystemBackup;
        bool    httpSystemLogging;
        bool    httpSupportInformation;
        int     inputConnectors;
        int     relayOutputs;
        bool    tls11;
        bool    tls22;
        bool    onboardKeyGeneration;
        bool    accessPolicyConfig;
        bool    x509Token;
        bool    samlToken;
        bool    kerberosToken;
        bool    relToken;
        bool    tls10;
        bool    dot1x;
        bool    remoteUserHanding;
        bool    systemBackup;
        bool    discoveryBye;
        bool    remoteDiscovery;
    } capabilities;
    struct Users {
        QString username;
        QString password;
        enum UserLevelType {
            Administrator,
            Operator,
            User,
            Anonymous,
            Extended
        };
        UserLevelType userLevel;
    } users;
    struct Network {
        struct Prtocols {
            QList<QString> networkProtocolsName;
            QList<bool>    networkProtocolsEnabled;
            QList<int>     networkProtocolsPort;
        } protocols;

        struct Interfaces {
            bool networkInfacesEnabled;
            bool autoNegotiation;
            int  speed;
            enum Duplex { Full, Half };
            Duplex  duplex;
            int     mtu;
            bool    ipv4Enabled;
            QString ipv4ManualAddress;
            int     ipv4ManualPrefixLength;
            bool    ipv4DHCP;
            QString networkInfacesName;
            QString hwAaddress;
            QString ipv4LinkLocalAddress;
            int     ipvLinkLocalPrefixLength;
            QString ipv4FromDHCPAddress;
            int     ipv4FromDHCPPrefixLength;
            bool    result;
        } interfaces;
    } network;
    struct Profiles {
        QList<QString> toKenPro;
        QList<bool>    fixed;
        QList<QString> namePro;
        QList<QString> nameVsc;
        QList<int>     useCountVsc;
        QList<QString> sourceTokenVsc;
        QList<QRect>   boundsVsc;
        QList<QString> nameVec;
        QList<int>     useCountVec;
        QList<QString> encodingVec;
        QList<int>     widthVec;
        QList<int>     heightVec;
        QList<int>     qualityVec;
        QList<int>     frameRateLimitVec;
        QList<int>     encodingIntervalVec;
        QList<int>     bitrateLimitVec;
        QList<int>     govLengthVec;
        QList<QString> h264ProfileVec;
        QList<QString> typeVec;
        QList<QString> ipv4AddressVec;
        QList<QString> ipv6AddressVec;
        QList<int>     portVec;
        QList<int>     ttlVec;
        QList<bool>    autoStartVec;
        QList<QString> sessionTimeoutVec;
        QList<QString> namePtz;
        QList<int>     useCountPtz;
        QList<QString> nodeToken;
        QList<QString> defaultAbsolutePantTiltPositionSpace;
        QList<QString> defaultAbsoluteZoomPositionSpace;
        QList<QString> defaultRelativePantTiltTranslationSpace;
        QList<QString> defaultRelativeZoomTranslationSpace;
        QList<QString> defaultContinuousPantTiltVelocitySpace;
        QList<QString> defaultContinuousZoomVelocitySpace;
        QList<QString> panTiltSpace;
        QList<int>     panTiltX;
        QList<int>     panTiltY;
        QList<QString> zoomSpace;
        QList<int>     zoomX;
        QList<QString> defaultPTZTimeout;
        QList<QString> panTiltUri;
        QList<int>     xRangeMinPt;
        QList<int>     xRangeMaxPt;
        QList<int>     yRangeMinPt;
        QList<int>     yRangeMaxPt;

        QList<QString> zoomUri;
        QList<int>     xRangeMinZm;
        QList<int>     xRangeMaxZm;

        QList<QString> nameMc;
        QList<int>     useCountMc;
        QList<bool>    status;
        QList<bool>    position;
        QList<QString> filter;
        QList<QString> subscriptionPolicy;
        QList<bool>    analytics;
        QList<QString> typeMc;
        QList<QString> ipv4AddressMc;
        QList<QString> ipv6AddressMc;
        QList<int>     portMc;
        QList<int>     ttlMc;
        QList<bool>    autoStartMc;
        QList<QString> sessionTimeoutMc;
    } profiles, profile720p, profileD1;

    struct DateTime {
        QDateTime utcTime;
        QDateTime localTime;
    } dateTime;

    // media management

    struct MediaConfig {

        struct Audio {

            struct EncodingOptions {
                QList<QList<int>> bitratList;
                QList<QList<int>> sampleRateList;
                enum Encoding { G711, G726, AAC };
                QList<Encoding> encoding;
            } encodingOptions;

            struct EncoderConfig {
                QList<QString> token;
                QList<QString> name;
                QList<int>     useCount;
                QList<QString> encoding;
                QList<int>     bitrate;
                QList<int>     sampleRate;
                QList<QString> type;
                QList<QString> ipv4Address;
                QList<QString> ipv6Address;
                QList<int>     port;
                QList<int>     ttl;
                QList<bool>    autoStart;
                QList<QString> sessionTimeout;

            } encodingConfig;
            struct SourceConfig {
                QList<QString> token;
                QList<QString> name;
                QList<int>     useCount;
                QList<QString> sourceToken;
            } sourceConfig;

        } audio;

        struct Video {
            struct StreamUri {
                QString uri;
                bool    invalidAfterConnect;
                bool    invalidAfterReboot;
                QString timeout;
            } streamUri;

            struct EncodingOptions {
                int        qualityRangeMin;
                int        qulityRangeMax;
                QList<int> resAvailableWidth;
                QList<int> resAvailableHeight;
                int        govLengthRangeMin;
                int        govLengthRangeMax;
                int        frameRateRangeMin;
                int        frameRateRangeMax;
                int        encodingIntervalRangeMin;
                int        encodingIntervalRangeMax;
                enum H264ProfilesSupported { Baseline, Main, Extended, High };
                QList<H264ProfilesSupported> h264ProfilesSupported;
            } encodingOptions;

            struct EncoderConfig {
                QList<QString> token;
                QList<QString> name;
                QList<int>     useCount;
                QList<QString> encoding;
                QList<int>     width;
                QList<int>     height;
                QList<int>     quality;
                QList<int>     frameRateLimit;
                QList<int>     encodingInterval;
                QList<int>     bitrateLimit;
                QList<int>     govLength;
                QList<QString> h264Profile;
                QList<QString> type;
                QList<QString> ipv4Address;
                QList<QString> ipv6Address;
                QList<int>     port;
                QList<int>     ttl;
                QList<bool>    autoStart;
                QList<QString> sessionTimeout;
            } encodingConfig;

            struct SourceConfig {
                QList<QString> name;
                QList<int>     useCount;
                QList<QString> sourceToken;
                QList<QRect>   bounds;
            } sourceConfig;

        } video;
    } mediaConfig;
};
#endif // DATASTRUCT_HPP
