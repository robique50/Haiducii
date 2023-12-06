#include "FrontEnd.h"
#include <iostream>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>

FrontEnd::FrontEnd(QWidget *parent,int userID)
    : QMainWindow(parent), networkManager(new QNetworkAccessManager(this)), userID(userID)
{
    ui.setupUi(this);
    registerWindow = new Register();
    //gameWindow = new Game(this, userID);
    connect(registerWindow, &Register::loginWindow, this, &FrontEnd::show);
    // connect(registerWindow, &Register::registrationCompleted, this, &FrontEnd::show);
   // connect(this, &FrontEnd::loginSuccessful, gameWindow, &Game::show);
    connect(this, &FrontEnd::loginSuccessful, this, &FrontEnd::onLoginSuccessful);
    connect(networkManager, &QNetworkAccessManager::finished, this, &FrontEnd::onLoginResponse);
    connect(this, &FrontEnd::loginFailed, this, &FrontEnd::onLoginFailed);
    

}

FrontEnd::~FrontEnd()
{
    delete networkManager;
    delete registerWindow;
    // Only delete gameWindow if it's not nullptr
    if (gameWindow) {
        delete gameWindow;
    }
}

void FrontEnd::on_pushButton_registerNow_clicked()
{
    registerWindow->show();
    this->close();
}

void FrontEnd::onLoginResponse(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject obj = doc.object();
        int userID = obj["userID"].toInt();

        if (userID > 0) {
            emit loginSuccessful(userID);
        }
        else {
            emit loginFailed("Invalid server response: User ID is 0 or negative.");
        }
    }
    else {
        emit loginFailed("Network error: " + reply->errorString());
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

void FrontEnd::onLoginSuccessful(int userID) {
    QMessageBox::information(this, "Login Success", "User ID: " + QString::number(userID));
    if (!gameWindow) {
        gameWindow = new Game(this, userID);
    }
    gameWindow->show();
    this->hide();
}

void FrontEnd::onLoginFailed(const QString& reason)
{
    QMessageBox::warning(this, "Login Failed", reason);
}
