#pragma once

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QColor>
#include <QPixmap>
#include <QPoint>
#include <QMouseEvent>

class ColorButtons : public QWidget
{
    Q_OBJECT
public:
    ColorButtons(QWidget* parent = nullptr);
    QSize sizeHint() const;
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    
    void swapColors();
    void resetColors();
    void drawColorSquare(QPainter& p, QRect rect, QColor color);

    static constexpr int colorReqtSize{26};
    static constexpr int resetSquareSize{7};
    QRect fgRect() const;
    QRect bgRect() const;
    QRect swapBtnRect() const;
    QRect resetBtnRect() const;

    QPixmap swapBtnPixmap;
    QColor colors[2];
    QColor defaultColors[2];

public slots:
    void setColor(int index, QColor color);
    void setForegroundColor(QColor color);
    void setBackgroundColor(QColor color);
};