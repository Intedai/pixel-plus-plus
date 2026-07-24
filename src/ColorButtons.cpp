#include "ColorButtons.hpp"

ColorButtons::ColorButtons(QWidget* parent)
    : QWidget(parent),
      swap_arrow(":/ui/swap_arrows.png")
{
    setMinimumSize(45, 45);
    colors[0] = Qt::black;
    colors[1] = Qt::white;
}

void ColorButtons::setColor(int index, QColor color)
{
    Q_ASSERT(index == 0 || index == 1);

    colors[index] = color;
    update();
}

void ColorButtons::setForegroundColor(QColor color)
{
    setColor(0, color);
}

void ColorButtons::setBackgroundColor(QColor color)
{
    setColor(1, color);
}

void ColorButtons::swapColors()
{
    QColor temp = colors[0];
    colors[0] = colors[1];
    colors[1] = temp;
    update();
}

void ColorButtons::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter p(this);

    p.setPen(Qt::white);
    p.setBrush(colors[1]);
    p.drawRect(17, 17, 26, 26);

    p.setBrush(Qt::transparent);
    p.setPen(Qt::black);
    p.drawRect(0, 0, 28, 28);
    p.drawRect(16, 16, 28, 28);

    p.setPen(Qt::white);
    p.setBrush(colors[0]);
    p.drawRect(1, 1, 26, 26);

    p.drawPixmap(29,0, swap_arrow);
}

void ColorButtons::mousePressEvent(QMouseEvent *event)
{
    QPoint clickPos = event->pos();
    QRect swap = QRect(29, 0, swap_arrow.width(), swap_arrow.height());
    
    if (swap.contains(clickPos)) {
        swapColors();
    }
}