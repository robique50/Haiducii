#include "CreatePrivateRoom.h"

CreatePrivateRoom::CreatePrivateRoom(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

CreatePrivateRoom::~CreatePrivateRoom()
{}

void CreatePrivateRoom::on_pushButton_generateCode_clicked()
{
	QString temp = "alalal12";
	QLineEdit* generateCodeLineEdit = findChild<QLineEdit*>("lineEdit_generateCode");
	generateCodeLineEdit->setText(temp);
}
