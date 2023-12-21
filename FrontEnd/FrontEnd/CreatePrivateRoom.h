#pragma once

#include <QMainWindow>
#include "ui_CreatePrivateRoom.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardItemModel>
#include <QTimer>
#include <random>
#include <tuple>
#include <string>
#include <vector>

class CreatePrivateRoom : public QMainWindow
{
	Q_OBJECT

public:
	CreatePrivateRoom(QWidget *parent = nullptr,int userID=0);
	~CreatePrivateRoom();
	std::string generateRandomCode(const int& length);
private slots:
	void on_pushButton_generateCode_clicked();
	void on_pushButton_Start();
	void onHttpReply(QNetworkReply* reply);

signals:
	void createPrivateRoomSignal();
private:
	Ui::CreatePrivateRoomClass ui;
	int userID;

	QNetworkAccessManager* networkManager;
	QStandardItemModel* playerModel;

	void fetchPlayerData();
	void updatePlayerModel(const QJsonObject& json);

};
