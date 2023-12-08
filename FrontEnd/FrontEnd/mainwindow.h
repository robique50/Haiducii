#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>
#include "ui_Game.h"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();
public slots:
    //void playButtonClicked();
    void showMainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void penWidth();
    void penColor();

private:
    void createActions();
    void createMenus();

    QMenu* optionMenu = nullptr;

    QAction* exitAct = nullptr;
    QAction* penColorAct = nullptr;
    QAction* penWidthAct = nullptr;
    QAction* clearScreenAct = nullptr;

    Ui::MainWindow uiMain;
    Ui::GameClass uiGame;
};

#endif
