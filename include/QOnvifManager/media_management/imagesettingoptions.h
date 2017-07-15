#ifndef IMAGESETTINGOPTIONS_H
#define IMAGESETTINGOPTIONS_H
#include <QObject>

namespace ONVIF {
class ImageSettingOptions : public QObject
{
public:
    ImageSettingOptions(QObject* parent = NULL);

    int brightnessMax() const
    {
        return m_brightnessMax;
    }
    void setBrightnessMax(int brightnessMax)
    {
        m_brightnessMax = brightnessMax;
    }

    int brightnessMin() const
    {
        return m_brightnessMin;
    }
    void setBrightnessMin(int brightnessMin)
    {
        m_brightnessMin = brightnessMin;
    }

    int colorSaturationMax() const
    {
        return m_colorSaturationMax;
    }
    void setColorSaturationMax(int colorSaturationMax)
    {
        m_colorSaturationMax = colorSaturationMax;
    }

    int colorSaturationMin() const
    {
        return m_colorSaturationMin;
    }
    void setColorSaturationMin(int colorSaturationMin)
    {
        m_colorSaturationMin = colorSaturationMin;
    }

    int contrastMax() const
    {
        return m_contrastMax;
    }
    void setContrastMax(int contrastMax)
    {
        m_contrastMax = contrastMax;
    }

    int contrastMin() const
    {
        return m_contrastMin;
    }
    void setContrastMin(int contrastMin)
    {
        m_contrastMin = contrastMin;
    }

    int sharpnessMax() const
    {
        return m_sharpnessMax;
    }
    void setSharpnessMax(int sharpnessMax)
    {
        m_sharpnessMax = sharpnessMax;
    }

    int sharpnessMin() const
    {
        return m_sharpnessMin;
    }
    void setSharpnessMin(int sharpnessMin)
    {
        m_sharpnessMin = sharpnessMin;
    }

    int defaultSpeedMax() const
    {
        return m_defaultSpeedMax;
    }
    void setDefaultSpeedMax(int defaultSpeedMax)
    {
        m_defaultSpeedMax = defaultSpeedMax;
    }

    int defaultSpeedMin() const
    {
        return m_defaultSpeedMin;
    }
    void setDefaultSpeedMin(int defaultSpeedMin)
    {
        m_defaultSpeedMin = defaultSpeedMin;
    }

    int exposureIrisMax() const
    {
        return m_exposureIrisMax;
    }
    void setExposureIrisMax(int exposureIrisMax)
    {
        m_exposureIrisMax = exposureIrisMax;
    }

    int exposureIrisMin() const
    {
        return m_exposureIrisMin;
    }
    void setExposureIrisMin(int exposureIrisMin)
    {
        m_exposureIrisMin = exposureIrisMin;
    }

private:
    int m_brightnessMax;
    int m_brightnessMin;
    int m_colorSaturationMax;
    int m_colorSaturationMin;
    int m_contrastMax;
    int m_contrastMin;
    int m_sharpnessMax;
    int m_sharpnessMin;
    int m_defaultSpeedMax;
    int m_defaultSpeedMin;
    int m_exposureIrisMax;
    int m_exposureIrisMin;
};
}
#endif // IMAGESETTINGOPTIONS_H
