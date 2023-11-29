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
    FrontEnd(QWidget *parent = nullptr);
    ~FrontEnd();

private slots:
    virtual void on_pushButton_login_clicked();
    virtual void on_pushButton_registerNow_clicked();
    void onLoginResponse(QNetworkReply* reply);

signals:
    void loginSuccessful();

private:
    Ui::FrontEndClass ui;
    Register* registerWindow = nullptr;
    Game* gameWindow = nullptr; 
    QNetworkAccessManager* networkManager;
};
