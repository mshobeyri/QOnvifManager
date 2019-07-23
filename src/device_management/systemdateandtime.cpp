#include "systemdateandtime.h"
#include "message.h"
#include <QString>
using namespace ONVIF;

SystemDateAndTime::SystemDateAndTime(QObject* parent) : QObject(parent) {}

void
SystemDateAndTime::setUtcTime(
    int year, int month, int day, int hour, int minute, int second) {
    QDate date;
    date.setDate(year, month, day);
    QTime time;
    time.setHMS(hour, minute, second);
    this->m_utcTime = QDateTime(date, time, Qt::UTC);
}

void
SystemDateAndTime::setLocalTime(
    int year, int month, int day, int hour, int minute, int second) {
    QDate date;
    date.setDate(year, month, day);
    QTime time;
    time.setHMS(hour, minute, second);
    this->m_localTime = QDateTime(date, time);
}

QDomElement
SystemDateAndTime::toxml() {
    QDomElement setSystemDateAndTime, dateTimeType, daylightSavings, timeZone,
        tz, dateTime, time, hour, minute, second, date, year, month, day;
    setSystemDateAndTime = newElement("wsdl:SetSystemDateAndTime");
    dateTimeType         = newElement("wsdl:DateTimeType", "Manual");
    daylightSavings      = newElement(
        "wsdl:DaylightSavings",
        this->daylightSavings() == true ? "true" : "false");
    timeZone = newElement("wsdl:TimeZone");
    tz       = newElement("sch:TZ", this->tz());
    time     = newElement("sch:Time");
    date     = newElement("sch:Date");
    dateTime = newElement("wsdl:UTCDateTime");
    hour =
        newElement("sch:Hour", QString::number(this->utcTime().time().hour()));
    minute = newElement(
        "sch:Minute", QString::number(this->utcTime().time().minute()));
    second = newElement(
        "sch:Second", QString::number(this->utcTime().time().second()));
    year =
        newElement("sch:Year", QString::number(this->utcTime().date().year()));
    month = newElement(
        "sch:Month", QString::number(this->utcTime().date().month()));
    day = newElement("sch:Day", QString::number(this->utcTime().date().day()));
    setSystemDateAndTime.appendChild(dateTimeType);
    setSystemDateAndTime.appendChild(daylightSavings);
    setSystemDateAndTime.appendChild(timeZone);
    setSystemDateAndTime.appendChild(dateTime);
    timeZone.appendChild(tz);
    dateTime.appendChild(time);
    dateTime.appendChild(date);
    time.appendChild(hour);
    time.appendChild(minute);
    time.appendChild(second);
    date.appendChild(year);
    date.appendChild(month);
    date.appendChild(day);
    return setSystemDateAndTime;
}
