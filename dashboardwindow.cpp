#include "DashboardWindow.h"
#include <QVBoxLayout>
#include <QJsonArray>
#include <QJsonObject>

DashboardWindow::DashboardWindow(User *user, QWidget *parent)
    : QMainWindow(parent), user(user) {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    priceLabel = new QLabel("در حال دریافت قیمت‌ها...", this);
    layout->addWidget(priceLabel);

    setCentralWidget(centralWidget);
    setWindowTitle("داشبورد - " + user->getEmail());
    resize(400, 300);

    apiManager = new APIManager(this);
    connect(apiManager, &APIManager::pricesUpdated, this, &DashboardWindow::updatePrices);
}

void DashboardWindow::updatePrices(const QJsonDocument &doc) {
    QString pricesText;
    QJsonArray prices = doc.array();

    for (const QJsonValue &value : prices) {
        QJsonObject obj = value.toObject();
        pricesText += QString("%1: $%2\n")
                          .arg(obj["symbol"].toString().toUpper())
                          .arg(obj["current_price"].toDouble());
    }

    priceLabel->setText(pricesText);
}
