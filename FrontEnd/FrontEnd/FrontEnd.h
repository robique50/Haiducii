#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FrontEnd.h"

class FrontEnd : public QMainWindow
{
    Q_OBJECT

public:
    FrontEnd(QWidget *parent = nullptr);
    ~FrontEnd();

private:
    Ui::FrontEndClass ui;
};
