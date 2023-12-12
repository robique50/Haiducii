#pragma once

#ifndef DRAWINGBOARD_H
#define DRAWINGBOARD_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>

enum class PenMode
{
	Pen,
	Eraser
};

class DrawingBoard :public QWidget
{
	Q_OBJECT

public:
	DrawingBoard(QWidget* parent=0);
    void setPenColor(const QColor& newColor);
    void setPenWidth(int newWidth);
    void setOriginalColor(const QColor& newColor);
    void setDrawingMode(PenMode mode);
    void setModified(bool modified);
    void restoreOriginalColor();
    bool isModified() const { return modified; }
    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }

public slots:
    void clearImage();
    void setEraserMode();
    void toggleEraseMode();  

protected:
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    void drawLineTo(const QPoint& endPoint, bool eraseMode);
    void resizeImage(QImage* image, const QSize& newSize);
    bool modified;
    bool scribbling;
    bool eraserMode;
    int myPenWidth;
    PenMode currentMode;
    QColor myPenColor;
    QColor originalPenColor;
    QImage image;
    QPoint lastPoint;
};
#endif

