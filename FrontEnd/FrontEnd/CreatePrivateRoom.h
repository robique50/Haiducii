#pragma once

#include <QMainWindow>
#include "ui_CreatePrivateRoom.h"
#include <random>
#include <tuple>
#include <string>
#include <vector>

class CreatePrivateRoom : public QMainWindow
{
	Q_OBJECT

public:
	CreatePrivateRoom(QWidget *parent = nullptr,int userID=0);
	~CreatePrivateRoom();
	std::string generateRandomCode(const int& length);
private slots:
	void on_pushButton_generateCode_clicked();

signals:
	void createPrivateRoomSignal();
private:
	Ui::CreatePrivateRoomClass ui;
	int userID;
};
