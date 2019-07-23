#ifndef PRESETS_H
#define PRESETS_H
#include <QList>
#include <QObject>
namespace ONVIF {
class Presets : public QObject
{
    Q_OBJECT
public:
    explicit Presets(QObject* parent = NULL);
    virtual ~Presets();
    QList<QString> getToken() const {
        return m_token;
    }

    void setToken(QString token) {
        m_token.push_back(token);
    }

    QList<QString> getName() const {
        return m_name;
    }

    void setName(QString name) {
        m_name.push_back(name);
    }

    QString getProfileToken() const {
        return m_profileToken;
    }

    void setProfileToken(const QString& profileToken) {
        m_profileToken = profileToken;
    }

private:
    QString        m_profileToken;
    QList<QString> m_token;
    QList<QString> m_name;
};
}
#endif // PRESETS_H
