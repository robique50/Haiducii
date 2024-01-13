#include "Game.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

Game::Game(QWidget* parent, int userID, const QString& username)
	: QMainWindow(parent), m_userID(userID), m_username(username)
{
	ui.setupUi(this);
	ui.label_username->setText("Hello " + m_username);
	createPrivateRoomWindow = new CreatePrivateRoom(this, userID,m_username);
	connect(createPrivateRoomWindow, &CreatePrivateRoom::createPrivateRoomSignal, this, &Game::show);
	connect(ui.pushButton_Play, &QPushButton::clicked, this, &Game::on_pushButton_Play_clicked);
	//connect(ui.pushButton_exit, &QPushButton::clicked, this, &Game::backToLoginScreen);
	
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
	this->m_userID = userID;
}

void Game::on_pushButton_Play_clicked()
{
	if (playWindow) {
		delete playWindow;
	}

	playWindow = new Play(this, m_userID,m_username);
	playWindow->show();
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

void Game::on_pushButton_exit_clicked()
{
	this->close();
}

void Game::on_pushButton_start_clicked()
{
	MainWindow* mainWindow = new MainWindow();
	mainWindow->show();
	this->close();
}

void Game::on_pushButton_create_private_room_clicked()
{
	QNetworkAccessManager* networkManager = new QNetworkAccessManager(this);
	QNetworkRequest request(QUrl("http://localhost:18080/createLobby"));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	QJsonObject jsonObj;
	jsonObj["userID"] = m_userID;

	QJsonDocument doc(jsonObj);
	QByteArray postData = doc.toJson();
	connect(networkManager, &QNetworkAccessManager::finished, this, [this, networkManager](QNetworkReply* reply) {
		if (reply->error()) {
			qDebug() << "Error in network reply:" << reply->errorString();
			reply->deleteLater();
			networkManager->deleteLater();
			return;
		}

		QByteArray response = reply->readAll();
		QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
		if (!jsonDoc.isObject()) {
			qDebug() << "Invalid JSON received";
			return;
		}
		QString roomCode = jsonDoc.object().value("roomCode").toString();
		qDebug() << "Lobby created with code: " << roomCode;

		if (createPrivateRoomWindow) {
			createPrivateRoomWindow->setRoomCode(roomCode);
			createPrivateRoomWindow->setUsername(m_username);
			createPrivateRoomWindow->show();
		}

		reply->deleteLater();
		networkManager->deleteLater();
		this->close();
		});

	networkManager->post(request, postData);
}


