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

    QDomElement toxml();

    QStringList userNames() const {
        return m_userNames;
    }

    QStringList passWord() const {
        return m_passWords;
    }

    QStringList userLevel() const {
        return m_userLevel;
    }

    bool result() const {
        return m_result;
    }
    void setResult(bool result) {
        m_result = result;
    }

    int actionMode() const {
        return m_actionMode;
    }
    void setActionMode(int actionMode) {
        m_actionMode = actionMode;
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
    // Administrator, Operator, User, Anonymous, Extended
    QStringList m_userLevel;
    int         m_actionMode;
    bool        m_result;
};
}
#endif // USER_H
