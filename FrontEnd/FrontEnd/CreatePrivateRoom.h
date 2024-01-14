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
#include "mainwindow.h"

class CreatePrivateRoom : public QMainWindow
{
	Q_OBJECT

public:
	CreatePrivateRoom(QWidget *parent = nullptr,int userID=0, const QString& username="");
	~CreatePrivateRoom();
	void setRoomCode(const QString& code);
	void setUsername(const QString& username);
private slots:
	void onHttpReply(QNetworkReply* reply);
	void showEvent(QShowEvent* event);
	void hideEvent(QHideEvent* event);
	void startButtonClicked();
	

private:
	int getNumberOfPlayers();
signals:
	void createPrivateRoomSignal();
private:
	Ui::CreatePrivateRoomClass ui;
	int userID;
	QString m_username;
	QTimer* timer;
	QString roomCode;

	QNetworkAccessManager* networkManager;
	QStandardItemModel* playerModel;

	void fetchPlayerData();
	void fetchRoomCode();
	void updatePlayerModel(const QJsonObject& json);

};
