#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QTimer>
#include <QMainWindow>
#include "ui_Game.h"
#include "ui_mainwindow.h"
#include "drawingboard.h"
#include <memory>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();
    void setUsername(const QString& username);
    void setRoomID(const QString& roomID);
    void setUserID(const int& userID);
    void clearChat();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void penWidth();
    void penColor();
    void onLeaveGameButtonClicked();
    void updateTimer();
    void connectPenColor();
    void sendButtonClicked();
    void updateChat();
    void onChatPosted(QNetworkReply* reply);
    void onChatUpdated(QNetworkReply* reply);
signals:
    void leaveGame();
    

private:
    void createActions();
    void endRound();
    void startNewRound();

    QString m_username;
    int m_userID;
    QString m_roomID;

    std::unique_ptr<QAction> eraseAct;
    std::unique_ptr<QAction> exitAct;
    std::unique_ptr<QAction> penColorAct;
    std::unique_ptr<QAction> penWidthAct;
    std::unique_ptr<QAction> clearScreenAct;

    DrawingBoard* drawingBoard = nullptr;

    Ui::MainWindow uiMain;
    Ui::GameClass uiGame;

    std::unique_ptr<QTimer> timer;
    int timeLeft;
};

#endif

