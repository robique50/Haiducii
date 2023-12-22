#include "CreatePrivateRoom.h"

CreatePrivateRoom::CreatePrivateRoom(QWidget *parent,int userID)
	: QMainWindow(parent),userID(userID)
{
	ui.setupUi(this);
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, &CreatePrivateRoom::onHttpReply);

    playerModel = new QStandardItemModel(this);
    ui.tableView_PlayersConected->setModel(playerModel); 

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &CreatePrivateRoom::fetchPlayerData);
    timer->start(2000);
}

CreatePrivateRoom::~CreatePrivateRoom()
{}

void CreatePrivateRoom::fetchPlayerData() {
    QNetworkRequest request(QUrl("http://localhost:18080/getConnected"));
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

std::string CreatePrivateRoom::generateRandomCode(const int& length)
{
    std::vector<std::pair<int,int>> charSets = {
        {65, 90},  // A-Z
        {97, 122}, // a-z
        {48, 57}   // 0-9
    };

    std::random_device rd;
    std::mt19937 gen(rd());

    std::string randomCode;
    randomCode.reserve(length);

    for (int i = 0; i < length; ++i) {
        int setIndex = std::uniform_int_distribution<int>
            (0, charSets.size() - 1)(gen);
        auto& selectedSet = charSets[setIndex];
        int charCode = std::uniform_int_distribution<int>
            (selectedSet.first, selectedSet.second)(gen);
        randomCode.push_back(static_cast<char>(charCode));
    }

    return randomCode;
}

void CreatePrivateRoom::on_pushButton_Start()
{

}

void CreatePrivateRoom::on_pushButton_generateCode_clicked()
{
    int codeLength = 8;
    QString temp = QString::fromStdString(generateRandomCode(codeLength));
    QLineEdit* generateCodeLineEdit = findChild<QLineEdit*>("lineEdit_generateCode");
    generateCodeLineEdit->setText(temp);

    QPushButton* generateCodeButton = findChild<QPushButton*>("pushButton_generateCode");
    if (generateCodeButton) {
        generateCodeButton->setDisabled(true);
    }
}
