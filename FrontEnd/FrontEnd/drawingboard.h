#pragma once

#ifndef DRAWINGBOARD_H
#define DRAWINGBOARD_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>

class DrawingBoard :public QWidget
{
	Q_OBJECT

public:
	DrawingBoard(QWidget* parent=0);
    void setPenColor(const QColor& newColor);
    void setPenWidth(int newWidth);

    bool isModified() const { return modified; }
    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }
    void clearImage();

public slots:
    //

protected:
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    void drawLineTo(const QPoint& endPoint);
    void resizeImage(QImage* image, const QSize& newSize);
    bool modified;
    bool scribbling;
    int myPenWidth;
    QColor myPenColor;
    QImage image;
    QPoint lastPoint;
};
#endif

