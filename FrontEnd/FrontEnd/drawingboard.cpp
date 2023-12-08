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
}

void DrawingBoard::setPenColor(const QColor& newColor)
{
    myPenColor = newColor;
}

void DrawingBoard::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

void DrawingBoard::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    modified = true;
    update();
}

void DrawingBoard::mouseMoveEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        scribbling = true;
    }
}

void DrawingBoard::mouseReleaseEvent(QMouseEvent* event)
{

}

void DrawingBoard::paintEvent(QPaintEvent* event)
{

}

void DrawingBoard::resizeEvent(QResizeEvent* event)
{

}

void DrawingBoard::mousePressEvent(QMouseEvent* event)
{

}

void DrawingBoard::drawLineTo(const QPoint& endPoint)
{

}

void DrawingBoard::resizeImage(QImage* image, const QSize& newSize)
{

}
