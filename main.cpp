#include <QApplication>
#include "LoginWindow.h"
#include "DashboardWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    LoginWindow loginWindow;
    QObject::connect(&loginWindow, &LoginWindow::loginSuccess, [&](User *user) {
        loginWindow.hide();
        DashboardWindow *dashboard = new DashboardWindow(user);
        dashboard->show();
    });

    loginWindow.show();
    return app.exec();
}
