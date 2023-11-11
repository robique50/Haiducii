#pragma once

#include <QMainWindow>
#include "Register.qrc"
#include "ui_Register.h"

class Register : public QMainWindow
{
	Q_OBJECT

public:
	Register(QWidget *parent = nullptr);
	~Register();

private slots:
	void on_pushButton_Login_now_clicked();
	void on_pushButton_Register_clicked();
private:
	Ui::RegisterClass ui;
};
