#include "FrontEnd.h"

FrontEnd::FrontEnd(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    registerWindow = new Register();
    connect(registerWindow, &Register::loginWindow, this, &FrontEnd::show);
}

FrontEnd::~FrontEnd()
{}

void FrontEnd::on_pushButton_registerNow_clicked()
{
    registerWindow->show();
    this->close();
}

void FrontEnd::on_pushButton_login_clicked()
{
    QString username, password;
    username = ui.lineEdit_username->text();
    password = ui.lineEdit_password->text();

    
}