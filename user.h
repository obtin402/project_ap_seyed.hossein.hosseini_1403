#ifndef USER_H
#define USER_H

#include <QString>
#include <QVector>
#include "Wallet.h"

class User {
public:
    enum Level { UNVERIFIED, LEVEL1, LEVEL2 };

    User(const QString &email, const QString &password);

    // احراز هویت و مدیریت سطح
    bool verifyCaptcha(const QString &captchaInput);
    bool verifyEmail(const QString &code);
    void promoteToLevel1();
    void promoteToLevel2();

    // مدیریت کیف پول
    bool createWallet(const QString &currency);
    QVector<Wallet> getWallets() const;

    // getters
    QString getEmail() const;
    Level getLevel() const;
    QString getInviteCode() const;

private:
    QString email;
    QString hashedPassword;
    QString inviteCode;
    Level level = UNVERIFIED;
    QVector<Wallet> wallets;
};

#endif // USER_H
