#include "Register.h"

Register::Register(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

Register::~Register()
{}

void Register::on_pushButton_Login_now_clicked()
{
	this->close();
	emit loginWindow();
}

void Register::on_pushButton_Register_clicked()
{
	QString fullname,username, password;
	fullname = ui.lineEdit_FullName->text();
	username = ui.lineEdit_username->text();
	password = ui.lineEdit_password->text();
}
