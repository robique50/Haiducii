#include "FrontEnd.h"

FrontEnd::FrontEnd(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

FrontEnd::~FrontEnd()
{}

void FrontEnd::on_pushButton_login_clicked()
{
    QString username, password;
    username = ui.lineEdit_username->text();
    password = ui.lineEdit_password->text();

    
}