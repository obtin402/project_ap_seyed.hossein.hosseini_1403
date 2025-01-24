#include "User.h"
#include <QCryptographicHash>

User::User(const QString &email, const QString &password)
    : email(email) {
    hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
}

bool User::verifyCaptcha(const QString &captchaInput) {
    // پیاده‌سازی CAPTCHA (مثال ساده)
    return captchaInput == "1234";
}

bool User::verifyEmail(const QString &code) {
    // ارسال کد به ایمیل و تایید (مثال ساده)
    return code == "0000";
}

void User::promoteToLevel1() {
    if (level == UNVERIFIED) {
        level = LEVEL1;
        inviteCode = "INV-" + QString::number(qrand() % 10000);
    }
}

void User::promoteToLevel2() {
    if (level == LEVEL1) {
        level = LEVEL2;
    }
}

bool User::createWallet(const QString &currency) {
    if (level == UNVERIFIED && wallets.size() >= 1) {
        return false; // کاربر تأییدنشده فقط یک کیف پول می‌سازد
    }
    wallets.append(Wallet(currency));
    return true;
}

QVector<Wallet> User::getWallets() const {
    return wallets;
}

QString User::getEmail() const { return email; }
User::Level User::getLevel() const { return level; }
QString User::getInviteCode() const { return inviteCode; }
