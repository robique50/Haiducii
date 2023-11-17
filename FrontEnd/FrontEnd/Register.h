#pragma once

#include <QMainWindow>
#include "ui_Register.h"

class Register : public QMainWindow
{
	Q_OBJECT

public:
	Register(QWidget *parent = nullptr);
	~Register();

private slots:
	virtual void on_pushButton_Login_now_clicked();
	virtual void on_pushButton_Register_clicked();
private:
	Ui::RegisterClass ui;
signals:
	void loginWindow();
	void registrationCompleted();
};
