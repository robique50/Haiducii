#pragma once

#include <QMainWindow>
#include "ui_Register.h"

class QNetworkAccessManager;
class QNetworkReply;

class Register : public QMainWindow
{
	Q_OBJECT

public:
	Register(QWidget *parent = nullptr);
	~Register();

private slots:
	virtual void on_pushButton_Login_now_clicked();
	virtual void on_pushButton_Register_clicked();
	void onRegistrationReply(QNetworkReply* reply);
private:
	Ui::RegisterClass ui;
	QNetworkAccessManager* networkManager;
	void sendRegistrationRequest(const QJsonObject& userData);
signals:
	void loginWindow();
};
