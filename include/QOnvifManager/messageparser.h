#ifndef ONVIF_MESSAGEPARSER_H
#define ONVIF_MESSAGEPARSER_H

#include <QObject>
#include <QXmlQuery>
#include <QBuffer>
#include <QXmlResultItems>

namespace ONVIF {
    class MessageParser : public QObject
    {
        Q_OBJECT
    public:
        explicit MessageParser(const QString &data, QHash<QString, QString> &namespaces, QObject *parent = 0);
        ~MessageParser();
        QString getValue(const QString &xpath);
        QString getBetween(const QString &start,const QString &end);
        bool find(const QString &xpath);
        QXmlQuery *query();
        QString nameSpace();

        std::string mData;
    private:
        QXmlQuery mQuery;
        QString mNamespaceQueryStr;
        QBuffer mBuffer;
    };
}

#endif // ONVIF_MESSAGEPARSER_H
