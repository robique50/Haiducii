#pragma once

#include <QMainWindow>
#include <QNetworkAccessManager>
#include "CreatePrivateRoom.h"
#include "ui_Play.h"

class Play : public QMainWindow
{
	Q_OBJECT

public:
	Play(QWidget* parent = nullptr, int userID = 0);
	~Play();

signals:
	void joinGame(const QString& roomCode);

private slots:
	void on_pushButton_joinGame_clicked();
	void handleJoinLobbyResponse();


private:
	CreatePrivateRoom* createPrivateRoomWindow= new CreatePrivateRoom();
	Ui::PlayClass ui;
	QNetworkAccessManager* networkManager;
	int m_userID;

};
