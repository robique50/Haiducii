#include "Play.h"
#include <iostream>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>

Play::Play(QWidget* parent, int userID)
	: QMainWindow(parent), networkManager(new QNetworkAccessManager(this)), m_userID(userID)
{
	ui.setupUi(this);
	ui.lineEdit_roomCode->setPlaceholderText("Enter lobby code");

	connect(ui.pushButton_joinGame, &QPushButton::clicked, this, &Play::on_pushButton_joinGame_clicked);
}


Play::~Play()
{
}

void Play::on_pushButton_joinGame_clicked()
{
    QString lobbyCode = ui.lineEdit_roomCode->text();
    if (lobbyCode.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter a lobby code.");
        return;
    }

    QUrl url(QString("http://localhost:18080/joinLobby/%1/%2").arg(lobbyCode).arg(m_userID));
    QNetworkRequest request(url);

    if (!networkManager) {
        networkManager = new QNetworkAccessManager(this);
    }

    QNetworkReply* reply = networkManager->get(request);

    connect(reply, &QNetworkReply::finished, this, &Play::handleJoinLobbyResponse);
}


