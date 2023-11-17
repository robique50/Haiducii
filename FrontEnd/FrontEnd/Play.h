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

private:
	Ui::PlayClass ui;
};
