#include "Wallet.h"
#include <QUuid>
#include <QCryptographicHash>
#include <QDebug>

// سازنده پیشفرض
Wallet::Wallet() : currency("BTC"), balance(0.0) {
    address = generateAddress();
    recoveryPhrase = generateRecoveryPhrase();
}

// سازنده با پارامتر (ارز و موجودی اولیه)
Wallet::Wallet(const QString &currency, double balance)
    : currency(currency), balance(balance) {
    address = generateAddress();
    recoveryPhrase = generateRecoveryPhrase();
}

// --------------- متدهای خصوصی برای تولید آدرس و عبارت بازیابی ---------------


QString Wallet::generateAddress() {
    // تولید آدرس منحصر به فرد با استفاده از UUID و هش SHA-256
    QString uuid = QUuid::createUuid().toString();
    QByteArray hash = QCryptographicHash::hash(uuid.toUtf8(), QCryptographicHash::Sha256);
    return "WALLET-" + QString(hash.toHex()).left(20).toUpper();
}

QString Wallet::generateRecoveryPhrase() {
    // تولید 6 کلمه تصادفی (مثال ساده)
    QStringList words = {
        "apple", "banana", "cherry", "date", "elderberry",
        "fig", "grape", "honeydew", "kiwi", "lemon"
    };
    QString phrase;
    for (int i = 0; i < 6; ++i) {
        phrase += words.at(QRandomGenerator::global()->bounded(words.size())) + " ";
    }
    return phrase.trimmed();
}

// --------------- متدهای انتقال و تبدیل ارز ---------------
bool Wallet::transfer(const QString &toAddress, double amount) {
    if (amount <= 0) {
        qWarning() << "مقدار انتقال باید مثبت باشد!";
        return false;
    }

    if (balance < amount) {
        qWarning() << "موجودی کافی نیست!";
        return false;
    }

    if (toAddress.isEmpty() || toAddress == address) {
        qWarning() << "آدرس مقصد نامعتبر است!";
        return false;
    }

    balance -= amount;
    qInfo() << "انتقال موفق:" << amount << currency << "به آدرس" << toAddress;
    return true;
}



bool Wallet::convert(const QString &targetCurrency, double amount, double exchangeRate) {
    if (amount <= 0) {
        qWarning() << "مقدار تبدیل باید مثبت باشد!";
        return false;
    }

    if (balance < amount) {
        qWarning() << "موجودی کافی نیست!";
        return false;
    }

    if (targetCurrency.isEmpty() || targetCurrency == currency) {
        qWarning() << "ارز مقصد نامعتبر است!";
        return false;
    }

    // تبدیل ارز (کسر از موجودی فعلی و افزودن به ارز مقصد)
    balance -= amount;
    double convertedAmount = amount * exchangeRate;

    qInfo() << "تبدیل موفق:" << amount << currency << "به" << convertedAmount << targetCurrency;
    return true;
}

// --------------- متدهای دسترسی (Getters) ---------------
QString Wallet::getAddress() const {
    return address;
}

QString Wallet::getRecoveryPhrase() const {
    return recoveryPhrase;
}

QString Wallet::getCurrency() const {
    return currency;
}


double Wallet::getBalance() const {
    return balance;
}

// --------------- متد تنظیم موجودی (برای تست) ---------------


void Wallet::setBalance(double newBalance) {
    balance = newBalance;
}




