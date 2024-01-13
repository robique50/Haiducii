#include "Register.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>
#include <regex>

Register::Register(QWidget* parent)
	: QMainWindow{ parent }, 
	networkManager{ new QNetworkAccessManager(this) }
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
	userData["password"] = ui.lineEdit_password->text();

	if (!validateFullName(userData["fullname"].toString())) {
		QMessageBox::warning(this, "Registration Failed", "Full Name must start with a capital letter and contain only letters and spaces.");
		return;
	}

	if (!validateUsername(userData["username"].toString())) {
		QMessageBox::warning(this, "Registration Failed", "Username must be at least 6 characters long.");
		return;
	}

	if (!validatePassword(userData["password"].toString())) {
		QMessageBox::warning(this, "Registration Failed", "Password must be at least 8 characters long, contain at least one uppercase letter, one lowercase letter, one number and one special character.");
		return;
	}

	sendRegistrationRequest(userData);
}

void Register::sendRegistrationRequest(const QJsonObject& userData)
{
	QNetworkRequest request(QUrl("http://localhost:18080/register"));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	networkManager->post(request, QJsonDocument(userData).toJson());
}

bool Register::validateUsername(const QString& username)
{
	std::regex username_rx("^.{6,}$");
	return std::regex_match(username.toStdString(), username_rx);
}

bool Register::validatePassword(const QString& password)
{
	std::regex password_rx("^(?=.*[A-Z])(?=.*[a-z])(?=.*\\d)(?=.*[@$!%*#?&])[A-Za-z\\d@$!%*#?&]{8,}$");
	return std::regex_match(password.toStdString(), password_rx);
}

bool Register::validateFullName(const QString& fullName)
{
	std::regex fullname_rx("^[A-Z][a-z]+(?: [A-Z][a-z]+)*$");
	return std::regex_match(fullName.toStdString(), fullname_rx);
}

void Register::onRegistrationReply(QNetworkReply* reply)
{
	if (reply->error() == QNetworkReply::NoError) {
		auto response = QJsonDocument::fromJson(reply->readAll()).object();
		QString message = response["message"].toString();

		QMessageBox::information(this, "Registration", message);
		this->close();
		emit loginWindow();
	}
	else {
		auto errorResponse = QJsonDocument::fromJson(reply->readAll()).object();
		QString errorMessage = errorResponse["error"].toString();

		QMessageBox::warning(this, "Registration Failed", errorMessage);
	}
	reply->deleteLater();
}


