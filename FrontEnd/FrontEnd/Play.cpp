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

   
    disconnect(ui.pushButton_joinGame, &QPushButton::clicked, this, &Play::on_pushButton_joinGame_clicked);
    connect(ui.pushButton_joinGame, &QPushButton::clicked, this, &Play::on_pushButton_joinGame_clicked);
}



Play::~Play()
{
    disconnect(ui.pushButton_joinGame, &QPushButton::clicked, this, &Play::on_pushButton_joinGame_clicked);
}


void Play::on_pushButton_joinGame_clicked() {
    ui.pushButton_joinGame->setEnabled(false);
    QString lobbyCode = ui.lineEdit_roomCode->text().trimmed();
    if (lobbyCode.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter a lobby code");
        return;
    }

    // Prepare the JSON object
    QJsonObject json;
    json["userID"] = m_userID;
    json["lobbyCode"] = lobbyCode;

    // Convert JSON object to byte array
    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    // Create the network request
    QNetworkRequest request(QUrl("http://localhost:18080/joinLobby"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Send POST request
    QNetworkReply* reply = networkManager->post(request, data);

    // Handle the response
    connect(reply, &QNetworkReply::finished, [this, reply, lobbyCode]() {
        ui.pushButton_joinGame->setEnabled(true);
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseBytes = reply->readAll();
            QJsonDocument jsonResponse = QJsonDocument::fromJson(responseBytes);
            QJsonObject responseObject = jsonResponse.object();

            QString message = responseObject["message"].toString();
            QMessageBox::information(this, "Info", message);

            // Show the create private room window
            CreatePrivateRoom* createPrivateRoomWindow = new CreatePrivateRoom(this, m_userID);
            createPrivateRoomWindow->setRoomCode(lobbyCode);
            createPrivateRoomWindow->show();
            this->hide(); // Optionally hide the current window
        }
        else {
            QMessageBox::critical(this, "Error", reply->errorString());
        }
        reply->deleteLater();
        });
}









