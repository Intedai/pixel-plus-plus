#pragma once

#include <QWidget>
#include <QPainter>
#include <QSize>
#include <QPointF>
#include <QColor>
#include <QMouseEvent>
#include <QLineF>
#include <QConicalGradient>
#include <QRadialGradient>
#include <QtMath>

class ColorWheel : public QWidget
{
    Q_OBJECT

public:
    ColorWheel(QWidget* parent = nullptr);
    QSize sizeHint() const override;
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
private:
    static constexpr double RADIUS {130 / 2.0};
    static constexpr double VALUE {1};
    void drawPointer(QPainter& p);
    QColor selectedColor;
signals:
    void ColorSelected(int index, const QColor& color);
};