#include <QtWidgets>
#include "mainwindow.h"
#include "drawingboard.h"

MainWindow::MainWindow()
{
    {
    uiMain.setupUi(this);
    drawingBoard = new DrawingBoard;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimer);

    // Setup the progress bar and label (Assuming you've set their object names in Qt Designer)
    uiMain.progressBar_timer = findChild<QProgressBar*>("progressBar_timer");
    uiMain.label_timer = findChild<QLabel*>("label_timer");

    timeLeft = 60; // 2 minutes, for example
    uiMain.progressBar_timer->setMaximum(timeLeft);
    uiMain.progressBar_timer->setValue(timeLeft);
    timer->start(1000); // Update every second

    createActions();
    createMenus();
    setWindowTitle(tr("Skribbl"));
    uiMain.verticalLayout_drawingBoard->addWidget(drawingBoard);
    connect(uiMain.lineEdit_chatInput, &QLineEdit::returnPressed, this, &MainWindow::onChatInputReturnPressed);
    connect(uiMain.pushButton_leave, &QPushButton::clicked, this, &MainWindow::onLeaveGameButtonClicked);
    connectPenColor();
    connect(uiMain.pushButton_ClearDrawing, &QPushButton::clicked, this, [this]() {
        drawingBoard->clearImage();
        });
    connect(uiMain.hSliderPenWidth, &QSlider::valueChanged, this, [this](int newValue) {
        drawingBoard->setPenWidth(newValue);
        });

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

void MainWindow::updateTimer()
{
    timeLeft--;
    uiMain.progressBar_timer->setValue(timeLeft);
    uiMain.label_timer->setText(QString::number(timeLeft) + " seconds");

    if (timeLeft <= 0) {
        timer->stop();
        endRound();
    }
}

void MainWindow::connectPenColor()
{
    connect(uiMain.pushColorWhite, &QPushButton::clicked, this, [this]() {
        drawingBoard->setPenColor(QColor(255, 255, 255));
        });
    connect(uiMain.pushColorGray, &QPushButton::clicked, this, [this]() {
        drawingBoard->setPenColor(QColor(116, 116, 116));
        });
    connect(uiMain.pushColorBlack, &QPushButton::clicked, this, [this]() {
        drawingBoard->setPenColor(QColor(0,0, 0));
        });
    connect(uiMain.pushColorRed, &QPushButton::clicked, this, [this]() {
        drawingBoard->setPenColor(QColor(255, 0, 0));
        });
    connect(uiMain.pushColorBrown, &QPushButton::clicked, this, [this]() {
        drawingBoard->setPenColor(QColor(150, 75, 0));
        });
    connect(uiMain.pushColorOrange, &QPushButton::clicked, this, [this]() {
        drawingBoard->setPenColor(QColor(255, 85, 0));
        });
    connect(uiMain.pushColorYellow, &QPushButton::clicked, this, [this]() {
        drawingBoard->setPenColor(QColor(255, 255, 0));
        });
    connect(uiMain.pushColorLime, &QPushButton::clicked, this, [this]() {
        drawingBoard->setPenColor(QColor(0, 255, 0));
        });
    connect(uiMain.pushColorGreen, &QPushButton::clicked, this, [this]() {
        drawingBoard->setPenColor(QColor(0, 109, 0));
        });
    connect(uiMain.pushColorBlue, &QPushButton::clicked, this, [this]() {
        drawingBoard->setPenColor(QColor(0, 0, 255));
        });
    connect(uiMain.pushColorPurple, &QPushButton::clicked, this, [this]() {
        drawingBoard->setPenColor(QColor(193, 6, 255));
        });
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

void MainWindow::endRound()
{
    QMessageBox::information(this, "Time's Up", "The round has ended.");
    // Additional logic for ending the round
    // Call startNewRound() after a delay or based on game logic
    QTimer::singleShot(3000, this, &MainWindow::startNewRound); // Example: 3-second delay
}

void MainWindow::startNewRound()
{
    // Logic for starting a new round
    timeLeft = 10; // Reset the timer for the new round
    uiMain.progressBar_timer->setMaximum(timeLeft);
    uiMain.progressBar_timer->setValue(timeLeft);
    timer->start(1000);
    drawingBoard->clearImage(); // Clear the drawing board
    // Additional setup for the new round
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

