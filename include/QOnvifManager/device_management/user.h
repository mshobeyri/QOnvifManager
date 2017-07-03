#ifndef USER_H
#define USER_H
#include <QDomElement>
#include <QObject>
namespace ONVIF {
class Users : public QObject
{
    Q_OBJECT

public:
    explicit Users(QObject* parent = NULL);
    virtual ~Users();

    QDomElement toxml(QString mainTag);

    QStringList userNames() const {
        return m_userNames;
    }

    QStringList passWord() const {
        return m_passWords;
    }

    QStringList userLevel() const {
        return m_userLevel;
    }

    bool result() const
    {
        return m_result;
    }
    void setResult(bool result)
    {
        m_result = result;
    }

public slots:
    void setUserNames(QString arg) {
        m_userNames.push_back(arg);
    }

    void setPassWords(QString arg) {
        m_passWords.push_back(arg);
    }

    void setUserLevel(QString arg) {
        m_userLevel.push_back(arg);
    }

private:
    QStringList m_userNames;
    QStringList m_passWords;
    //Administrator, Operator, User, Anonymous, Extended
    QStringList m_userLevel;
    bool m_result;
};
}
#endif // USER_H
