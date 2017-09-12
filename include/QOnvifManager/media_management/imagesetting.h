#ifndef IMAGESETTING_H
#define IMAGESETTING_H
#include <QDomElement>
#include <QObject>

namespace ONVIF {
class ImageSetting : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int brightness READ brightness WRITE setBrightness)
    Q_PROPERTY(
        int colorSaturation READ colorSaturation WRITE setColorSaturation)
    Q_PROPERTY(int contrast READ contrast WRITE setContrast)
public:
    ImageSetting(QObject* parent = NULL);
    QDomElement toxml();

    int brightness() const {
        return m_brightness;
    }
    void setBrightness(int brightness) {
        m_brightness = brightness;
    }

    int colorSaturation() const {
        return m_colorSaturation;
    }
    void setColorSaturation(int colorSaturation) {
        m_colorSaturation = colorSaturation;
    }

    int contrast() const {
        return m_contrast;
    }
    void setContrast(int contrast) {
        m_contrast = contrast;
    }

    int sharpness() const {
        return m_sharpness;
    }
    void setSharpness(int sharpness) {
        m_sharpness = sharpness;
    }

    bool autofocusManual() const {
        return m_autofocusManual;
    }
    void setAutofocusManual(bool autofocusManual) {
        m_autofocusManual = autofocusManual;
    }

    int defaultSpeed() const {
        return m_defaultSpeed;
    }
    void setDefaultSpeed(int defaultSpeed) {
        m_defaultSpeed = defaultSpeed;
    }

    bool exposureManual() const {
        return m_exposureManual;
    }
    void setExposureManual(bool exposureManual) {
        m_exposureManual = exposureManual;
    }

    int exposureIris() const {
        return m_exposureIris;
    }
    void setExposureIris(int exposureIris) {
        m_exposureIris = exposureIris;
    }

    bool result() const {
        return m_result;
    }
    void setResult(bool result) {
        m_result = result;
    }

    bool forcePersistence() const {
        return m_forcePersistence;
    }
    void setForcePersistence(bool forcePersistence) {
        m_forcePersistence = forcePersistence;
    }

    QString token() const {
        return m_token;
    }
    void setToken(const QString& token) {
        m_token = token;
    }

private:
    int     m_brightness;
    int     m_colorSaturation;
    int     m_contrast;
    int     m_sharpness;
    bool    m_autofocusManual;
    int     m_defaultSpeed;
    bool    m_exposureManual;
    int     m_exposureIris;
    bool    m_forcePersistence;
    QString m_token;
    bool    m_result;
};
}
#endif // IMAGESETTING_H
