#include <QtWidgets>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#endif
#endif

#include "drawingboard.h"

DrawingBoard::DrawingBoard(QWidget* parent)
	: QWidget{ parent },
	modified{ false },
	scribbling{ false },
	myPenWidth{ 5 },
	myPenColor{ Qt::blue },
	eraserMode{ false },
	fillModeActive{ false },
	currentMode{ PenMode::Pen },
	lastUsedPenColor{ Qt::blue }

{
	setAttribute(Qt::WA_StaticContents);
}

void DrawingBoard::setPenColor(const QColor& newColor)
{
	if (!eraserMode) {
		lastUsedPenColor = newColor;
	}
	myPenColor = newColor;
}

void DrawingBoard::setPenWidth(int newWidth)
{
	myPenWidth = qBound(1, newWidth, 50);
}

void DrawingBoard::setDrawingMode(PenMode mode)
{
	currentMode = mode;
	if (currentMode == PenMode::Eraser) {
		lastUsedPenColor = myPenColor;
		myPenColor = Qt::white;
	}
	else if (!eraserMode) {
		myPenColor = lastUsedPenColor;
	}
	setPenWidth(myPenWidth);
}

void DrawingBoard::setModified(bool modified)
{
	this->modified = modified;
}

void DrawingBoard::setFillColor(const QColor& newColor)
{
	lastFillColor = newColor;
}

void DrawingBoard::setFillMode(bool active)
{
	fillModeActive = active;
}

void DrawingBoard::clearImage()
{
	image.fill(qRgb(255, 255, 255));
	modified = true;
	update();
}

void DrawingBoard::setEraserMode()
{
	eraserMode = !eraserMode;
	if (eraserMode) {
		lastUsedPenColor = myPenColor;
		myPenColor = Qt::white;
	}
	else {
		myPenColor = lastUsedPenColor;
	}
	setPenWidth(myPenWidth);
}

void DrawingBoard::toggleEraseMode()
{
	setDrawingMode(currentMode == PenMode::Pen ? PenMode::Eraser : PenMode::Pen);
}

void DrawingBoard::fillColor(const QPoint& point, const QColor& newColor)
{
	QColor oldColor = image.pixelColor(point);

	if (oldColor == newColor) return;

	std::stack<QPoint> stack;
	stack.push(point);

	while (!stack.empty()) {
		QPoint current = stack.top();
		stack.pop();

		if (image.pixelColor(current) == oldColor) {
			image.setPixelColor(current, newColor);

			stack.push(QPoint(current.x() + 1, current.y()));
			stack.push(QPoint(current.x() - 1, current.y()));
			stack.push(QPoint(current.x(), current.y() + 1));
			stack.push(QPoint(current.x(), current.y() - 1));
		}
	}

	update();
}

void DrawingBoard::mouseMoveEvent(QMouseEvent* event)
{
	if ((event->buttons() & Qt::LeftButton) && scribbling)
	{
		if (currentMode == PenMode::Eraser) {
			drawLineTo(event->pos(), true);
		}
		else {
			drawLineTo(event->pos(), false);
		}
	}
}

void DrawingBoard::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton && scribbling) {
		if (currentMode == PenMode::Eraser) {
			drawLineTo(event->pos(), true);
		}
		else {
			drawLineTo(event->pos(), false);
		}
		scribbling = false;
	}
}

void DrawingBoard::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);

	QRect dirtyRect = event->rect();

	painter.drawImage(dirtyRect, image, dirtyRect);
}

void DrawingBoard::resizeEvent(QResizeEvent* event)
{
	int newWidth = qMax(contentsRect().width() + 128, image.width());
	int newHeight = qMax(contentsRect().height() + 128, image.height());
	resizeImage(&image, QSize(newWidth, newHeight));
	update();
}

void DrawingBoard::mousePressEvent(QMouseEvent* event)
{
	lastClickPoint = event->pos();
	if (event->button() == Qt::LeftButton) {
		if (fillModeActive) {
			fillColor(event->pos(), myPenColor);
			fillModeActive = false;
		}
		else {
			lastPoint = event->pos();
			scribbling = true;
			lastPoint = event->pos();
			drawLineTo(lastPoint, currentMode == PenMode::Eraser);
		}
	}
}
void DrawingBoard::drawLineTo(const QPoint& endPoint, bool eraseMode)
{
	QPainter painter(&image);
	QColor drawColor = eraseMode ? Qt::white : myPenColor;
	painter.setPen(QPen(drawColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
		Qt::RoundJoin));

	painter.drawLine(lastPoint, endPoint);

	modified = true;

	int rad = (myPenWidth / 2) + 2;

	update(QRect(lastPoint, endPoint).normalized()
		.adjusted(-rad, -rad, +rad, +rad));

	lastPoint = endPoint;
}

void DrawingBoard::resizeImage(QImage* image, const QSize& newSize)
{
	if (image->size() == newSize)
		return;

	QImage newImage(newSize, QImage::Format_RGB32);
	newImage.fill(qRgb(255, 255, 255));

	QPainter painter(&newImage);
	painter.drawImage(QPoint(0, 0), *image);
	*image = newImage;
}