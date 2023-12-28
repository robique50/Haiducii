#include "CreatePrivateRoom.h"

CreatePrivateRoom::CreatePrivateRoom(QWidget *parent,int userID)
	: QMainWindow(parent),userID(userID)
{
	ui.setupUi(this);
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, &CreatePrivateRoom::onHttpReply);

    playerModel = new QStandardItemModel(this);
    ui.tableView_PlayersConected->setModel(playerModel); 

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &CreatePrivateRoom::fetchPlayerData);
    timer->start(2000);
    //fetchRoomCode();
}

CreatePrivateRoom::~CreatePrivateRoom()
{}

void CreatePrivateRoom::showEvent(QShowEvent* event) {
    QMainWindow::showEvent(event);
    timer->start(2000); 
}

void CreatePrivateRoom::hideEvent(QHideEvent* event) {
    QMainWindow::hideEvent(event);
    timer->stop(); 
}

void CreatePrivateRoom::setRoomCode(const QString & code)
{
    roomCode = code;    
    ui.lineEdit_roomCode=findChild<QLineEdit*>("ui.lineEdit_roomCode");
    if(ui.lineEdit_roomCode)
	{
		ui.lineEdit_roomCode->setText(roomCode);
	}
}

void CreatePrivateRoom::fetchPlayerData() {
    QNetworkRequest request(QUrl("http://localhost:18080/getConnected"));
    networkManager->get(request);
}

void CreatePrivateRoom::fetchRoomCode()
{
    QNetworkRequest request(QUrl("http://localhost:18080/getRoomCode"));  
    networkManager->get(request);
}

void CreatePrivateRoom::onHttpReply(QNetworkReply* reply) {
    if (reply->error()) {
        qDebug() << "Error in network reply:" << reply->errorString();
        return;
    }

    QByteArray response = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
    updatePlayerModel(jsonDoc.object());
}

void CreatePrivateRoom::updatePlayerModel(const QJsonObject& json) {
    playerModel->clear(); 
    playerModel->setHorizontalHeaderLabels({ "Player ID", "Player Name" }); 

    const QJsonObject& players = json["players"].toObject();
    for (const auto& id : players.keys()) {
        const QJsonObject& playerData = players[id].toObject();
        QStandardItem* idItem = new QStandardItem(id);
        QStandardItem* nameItem = new QStandardItem(playerData["name"].toString());

        playerModel->appendRow({ idItem, nameItem });
    }
}

void CreatePrivateRoom::on_pushButton_Start()
{

}

