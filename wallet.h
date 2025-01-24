#ifndef WALLET_H
#define WALLET_H

#include <QString>

class Wallet {
public:
    Wallet();
    Wallet(const QString &currency, double balance = 0.0);
    QString generateRecoveryPhrase();
    QString getAddress() const;
    QString getRecoveryPhrase() const;
    QString getCurrency() const;
    double getBalance() const;
    QString generateAddress();
    bool convert(const QString &targetCurrency, double amount, double exchangeRate) ;
    void setBalance(double newBalance) ;
    bool transfer(const QString &toAddress, double amount);
    bool convert(const QString &targetCurrency, double amount);

private:
    QString address;
    QString recoveryPhrase; // 6 کلمه‌ای
    QString currency;
    double balance;
};

#endif // WALLET_H
