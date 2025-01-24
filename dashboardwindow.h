#ifndef DASHBOARDWINDOW_H
#define DASHBOARDWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "User.h"
#include "APIManager.h"

class DashboardWindow : public QMainWindow {
    Q_OBJECT
public:
    DashboardWindow(User *user, QWidget *parent = nullptr);

private slots:
    void updatePrices(const QJsonDocument &data);

private:
    User *user;
    APIManager *apiManager;
    QLabel *priceLabel;
};

#endif // DASHBOARDWINDOW_H
