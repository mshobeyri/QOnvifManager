#ifndef VIDEOENCODERCONFIGURATIONOPTIONS_H
#define VIDEOENCODERCONFIGURATIONOPTIONS_H
#include <QList>
#include <QObject>
namespace ONVIF {
class VideoEncoderConfigurationOptions : public QObject
{
    Q_OBJECT
    Q_ENUMS(H264ProfilesSupported)
public:
    explicit VideoEncoderConfigurationOptions(QObject* parent = NULL);
    virtual ~VideoEncoderConfigurationOptions();
    enum H264ProfilesSupported { Baseline, Main, Extended, High, Unknown };
    H264ProfilesSupported stringToEnum(QString s) {
        if (s == QString("Baseline"))
            return Baseline;
        if (s == QString("Main"))
            return Main;
        if (s == QString("Extended"))
            return Extended;
        if (s == QString("High"))
            return High;

        return Unknown;
    }

    int  qualityRangeMin() const;
    void setQualityRangeMin(int qualityRangeMin);

    int  qulityRangeMax() const;
    void setQulityRangeMax(int qulityRangeMax);

    int  govLengthRangeMin() const;
    void setGovLengthRangeMin(int govLengthRangeMin);

    int  govLengthRangeMax() const;
    void setGovLengthRangeMax(int govLengthRangeMax);

    int  bitRateRangeMin() const;
    void setBitRateRangeMin(int bitRateRangeMin);

    int  bitRateRangeMax() const;
    void setBitRateRangeMax(int bitRateRangeMax);


    int  frameRateRangeMinJpeg() const;
    void setFrameRateRangeMinJpeg(int frameRateRangeMinJpeg);

    int  frameRateRangeMaxJpeg() const;
    void setFrameRateRangeMaxJpeg(int frameRateRangeMaxJpeg);

    int  frameRateRangeMinH264() const;
    void setFrameRateRangeMinH264(int frameRateRangeMinH264);

    int  frameRateRangeMaxH264() const;
    void setFrameRateRangeMaxH264(int frameRateRangeMaxH264);


    int  encodingIntervalRangeMinJpeg() const;
    void setEncodingIntervalRangeMinJpeg(int encodingIntervalRangeMinJpeg);

    int  encodingIntervalRangeMaxJpeg() const;
    void setEncodingIntervalRangeMaxJpeg(int encodingIntervalRangeMaxJpeg);

    int  encodingIntervalRangeMinH264() const;
    void setEncodingIntervalRangeMinH264(int encodingIntervalRangeMinH264);

    int  encodingIntervalRangeMaxH264() const;
    void setEncodingIntervalRangeMaxH264(int encodingIntervalRangeMaxH264);


    QList<int> resAvailableWidthJpeg() const;
    void setResAvailableWidthJpeg(int resAvailableWidth);

    QList<int> resAvailableHeightJpeg() const;
    void setResAvailableHeightJpeg(int resAvailableHeight);

    QList<int> resAvailableWidthH264() const;
    void setResAvailableWidthH264(int resAvailableWidth);

    QList<int> resAvailableHeightH264() const;
    void setResAvailableHeightH264(int resAvailableHeight);

    QList<H264ProfilesSupported> getH264ProfilesSupported() const;
    void setH264ProfilesSupported(H264ProfilesSupported h264ProfilesSupported);


private:
    int m_qualityRangeMin;
    int m_qualityRangeMax;
    int m_govLengthRangeMin;
    int m_govLengthRangeMax;
    int m_bitRateRangeMin;
    int m_bitRateRangeMax;

    int m_frameRateRangeMinJpeg;
    int m_frameRateRangeMaxJpeg;
    int m_frameRateRangeMinH264;
    int m_frameRateRangeMaxH264;

    int m_encodingIntervalRangeMinJpeg;
    int m_encodingIntervalRangeMaxJpeg;
    int m_encodingIntervalRangeMinH264;
    int m_encodingIntervalRangeMaxH264;

    QList<int>                   m_resAvailableWidthJpeg;
    QList<int>                   m_resAvailableHeightJpeg;
    QList<int>                   m_resAvailableWidthH264;
    QList<int>                   m_resAvailableHeightH264;
    QList<H264ProfilesSupported> m_h264ProfilesSupported;
};
}
#endif // VIDEOENCODERCONFIGURATIONOPTIONS_H
