#include "ColorButtons.hpp"

ColorButtons::ColorButtons(QWidget* parent)
    : QWidget(parent),
      swapBtnPixmap(":/ui/swap_arrows.png")
{
    setMinimumSize(45, 45);
    defaultColors[0] = Qt::black;
    defaultColors[1] = Qt::white;

    colors[0] = defaultColors[0];
    colors[1] = defaultColors[1];
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

void ColorButtons::resetColors()
{
    colors[0] = defaultColors[0];
    colors[1] = defaultColors[1];
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
    
    // Reset colors button
    p.setBrush(defaultColors[0]);
    p.drawRect(2, 31, 7, 7);
    p.setBrush(defaultColors[1]);
    p.drawRect(6, 35, 7, 7);
    
    // Swap colors button
    p.drawPixmap(29,0, swapBtnPixmap);
}

void ColorButtons::mousePressEvent(QMouseEvent *event)
{
    QPoint clickPos = event->pos();
    QRect swap = QRect(29, 0, swapBtnPixmap.width(), swapBtnPixmap.height());
    
    if (swap.contains(clickPos))
    {
        swapColors();
    }

    QRect reset = QRect(2,31, 12, 12);

    if (reset.contains(clickPos))
    {
        resetColors();
    }
}