#include "Register.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>

Register::Register(QWidget* parent)
	: QMainWindow(parent), networkManager(new QNetworkAccessManager(this))
{
	ui.setupUi(this);
	connect(networkManager, &QNetworkAccessManager::finished, this, &Register::onRegistrationReply);
}

Register::~Register()
{
	delete networkManager;
}


void Register::on_pushButton_Login_now_clicked()
{
	this->close();
	emit loginWindow();
}

void Register::on_pushButton_Register_clicked()
{
    QJsonObject userData;
    userData["fullname"] = ui.lineEdit_FullName->text();
    userData["username"] = ui.lineEdit_username->text();
    userData["password"] = ui.lineEdit_password->text(); // Consider hashing the password

    sendRegistrationRequest(userData);
}

void Register::sendRegistrationRequest(const QJsonObject& userData)
{
	QNetworkRequest request(QUrl("http://localhost:18080/register"));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	networkManager->post(request, QJsonDocument(userData).toJson());
}

void Register::onRegistrationReply(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        // Parse the response
        auto response = QJsonDocument::fromJson(reply->readAll()).object();
        QString message = response["message"].toString();

        // Handle successful response
        QMessageBox::information(this, "Registration", message);
        this->close();
        emit loginWindow();
    }
    else {
        // Parse the error response
        auto errorResponse = QJsonDocument::fromJson(reply->readAll()).object();
        QString errorMessage = errorResponse["error"].toString();

        // Handle error
        QMessageBox::warning(this, "Registration Failed", errorMessage);
    }
    reply->deleteLater();
}


