#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FrontEnd.h"

class FrontEnd : public QMainWindow
{
    Q_OBJECT

public:
    FrontEnd(QWidget *parent = nullptr);
    ~FrontEnd();

private slots:
    void on_pushButton_login_clicked();

private:
    Ui::FrontEndClass ui;
};
