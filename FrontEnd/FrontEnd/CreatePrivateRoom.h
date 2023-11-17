#pragma once

#include <QMainWindow>
#include "ui_CreatePrivateRoom.h"

class CreatePrivateRoom : public QMainWindow
{
	Q_OBJECT

public:
	CreatePrivateRoom(QWidget *parent = nullptr);
	~CreatePrivateRoom();

private slots:
	void on_pushButton_generateCode_clicked();

signals:
	void createPrivateRoomSignal();
private:
	Ui::CreatePrivateRoomClass ui;
};
