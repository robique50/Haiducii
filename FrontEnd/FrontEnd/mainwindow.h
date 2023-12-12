#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>
#include "ui_Game.h"
#include "ui_mainwindow.h"
#include "drawingboard.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void penWidth();
    void penColor();
    void onChatInputReturnPressed();
    void onLeaveGameButtonClicked();
    void updateTimer();

signals:
    void leaveGame();
    

private:
    void createActions();
    void createMenus();
    void endRound();
    void startNewRound();

    QMenu* optionMenu = nullptr;

    QAction* eraseAct = nullptr;
    QAction* exitAct = nullptr;
    QAction* penColorAct = nullptr;
    QAction* penWidthAct = nullptr;
    QAction* clearScreenAct = nullptr;

    DrawingBoard* drawingBoard = nullptr;

    Ui::MainWindow uiMain;
    Ui::GameClass uiGame;

    QTimer* timer;
    int timeLeft;

};

#endif

