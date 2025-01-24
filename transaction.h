#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>

class Transaction {
public:
    enum Type { BUY, SELL, TRANSFER, CONVERT };

    Transaction(Type type, const QString &from, const QString &to, double amount);
    bool validate(); // اعتبارسنجی با سرور

private:
    Type type;
    QString fromAddress;
    QString toAddress;
    double amount;
    QString timestamp;
};

#endif // TRANSACTION_H
