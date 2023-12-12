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



void Game::playButtonClicked()
{
	mainWindow = new MainWindow;
	connect(mainWindow, &MainWindow::leaveGame, this, &Game::showAndHandleLeave);
	mainWindow->show();
	this->hide();
}

void Game::showAndHandleLeave()
{
	this->show();
	if (mainWindow) {
		mainWindow->deleteLater();
		mainWindow = nullptr;
	}
}

void Game::on_pushButton_create_private_room_clicked()
{
	if (createPrivateRoomWindow) {
		createPrivateRoomWindow->show();
		this->close();
	}
}


