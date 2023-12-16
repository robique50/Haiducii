#pragma once

#ifndef DRAWINGBOARD_H
#define DRAWINGBOARD_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <stack>

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
    void setDrawingMode(PenMode mode);
    void setModified(bool modified);
    bool isModified() const { return modified; }
    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }
    void setFillColor(const QColor& newColor);
    void setFillMode(bool active);

public slots:
    void clearImage();
    void setEraserMode();
    void toggleEraseMode();  
    void fillColor(const QPoint& point,const QColor& newColor);

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
    bool fillModeActive;
    int myPenWidth;
    PenMode currentMode;
    QColor myPenColor;
    QColor lastUsedPenColor;
    QImage image;
    QPoint lastPoint;
    QPoint lastClickPoint;
    QColor lastFillColor;
};
#endif

