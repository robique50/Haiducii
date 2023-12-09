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
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);

    modified = false;
    scribbling = false;
    myPenWidth = 1;
    myPenColor = Qt::blue;
    originalPenColor = myPenColor;
}

void DrawingBoard::setPenColor(const QColor& newColor)
{
    myPenColor = newColor;
}

void DrawingBoard::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

void DrawingBoard::setDrawMode(DrawMode mode)
{
    currentDrawMode = mode;

    if (mode == Eraser) {
        originalPenColor = myPenColor;
        myPenColor = Qt::white;
        setPenColor(myPenColor);
    }
    else {
        restoreOriginalColor();
    }
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

void DrawingBoard::mouseMoveEvent(QMouseEvent* event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling)
    {
        if (currentDrawMode == Eraser) {
            drawLineTo(event->pos(),true);
    }
        else {
            drawLineTo(event->pos(),false);
}
    }
}

void DrawingBoard::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        if (currentDrawMode == Eraser) {
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
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);

}

void DrawingBoard::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        scribbling = true;
    }

    if (currentDrawMode == Eraser) {
        myPenColor = Qt::white;
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
