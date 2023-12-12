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
    : QWidget(parent),
    modified(false),
    scribbling(false),
    myPenWidth(5),
    myPenColor(Qt::blue),
    eraserMode(false),
    currentMode(PenMode::Pen),
    originalPenColor(myPenColor)
{
    setAttribute(Qt::WA_StaticContents);

    modified = false;
    scribbling = false;
    myPenWidth = 1;
    myPenColor = QColor(255,0,0);
    originalPenColor = myPenColor;
}

void DrawingBoard::setPenColor(const QColor& newColor)
{
    myPenColor = newColor;
}

void DrawingBoard::setPenWidth(int newWidth)
{
    myPenWidth = qBound(1, newWidth, 50);
}

void DrawingBoard::setOriginalColor(const QColor& newColor)
{
	originalPenColor = newColor;
}

void DrawingBoard::setDrawingMode(PenMode mode)
{
    currentMode = mode;

    if (currentMode == PenMode::Eraser) {
        setPenColor(QColor(255, 255, 255)); 
        setPenWidth(myPenWidth);
    }
    else {
        setPenColor(originalPenColor);
    }

}

void DrawingBoard::setModified(bool modified)
{
	this->modified = modified;
}

void DrawingBoard::restoreOriginalColor()
{
    myPenColor = originalPenColor;
    setPenColor(myPenColor);
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
        myPenColor = Qt::white;
        setPenWidth(myPenWidth);
    }
    else {
        myPenColor = originalPenColor;
    }
}

void DrawingBoard::toggleEraseMode()
{
    setDrawingMode(currentMode == PenMode::Pen ? PenMode::Eraser : PenMode::Pen);
}

void DrawingBoard::mouseMoveEvent(QMouseEvent* event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling)
    {
        if (currentMode == PenMode::Eraser) {
            drawLineTo(event->pos(),true);
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
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        scribbling = true;
        lastPoint = event->pos();
        drawLineTo(lastPoint, currentMode == PenMode::Eraser);
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
