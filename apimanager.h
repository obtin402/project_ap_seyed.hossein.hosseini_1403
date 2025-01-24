#ifndef APIMANAGER_H
#define APIMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonDocument>

class APIManager : public QObject {
    Q_OBJECT
public:
    explicit APIManager(QObject *parent = nullptr);

    void fetchPrices(const QStringList &cryptoIds = {"bitcoin", "ethereum"});
    void fetchHistoricalData(const QString &cryptoId, int days = 7);

signals:
    void pricesUpdated(const QJsonDocument &data);
    void historicalDataUpdated(const QJsonDocument &data);

private slots:
    void onPricesReply(QNetworkReply *reply);
    void onHistoricalDataReply(QNetworkReply *reply);

private:
    QNetworkAccessManager manager;
};

#endif // APIMANAGER_H
