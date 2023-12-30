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

void Play::handleJoinLobbyResponse()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) {
        QMessageBox::critical(this, "Error", "An unexpected error occurred.");
        return;
    }

    if (reply->error()) {
        QMessageBox::critical(this, "Error", "Failed to join the lobby: " + reply->errorString());
        reply->deleteLater();
        return;
    }


    QByteArray responseBytes = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseBytes);
    if (!jsonResponse.isObject()) {
        QMessageBox::critical(this, "Error", "Invalid response from server.");
        reply->deleteLater();
        return;
    }

    QJsonObject responseObject = jsonResponse.object();
    QString message = responseObject.value("message").toString();
    bool success = responseObject.value("success").toBool();

    if (success) {

        QMessageBox::information(this, "Lobby", "Successfully joined the lobby!");
        // Aici puteți adăuga cod pentru a deschide fereastra lobby-ului sau pentru a actualiza interfața
    }
    else {
        // Afisează un mesaj de eroare
        QMessageBox::warning(this, "Failed", message);
    }

    reply->deleteLater();
}

