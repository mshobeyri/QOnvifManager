#include "videoencoderconfigurationoptions.h"

using namespace ONVIF;
VideoEncoderConfigurationOptions::VideoEncoderConfigurationOptions(
    QObject* parent)
    : QObject(parent) {}

VideoEncoderConfigurationOptions::~VideoEncoderConfigurationOptions() {}

int
VideoEncoderConfigurationOptions::qualityRangeMin() const {
    return m_qualityRangeMin;
}

void
VideoEncoderConfigurationOptions::setQualityRangeMin(int qualityRangeMin) {
    m_qualityRangeMin = qualityRangeMin;
}

int
VideoEncoderConfigurationOptions::qulityRangeMax() const {
    return m_qualityRangeMax;
}

void
VideoEncoderConfigurationOptions::setQulityRangeMax(int qulityRangeMax) {
    m_qualityRangeMax = qulityRangeMax;
}

int
VideoEncoderConfigurationOptions::govLengthRangeMin() const {
    return m_govLengthRangeMin;
}

void
VideoEncoderConfigurationOptions::setGovLengthRangeMin(int govLengthRangeMin) {
    m_govLengthRangeMin = govLengthRangeMin;
}

int
VideoEncoderConfigurationOptions::govLengthRangeMax() const {
    return m_govLengthRangeMax;
}

void
VideoEncoderConfigurationOptions::setGovLengthRangeMax(int govLengthRangeMax) {
    m_govLengthRangeMax = govLengthRangeMax;
}

int
VideoEncoderConfigurationOptions::bitRateRangeMin() const {
    return m_bitRateRangeMin;
}

void
VideoEncoderConfigurationOptions::setBitRateRangeMin(int bitRateRangeMin) {
    m_bitRateRangeMin = bitRateRangeMin;
}

int
VideoEncoderConfigurationOptions::bitRateRangeMax() const {
    return m_bitRateRangeMax;
}

void
VideoEncoderConfigurationOptions::setBitRateRangeMax(int bitRateRangeMax) {
    m_bitRateRangeMax = bitRateRangeMax;
}

int
VideoEncoderConfigurationOptions::frameRateRangeMinJpeg() const {
    return m_frameRateRangeMinJpeg;
}

void
VideoEncoderConfigurationOptions::setFrameRateRangeMinJpeg(
    int frameRateRangeMinJpeg) {
    m_frameRateRangeMinJpeg = frameRateRangeMinJpeg;
}

int
VideoEncoderConfigurationOptions::frameRateRangeMaxJpeg() const {
    return m_frameRateRangeMaxJpeg;
}

void
VideoEncoderConfigurationOptions::setFrameRateRangeMaxJpeg(
    int frameRateRangeMaxJpeg) {
    m_frameRateRangeMaxJpeg = frameRateRangeMaxJpeg;
}

int
VideoEncoderConfigurationOptions::frameRateRangeMaxH264() const {
    return m_frameRateRangeMaxH264;
}

void
VideoEncoderConfigurationOptions::setFrameRateRangeMaxH264(
    int frameRateRangeMax) {
    m_frameRateRangeMaxH264 = frameRateRangeMax;
}

int
VideoEncoderConfigurationOptions::frameRateRangeMinH264() const {
    return m_frameRateRangeMinH264;
}
void
VideoEncoderConfigurationOptions::setFrameRateRangeMinH264(
    int frameRateRangeMin) {
    m_frameRateRangeMinH264 = frameRateRangeMin;
}


int
VideoEncoderConfigurationOptions::encodingIntervalRangeMinJpeg() const {
    return m_encodingIntervalRangeMinJpeg;
}

void
VideoEncoderConfigurationOptions::setEncodingIntervalRangeMinJpeg(
    int encodingIntervalRangeMinJpeg) {
    m_encodingIntervalRangeMinJpeg = encodingIntervalRangeMinJpeg;
}

int
VideoEncoderConfigurationOptions::encodingIntervalRangeMaxJpeg() const {
    return m_encodingIntervalRangeMaxJpeg;
}

void
VideoEncoderConfigurationOptions::setEncodingIntervalRangeMaxJpeg(
    int encodingIntervalRangeMaxJpeg) {
    m_encodingIntervalRangeMaxJpeg = encodingIntervalRangeMaxJpeg;
}


void
VideoEncoderConfigurationOptions::setEncodingIntervalRangeMinH264(
    int encodingIntervalRangeMinH264) {
    m_encodingIntervalRangeMinH264 = encodingIntervalRangeMinH264;
}

int
VideoEncoderConfigurationOptions::encodingIntervalRangeMinH264() const {
    return m_encodingIntervalRangeMinH264;
}

int
VideoEncoderConfigurationOptions::encodingIntervalRangeMaxH264() const {
    return m_encodingIntervalRangeMaxH264;
}

void
VideoEncoderConfigurationOptions::setEncodingIntervalRangeMaxH264(
    int encodingIntervalRangeMax) {
    m_encodingIntervalRangeMaxH264 = encodingIntervalRangeMax;
}

QList<int>
VideoEncoderConfigurationOptions::resAvailableWidthJpeg() const {
    return m_resAvailableWidthJpeg;
}
void
VideoEncoderConfigurationOptions::setResAvailableWidthJpeg(
    int resAvailableWidth) {
    m_resAvailableWidthJpeg.push_back(resAvailableWidth);
}

QList<int>
VideoEncoderConfigurationOptions::resAvailableHeightJpeg() const {
    return m_resAvailableHeightJpeg;
}
void
VideoEncoderConfigurationOptions::setResAvailableHeightJpeg(
    int resAvailableHeight) {
    m_resAvailableHeightJpeg.push_back(resAvailableHeight);
}

QList<int>
VideoEncoderConfigurationOptions::resAvailableWidthH264() const {
    return m_resAvailableWidthH264;
}

void
VideoEncoderConfigurationOptions::setResAvailableWidthH264(
    int resAvailableWidth) {
    m_resAvailableWidthH264.push_back(resAvailableWidth);
}

QList<int>
VideoEncoderConfigurationOptions::resAvailableHeightH264() const {
    return m_resAvailableHeightH264;
}
void
VideoEncoderConfigurationOptions::setResAvailableHeightH264(
    int resAvailableHeight) {
    m_resAvailableHeightH264.push_back(resAvailableHeight);
}

void
VideoEncoderConfigurationOptions::setH264ProfilesSupported(
    VideoEncoderConfigurationOptions::H264ProfilesSupported
        h264ProfilesSupported) {
    m_h264ProfilesSupported.push_back(h264ProfilesSupported);
}

QList<VideoEncoderConfigurationOptions::H264ProfilesSupported>
VideoEncoderConfigurationOptions::getH264ProfilesSupported() const {
    return m_h264ProfilesSupported;
}
