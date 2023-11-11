#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FrontEnd.h"
#include "Register.h"

class FrontEnd : public QMainWindow
{
    Q_OBJECT

public:
    FrontEnd(QWidget *parent = nullptr);
    ~FrontEnd();

private slots:
    virtual void on_pushButton_login_clicked();
    virtual void on_pushButton_registerNow_clicked();

private:
    Ui::FrontEndClass ui;
    Register* registerWindow = nullptr;
};
