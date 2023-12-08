#include <QtWidgets>
#include "mainwindow.h"

MainWindow::MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent* event)
{
    QMessageBox::StandardButton answer;
    answer = QMessageBox::question(this, tr("Exit Confirmation"),
        tr("Are you sure you want to leave?"),
        QMessageBox::Yes | QMessageBox::No);
    if (answer == QMessageBox::Yes) {
        event->accept();
    }
    else {
        event->ignore();
    }
}

void MainWindow::penColor()
{

}

void MainWindow::createActions()
{

}

void MainWindow::createMenus()
{

}

void MainWindow::penWidth()
{

}

void MainWindow::showMainWindow()
{
    this->show();
}
