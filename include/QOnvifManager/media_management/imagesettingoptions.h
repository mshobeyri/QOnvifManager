#ifndef IMAGESETTINGOPTIONS_H
#define IMAGESETTINGOPTIONS_H
#include <QObject>

namespace ONVIF {
class ImageSettingOptions : public QObject
{
public:
    ImageSettingOptions(QObject* parent = NULL);

    double brightnessMax() const {
        return m_brightnessMax;
    }
    void setBrightnessMax(double brightnessMax) {
        m_brightnessMax = brightnessMax;
    }

    double brightnessMin() const {
        return m_brightnessMin;
    }
    void setBrightnessMin(double brightnessMin) {
        m_brightnessMin = brightnessMin;
    }

    double colorSaturationMax() const {
        return m_colorSaturationMax;
    }
    void setColorSaturationMax(double colorSaturationMax) {
        m_colorSaturationMax = colorSaturationMax;
    }

    double colorSaturationMin() const {
        return m_colorSaturationMin;
    }
    void setColorSaturationMin(double colorSaturationMin) {
        m_colorSaturationMin = colorSaturationMin;
    }

    double contrastMax() const {
        return m_contrastMax;
    }
    void setContrastMax(double contrastMax) {
        m_contrastMax = contrastMax;
    }

    double contrastMin() const {
        return m_contrastMin;
    }
    void setContrastMin(double contrastMin) {
        m_contrastMin = contrastMin;
    }

    double sharpnessMax() const {
        return m_sharpnessMax;
    }
    void setSharpnessMax(double sharpnessMax) {
        m_sharpnessMax = sharpnessMax;
    }

    double sharpnessMin() const {
        return m_sharpnessMin;
    }
    void setSharpnessMin(double sharpnessMin) {
        m_sharpnessMin = sharpnessMin;
    }

    double defaultSpeedMax() const {
        return m_defaultSpeedMax;
    }
    void setDefaultSpeedMax(double defaultSpeedMax) {
        m_defaultSpeedMax = defaultSpeedMax;
    }

    double defaultSpeedMin() const {
        return m_defaultSpeedMin;
    }
    void setDefaultSpeedMin(double defaultSpeedMin) {
        m_defaultSpeedMin = defaultSpeedMin;
    }

    double exposureIrisMax() const {
        return m_exposureIrisMax;
    }
    void setExposureIrisMax(double exposureIrisMax) {
        m_exposureIrisMax = exposureIrisMax;
    }

    double exposureIrisMin() const {
        return m_exposureIrisMin;
    }
    void setExposureIrisMin(double exposureIrisMin) {
        m_exposureIrisMin = exposureIrisMin;
    }

private:
    double m_brightnessMax;
    double m_brightnessMin;
    double m_colorSaturationMax;
    double m_colorSaturationMin;
    double m_contrastMax;
    double m_contrastMin;
    double m_sharpnessMax;
    double m_sharpnessMin;
    double m_defaultSpeedMax;
    double m_defaultSpeedMin;
    double m_exposureIrisMax;
    double m_exposureIrisMin;
};
}
#endif // IMAGESETTINGOPTIONS_H
