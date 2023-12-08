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
}

void DrawingBoard::setPenWidth(int newWidth)
{

}

void DrawingBoard::clearImage()
{

}

void DrawingBoard::mouseMoveEvent(QMouseEvent* event)
{
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
