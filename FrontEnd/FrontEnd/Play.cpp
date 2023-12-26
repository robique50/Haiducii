#include "Play.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>

Play::Play(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//networkManager = new QNetworkAccessManager(this);
	ui.lineEdit_roomCode->setPlaceholderText("Enter lobby code");
	//connect(ui.pushButton_joinGame, &QPushButton::clicked, this, &Play::on_pushButton_joinGame_clicked);

}

Play::~Play()
{}
