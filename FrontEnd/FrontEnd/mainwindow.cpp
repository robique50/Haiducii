#include <QtWidgets>
#include "mainwindow.h"
#include "drawingboard.h"
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>


MainWindow::MainWindow()
{
	uiMain.setupUi(this);
	drawingBoard = new DrawingBoard;
	timer = std::make_unique<QTimer>(this);
	connect(timer.get(), &QTimer::timeout, this, &MainWindow::updateTimer);

	uiMain.progressBar_timer = findChild<QProgressBar*>("progressBar_timer");
	uiMain.label_timer = findChild<QLabel*>("label_timer");

	timeLeft = 120;
	uiMain.progressBar_timer->setMaximum(timeLeft);
	uiMain.progressBar_timer->setValue(timeLeft);
	timer->start(1000);

	createActions();
	setWindowTitle(tr("Skribbl"));
	uiMain.verticalLayout_drawingBoard->addWidget(drawingBoard);
	connect(uiMain.pushButton_leave, &QPushButton::clicked, this, &MainWindow::onLeaveGameButtonClicked);
	connectPenColor();
	connect(uiMain.pushButton_ClearDrawing, &QPushButton::clicked, this, [this]() {
		drawingBoard->clearImage();
		});
	connect(uiMain.hSliderPenWidth, &QSlider::valueChanged, this, [this](int newValue) {
		drawingBoard->setPenWidth(newValue);
		});
	connect(uiMain.pushButton_FillDrawing, &QPushButton::clicked, this, [this]() {
		drawingBoard->setFillMode(true);
		});
	connect(uiMain.sendMessage, &QPushButton::clicked, this, &MainWindow::sendButtonClicked);
	resize(1000, 800);
	//connect(uiMain.lineEdit_chatInput, &QLineEdit::returnPressed, this, &MainWindow::onChatInputReturnPressed);
}

void MainWindow::setUsername(const QString& username)
{
	m_username = username;
}

void MainWindow::setRoomID(const QString& roomID)
{
	m_roomID = roomID;
}

void MainWindow::setUserID(const int& userID)
{
	m_userID = userID;
}

void MainWindow::clearChat()
{
	QNetworkRequest request(QUrl("http://localhost:18080/clearChat"));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

	QJsonObject json;
	json["roomID"] = m_roomID;

	QNetworkAccessManager* manager = new QNetworkAccessManager(this);
	manager->post(request, QJsonDocument(json).toJson());
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	QMessageBox::StandardButton answer;
	answer = QMessageBox::question(this, tr("Exit Confirmation"),
		tr("Are you sure you want to leave?"),
		QMessageBox::Yes | QMessageBox::No);
	if (answer == QMessageBox::Yes) {
		clearChat();
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
		drawingBoard->setPenColor(QColor(0, 0, 0));
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

void MainWindow::sendButtonClicked()
{
	QString text = uiMain.chatInput->toPlainText();
    if (text.isEmpty() || text.size() < 3)
        return;

    QNetworkRequest request(QUrl("http://localhost:18080/addChat"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["roomID"] = m_roomID;
    json["username"] = m_username;
    json["text"] = text;

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::onChatPosted);

    manager->post(request, QJsonDocument(json).toJson());
    uiMain.chatInput->clear();
}

void MainWindow::updateChat()
{
	QNetworkRequest request(QUrl("http://localhost:18080/getChat"));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

	QJsonObject json;
	json["roomID"] = m_roomID;

	QNetworkAccessManager* manager = new QNetworkAccessManager(this);
	connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::onChatUpdated);
	manager->post(request, QJsonDocument(json).toJson());
}

void MainWindow::onChatPosted(QNetworkReply* reply)
{
	if (reply->error() != QNetworkReply::NoError) {
		qDebug() << "Error posting chat message: " << reply->errorString();
	}
	else {
		updateChat();
	}
	reply->deleteLater();
}

void MainWindow::onChatUpdated(QNetworkReply* reply)
{
	if (reply->error() != QNetworkReply::NoError) {
		qDebug() << "Error updating chat:" << reply->errorString();
	}
	else {
		QString chatText = QString::fromUtf8(reply->readAll());
		uiMain.chat->setPlainText(chatText);
	}
	reply->deleteLater();
}

void MainWindow::createActions()
{
	exitAct = std::make_unique<QAction>(tr("&Exit"), this);
	exitAct->setShortcuts(QKeySequence::Quit);
	connect(exitAct.get(), &QAction::triggered, this, &MainWindow::close);

	penColorAct = std::make_unique<QAction>(tr("&Pen Color..."), this);
	connect(penColorAct.get(), &QAction::triggered, this, &MainWindow::penColor);

	penWidthAct = std::make_unique<QAction>(tr("Pen &Width..."), this);
	connect(penWidthAct.get(), &QAction::triggered, this, &MainWindow::penWidth);

	eraseAct = std::make_unique<QAction>(tr("&Erase Mode"), this);
	eraseAct->setShortcut(tr("Ctrl+E"));
	connect(eraseAct.get(), &QAction::triggered, drawingBoard, &DrawingBoard::toggleEraseMode);

	clearScreenAct = std::make_unique<QAction>(tr("&Clear Screen"), this);
	clearScreenAct->setShortcut(tr("Ctrl+L"));
	connect(clearScreenAct.get(), &QAction::triggered, drawingBoard, &DrawingBoard::clearImage);

	addAction(exitAct.get());
	addAction(penColorAct.get());
	addAction(penWidthAct.get());
	addAction(eraseAct.get());
	addAction(clearScreenAct.get());
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