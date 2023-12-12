#include <QtWidgets>
#include "mainwindow.h"
#include "drawingboard.h"

MainWindow::MainWindow()
{
    {
    uiMain.setupUi(this);
    drawingBoard = new DrawingBoard;

    createActions();
    createMenus();
    setWindowTitle(tr("Skribbl"));
    uiMain.verticalLayout_drawingBoard->addWidget(drawingBoard);
    connect(uiMain.lineEdit_chatInput, &QLineEdit::returnPressed, this, &MainWindow::onChatInputReturnPressed);
    connect(uiMain.pushButton_leave, &QPushButton::clicked, this, &MainWindow::onLeaveGameButtonClicked);
    
    resize(1000, 800);
}
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

void MainWindow::onChatInputReturnPressed()
{
	QString message = uiMain.lineEdit_chatInput->text();
    if (!message.isEmpty())
    {
    uiMain.textEdit_chatDislay->append(message);
	uiMain.lineEdit_chatInput->clear();
    }
}

void MainWindow::onLeaveGameButtonClicked()
{
    emit leaveGame();
    this->hide(); 
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

    eraseAct = new QAction(tr("&Erase Mode"), this);
    eraseAct->setShortcut(tr("Ctrl+E"));
    connect(eraseAct, SIGNAL(triggered()), drawingBoard, SLOT(toggleEraseMode()));

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
    optionMenu->addAction(eraseAct);
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
