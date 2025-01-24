#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include "User.h"
#include <QObject>

class AuthManager : public QObject {
    Q_OBJECT
public:
    AuthManager(QObject *parent = nullptr);

    bool registerUser(const QString &email, const QString &password);
    bool login(const QString &email, const QString &password);
    bool verifyCaptcha(const QString &userInput);
    void sendVerificationCode(const QString &email);
    bool verifyCode(const QString &code);

signals:
    void userVerified(User *user);

private:
    QVector<User> users;
};

#endif // AUTHMANAGER_H
