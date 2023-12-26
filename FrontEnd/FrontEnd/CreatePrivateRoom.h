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
	void setRoomCode(const QString& code);
private slots:
	void on_pushButton_Start();
	void onHttpReply(QNetworkReply* reply);

signals:
	void createPrivateRoomSignal();
private:
	Ui::CreatePrivateRoomClass ui;
	int userID;
	QString roomCode;

	QNetworkAccessManager* networkManager;
	QStandardItemModel* playerModel;

	void fetchPlayerData();
	void fetchRoomCode();
	void updatePlayerModel(const QJsonObject& json);

};
