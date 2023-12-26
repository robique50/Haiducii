#pragma once

#include <QMainWindow>
#include "ui_Play.h"

class Play : public QMainWindow
{
	Q_OBJECT

public:
	Play(QWidget *parent = nullptr);
	~Play();

signals:
	void playWindowSignal();
	void joinGame(const QString& roomCode);

private slots:
	//void on_pushButton_joinGame_clicked();

private:
	Ui::PlayClass ui;
	//QNetworkAccessManager* networkManager=nullptr;
};
