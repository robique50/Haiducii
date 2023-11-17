#pragma once

#include <QMainWindow>
#include "ui_Game.h"
#include "CreatePrivateRoom.h"
#include "Play.h"
#include <qmessagebox.h>

class Game : public QMainWindow
{
	Q_OBJECT

public:
	Game(QWidget *parent = nullptr);
	~Game();

private slots:
	 virtual void on_pushButton_create_private_room_clicked();
	 virtual void on_pushButton_Play_clicked();


private:
	Ui::GameClass ui;
	CreatePrivateRoom* createPrivateRoomWindow = nullptr;
	Play* playWindow = nullptr;
	
};
