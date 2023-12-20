#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FrontEnd.h"
#include "Register.h"
#include "Game.h"
#include <qmessagebox.h>

class FrontEnd : public QMainWindow
{
    Q_OBJECT

public:
    FrontEnd(QWidget* parent = nullptr, int userID = 0);
    ~FrontEnd();

private slots:
    virtual void on_pushButton_login_clicked();
    virtual void on_pushButton_registerNow_clicked();
    void onLoginResponse(QNetworkReply* reply);
    void onLoginSuccessful(int userID, const QString& username);
    void onLoginFailed(const QString& reason);



signals:
    void loginSuccessful(int userID, const QString& username);
    void loginFailed(const QString& reason);

private:
    Ui::FrontEndClass ui;
    Register* registerWindow = nullptr;
    Game* gameWindow = nullptr;
    QNetworkAccessManager* networkManager;
    int userID;

};
