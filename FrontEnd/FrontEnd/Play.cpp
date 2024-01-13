#include "Play.h"
#include <iostream>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>

Play::Play(QWidget* parent, int userID, const QString& username)
	: QMainWindow(parent), networkManager(new QNetworkAccessManager(this)), m_userID(userID), m_username(username)
{
	ui.setupUi(this);
	ui.lineEdit_roomCode->setPlaceholderText("Enter lobby code");

   
    //disconnect(ui.pushButton_joinGame, &QPushButton::clicked, this, &Play::on_pushButton_joinGame_clicked);
    connect(ui.joinGame, &QPushButton::clicked, this, &Play::on_pushButton_joinGame_clicked);
}



Play::~Play()
{
    disconnect(ui.joinGame, &QPushButton::clicked, this, &Play::on_pushButton_joinGame_clicked);
}


void Play::on_pushButton_joinGame_clicked() {
    ui.joinGame->setEnabled(false);
    QString lobbyCode = ui.lineEdit_roomCode->text().trimmed();
    if (lobbyCode.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter a lobby code");
        return;
    }

    
    QJsonObject json;
    json["userID"] = m_userID;
    json["lobbyCode"] = lobbyCode;

    
    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    
    QNetworkRequest request(QUrl("http://localhost:18080/joinLobby"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    
    QNetworkReply* reply = networkManager->post(request, data);

    connect(reply, &QNetworkReply::finished, [this, reply, lobbyCode]() {
        ui.joinGame->setEnabled(true);
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseBytes = reply->readAll();
            QJsonDocument jsonResponse = QJsonDocument::fromJson(responseBytes);
            QJsonObject responseObject = jsonResponse.object();

            QString message = responseObject["message"].toString();
            QMessageBox::information(this, "Info", message);

            
            CreatePrivateRoom* createPrivateRoomWindow = new CreatePrivateRoom(this, m_userID,m_username);
            createPrivateRoomWindow->setRoomCode(lobbyCode);
            createPrivateRoomWindow->show();
            this->hide(); 
        }
        else {
            QMessageBox::critical(this, "Error", reply->errorString());
        }
        reply->deleteLater();
        });
}









