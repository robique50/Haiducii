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

    connect(ui.pushButton_Start, &QPushButton::clicked, this, &CreatePrivateRoom::startButtonClicked);
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

void CreatePrivateRoom::startButtonClicked()
{
    MainWindow* mainWindow = new MainWindow();
    mainWindow->setAttribute(Qt::WA_DeleteOnClose);
    mainWindow->show();
    this->close();
}

void CreatePrivateRoom::setRoomCode(const QString & code)
{
    roomCode = code;
    if (ui.lineEdit_roomCode)
    {
        ui.lineEdit_roomCode->setText(roomCode);
    }
}

void CreatePrivateRoom::fetchPlayerData() {
    if (roomCode.isEmpty()) {
        return;
    }

    QNetworkRequest request(QUrl(QString("http://localhost:18080/getLobbyInfo?lobbyCode=%1").arg(roomCode)));
    networkManager->get(request);
}


void CreatePrivateRoom::fetchRoomCode() {
    QNetworkRequest request(QUrl("http://localhost:18080/createLobby"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject jsonObj;
    jsonObj["userID"] = userID;

    QJsonDocument doc(jsonObj);
    QByteArray postData = doc.toJson();

    networkManager->post(request, postData);
}


void CreatePrivateRoom::onHttpReply(QNetworkReply* reply) {
    if (reply->error()) {
        qDebug() << "Error in network reply:" << reply->errorString();
        return;
    }

    QByteArray response = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(response);

    if (jsonDoc.isObject()) {
        QJsonObject jsonObj = jsonDoc.object();
        if (jsonObj.contains("players")) {
            updatePlayerModel(jsonObj);
        }
    }
}


void CreatePrivateRoom::updatePlayerModel(const QJsonObject& json) {
    playerModel->clear();
    playerModel->setHorizontalHeaderLabels({ "Player Name" });

    const QJsonArray& players = json["players"].toArray();
    for (const QJsonValue& playerVal : players) {
        QStandardItem* nameItem = new QStandardItem(playerVal.toString());
        playerModel->appendRow({ nameItem });
    }
}



