#pragma once

#include <QMainWindow>
#include "ui_Game.h"

class Game : public QMainWindow
{
	Q_OBJECT

public:
	Game(QWidget *parent = nullptr);
	~Game();

private:
	Ui::GameClass ui;

signals:
	void loginSuccess();
	
};
