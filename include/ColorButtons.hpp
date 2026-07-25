#pragma once

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QColor>
#include <QPixmap>
#include <QPoint>
#include <QMouseEvent>

/*
TODO:
Avoid magic numbers and create constant rectangles instead of the one in mouse event and more...
*/

class ColorButtons : public QWidget
{
    Q_OBJECT
public:
    ColorButtons(QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
public slots:
    void setColor(int index, QColor color);
    void setForegroundColor(QColor color);
    void setBackgroundColor(QColor color);
private:
    void swapColors();
    void resetColors();
    QPixmap swapBtnPixmap;
    QColor colors[2];
    QColor defaultColors[2];
};