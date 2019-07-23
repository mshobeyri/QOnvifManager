#include "imagesetting.h"
#include "message.h"
using namespace ONVIF;

ImageSetting::ImageSetting(QObject* parent) : QObject(parent) {}

QDomElement
ImageSetting::toxml() {
    QDomElement setImagingSetting, videoSourceToken, imagingSetting, brightness,
        colorSaturation, contrast, exposure, exposureMode, exposureIris, focus,
        autofocusManual, defaultSpeed, sharpness, forcePersistence;
    setImagingSetting = newElement("SetImagingSettings");
    setImagingSetting.setAttribute(
        "xmlns", "http://www.onvif.org/ver20/imaging/wsdl");
    videoSourceToken = newElement("VideoSourceToken", this->token());

    imagingSetting = newElement("ImagingSettings");

    brightness = newElement("Brightness", QString::number(this->brightness()));
    brightness.setAttribute("xmlns", "http://www.onvif.org/ver10/schema");

    contrast = newElement("Contrast", QString::number(this->contrast()));
    contrast.setAttribute("xmlns", "http://www.onvif.org/ver10/schema");

    sharpness = newElement("Sharpness", QString::number(this->sharpness()));
    sharpness.setAttribute("xmlns", "http://www.onvif.org/ver10/schema");

    colorSaturation =
        newElement("ColorSaturation", QString::number(this->colorSaturation()));
    colorSaturation.setAttribute("xmlns", "http://www.onvif.org/ver10/schema");

    exposure = newElement("ColorSaturation");
    exposure.setAttribute("xmlns", "http://www.onvif.org/ver10/schema");
    exposureMode =
        newElement("Mode", this->exposureManual() ? "MANUAL" : "AUTO");
    exposureIris = newElement("Iris", QString::number(this->exposureIris()));


    focus = newElement("Focus");
    focus.setAttribute("xmlns", "http://www.onvif.org/ver10/schema");
    autofocusManual =
        newElement("AutoFocusMode", this->exposureManual() ? "MANUAL" : "AUTO");
    defaultSpeed =
        newElement("DefaultSpeed", QString::number(this->defaultSpeed()));

    forcePersistence = newElement(
        "ForcePersistence", this->forcePersistence() ? "true" : "false");

    exposure.appendChild(exposureMode);
    exposure.appendChild(exposureIris);

    focus.appendChild(autofocusManual);
    focus.appendChild(defaultSpeed);

    imagingSetting.appendChild(brightness);
    imagingSetting.appendChild(contrast);
    imagingSetting.appendChild(sharpness);
    imagingSetting.appendChild(colorSaturation);
    imagingSetting.appendChild(exposure);
    imagingSetting.appendChild(focus);

    setImagingSetting.appendChild(videoSourceToken);
    setImagingSetting.appendChild(imagingSetting);
    setImagingSetting.appendChild(forcePersistence);

    return setImagingSetting;
}
