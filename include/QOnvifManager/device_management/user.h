#ifndef USER_H
#define USER_H
#include <QDomElement>
#include <QObject>
namespace ONVIF {
class Users : public QObject
{
    Q_OBJECT
    Q_ENUMS(UserLevelType)

public:
    explicit Users(QObject* parent = NULL);
    virtual ~Users();
    enum UserLevelType { Administrator, Operator, User, Anonymous, Extended };

    QString toString(UserLevelType _userLevelType);
    QDomElement toxml(QString mainTag);

    QStringList userNames() const {
        return m_userNames;
    }

    QStringList passWord() const {
        return m_passWords;
    }

    QList<UserLevelType> userLevel() const {
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
        int levelInt = 0;
        if (arg == "Administrator")
            levelInt = 0;
        else if (arg == "Operator")
            levelInt = 1;
        else if (arg == "User")
            levelInt = 2;
        else if (arg == "Anonynos")
            levelInt = 3;
        else if (arg == "Extended")
            levelInt = 4;
        m_userLevel.push_back(static_cast<UserLevelType>(levelInt));
    }

private:
    QStringList          m_userNames;
    QStringList          m_passWords;
    QList<UserLevelType> m_userLevel;
    bool m_result;
};
}
#endif // USER_H
