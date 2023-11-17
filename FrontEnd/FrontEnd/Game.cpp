#include "Game.h"



Game::Game(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	playWindow = new Play();
	createPrivateRoomWindow = new CreatePrivateRoom();
	bool privateRoomConnection = connect(createPrivateRoomWindow, &CreatePrivateRoom::createPrivateRoomSignal, this, &Game::show);
	bool playWindowConnection = connect(playWindow, &Play::playWindowSignal, this, &Game::show);
	if (privateRoomConnection) {
		QMessageBox::information(this, "Connection Status", "Connection to createPrivateRoomSignal successful!");
	}
	else {
		QMessageBox::critical(this, "Connection Status", "Connection to createPrivateRoomSignal failed!");
	}

	if (playWindowConnection) {
		QMessageBox::information(this, "Connection Status", "Connection to playWindowSignal successful!");
	}
	else {
		QMessageBox::critical(this, "Connection Status", "Connection to playWindowSignal failed!");
	}
}

Game::~Game()
{}

void Game::on_pushButton_Play_clicked()
{
	playWindow->show();
	this->close();
}

void Game::on_pushButton_create_private_room_clicked()
{
	createPrivateRoomWindow->show();
	this->close();
}


