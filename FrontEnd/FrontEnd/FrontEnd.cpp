#include "FrontEnd.h"
#include <iostream>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>

FrontEnd::FrontEnd(QWidget *parent)
    : QMainWindow(parent), networkManager(new QNetworkAccessManager(this))
{
    ui.setupUi(this);
    registerWindow = new Register();
    gameWindow = new Game();
    connect(registerWindow, &Register::loginWindow, this, &FrontEnd::show);
    // connect(registerWindow, &Register::registrationCompleted, this, &FrontEnd::show);
    connect(this, &FrontEnd::loginSuccessful, gameWindow, &Game::show);
    connect(networkManager, &QNetworkAccessManager::finished, this, &FrontEnd::onLoginResponse);
    

}

FrontEnd::~FrontEnd()
{
    delete networkManager;
    delete registerWindow;
    delete gameWindow;
}

void FrontEnd::on_pushButton_registerNow_clicked()
{
    registerWindow->show();
    this->close();
}

void FrontEnd::onLoginResponse(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        // Login successful
        emit loginSuccessful();
        gameWindow->show();
        this->close();
    }
    else {
        // Login failed
        QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
    }
    reply->deleteLater();
}

void FrontEnd::on_pushButton_login_clicked()
{
    QString username, password;
    username = ui.lineEdit_username->text();
    password = ui.lineEdit_password->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Error", "Please enter both username and password.");
        return;
    }

    QJsonObject loginData;
    loginData["username"] = username;
    loginData["password"] = password;

    QNetworkRequest request(QUrl("http://localhost:18080/login"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    networkManager->post(request, QJsonDocument(loginData).toJson());

    
}