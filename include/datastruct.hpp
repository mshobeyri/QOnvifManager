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
    }probeData;

    // device management
    struct Information {
        QString manufacturer;
        QString model;
        QString firmwareVersion;
        QString serialNumber;
        QString hardwareId;
    }information;

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
    }capabilities;

    struct DateTime {
        QDateTime utcTime;
        QDateTime localTime;
    }dateTime;

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
    }mediaConfig;
};
#endif // DATASTRUCT_HPP
