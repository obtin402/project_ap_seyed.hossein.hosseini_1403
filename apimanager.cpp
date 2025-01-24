#include "APIManager.h"
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QUrlQuery>

APIManager::APIManager(QObject *parent) : QObject(parent) {}

void APIManager::fetchPrices(const QStringList &cryptoIds) {
    QUrl url("https://api.coingecko.com/api/v3/coins/markets");
    QUrlQuery query;
    query.addQueryItem("vs_currency", "usd");
    query.addQueryItem("ids", cryptoIds.join(","));
    url.setQuery(query);

    QNetworkReply *reply = manager.get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, [this, reply]() { onPricesReply(reply); });
}

void APIManager::fetchHistoricalData(const QString &cryptoId, int days) {
    QUrl url(QString("https://api.coingecko.com/api/v3/coins/%1/market_chart").arg(cryptoId));
    QUrlQuery query;
    query.addQueryItem("vs_currency", "usd");
    query.addQueryItem("days", QString::number(days));
    url.setQuery(query);

    QNetworkReply *reply = manager.get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, [this, reply]() { onHistoricalDataReply(reply); });
}

void APIManager::onPricesReply(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        emit pricesUpdated(doc);
    }
    reply->deleteLater();
}

void APIManager::onHistoricalDataReply(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        emit historicalDataUpdated(doc);
    }
    reply->deleteLater();
}
