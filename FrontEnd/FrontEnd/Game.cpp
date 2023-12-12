#include "Game.h"



Game::Game(QWidget *parent,int userID)
	: QMainWindow(parent),userID(userID)
{
	ui.setupUi(this);
	playWindow = new Play();
	createPrivateRoomWindow = new CreatePrivateRoom(this,userID);
	//bool privateRoomConnection = connect(createPrivateRoomWindow, &CreatePrivateRoom::createPrivateRoomSignal, this, &Game::show);
	//bool playWindowConnection = connect(playWindow, &Play::playWindowSignal, this, &Game::show);
	connect(createPrivateRoomWindow, &CreatePrivateRoom::createPrivateRoomSignal, this, &Game::show);
	connect(ui.pushButton_Play, &QPushButton::clicked, this, &Game::playButtonClicked);
	/*if (privateRoomConnection) {
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
	}*/
}

Game::~Game()
{
	if (createPrivateRoomWindow) {
		delete createPrivateRoomWindow;
	}
	if (playWindow) {
		delete playWindow;
	}
}

void Game::setUserID(int userID)
{
	this->userID = userID;
}

/*void Game::on_pushButton_Play_clicked()
{
	if (playWindow) {
		playWindow->show();
		this->close();
	}
}*/

void Game::playButtonClicked()
{
		MainWindow* drawingBoard = new MainWindow;
		drawingBoard->show();
		this->close();
}

void Game::on_pushButton_create_private_room_clicked()
{
	if (createPrivateRoomWindow) {
		createPrivateRoomWindow->show();
		this->close();
	}
}


