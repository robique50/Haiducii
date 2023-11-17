#include "FrontEnd.h"
#include <iostream>

FrontEnd::FrontEnd(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    registerWindow = new Register();
    gameWindow = new Game();
    connect(registerWindow, &Register::loginWindow, this, &FrontEnd::show);
    // connect(registerWindow, &Register::registrationCompleted, this, &FrontEnd::show);
    connect(this, &FrontEnd::loginSuccessful, gameWindow, &Game::show);
    

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

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Error", "Please enter both username and password.");
        return;
    }

    emit loginSuccessful();

    gameWindow->show();
    this->close();

    
}