#include <QtWidgets>
#include "mainwindow.h"
#include "drawingboard.h"

MainWindow::MainWindow()
{
    drawingBoard = new DrawingBoard;
    setCentralWidget(drawingBoard);
    createActions();
    createMenus();
    setWindowTitle(tr("Skribbl"));
    uiMain.verticalLayout->addWidget(drawingBoard);
    resize(500, 500);
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
    QColor newColor = QColorDialog::getColor(drawingBoard->penColor());

    if (newColor.isValid())
        drawingBoard->setPenColor(newColor);
}

void MainWindow::createActions()
{
    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    penColorAct = new QAction(tr("&Pen Color..."), this);
    connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));

    penWidthAct = new QAction(tr("Pen &Width..."), this);
    connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));

    clearScreenAct = new QAction(tr("&Clear Screen"), this);
    clearScreenAct->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAct, SIGNAL(triggered()),
        drawingBoard, SLOT(clearImage()));
}

void MainWindow::createMenus()
{
    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addAction(penColorAct);
    optionMenu->addAction(penWidthAct);
    optionMenu->addSeparator();
    optionMenu->addAction(clearScreenAct);
    menuBar()->addMenu(optionMenu);
}

void MainWindow::penWidth()
{
    bool ok;

    int newWidth = QInputDialog::getInt(this, tr("Scribble"),
        tr("Select pen width:"),
        drawingBoard->penWidth(),
        1, 50, 1, &ok);
    if (ok)
        drawingBoard->setPenWidth(newWidth);
}

void MainWindow::showMainWindow()
{
    this->show();
}
