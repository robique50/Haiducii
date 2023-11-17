#include "Game.h"


Game::Game(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//createRoomWindow = new CreateRoom();
	playWindow = new Play();
	createPrivateRoomWindow = new CreatePrivateRoom();
	//auto connectResult = 
	connect(createPrivateRoomWindow, &CreatePrivateRoom::createPrivateRoomSignal, this, &Game::show);
	/*if (!connectResult) {
		qDebug() << "Connection error: " << QObject::connect(ui.pushButton_create_private_room, &QPushButton::clicked, this, &Game::on_pushButton_create_private_room_clicked);
	}*/
}

Game::~Game()
{}

void Game::on_pushButton_create_private_room_clicked()
{
	createPrivateRoomWindow->show();
	this->close();
}


