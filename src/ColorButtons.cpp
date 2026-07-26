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

QSize ColorButtons::sizeHint() const
{
    return {45, 45};
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

QRect ColorButtons::fgRect() const
{
    return {1, 1, colorReqtSize, colorReqtSize};
}

QRect ColorButtons::bgRect() const
{
    int bgColorTopLeft{width() - (colorReqtSize + 1 + 2) + 1};
    return {bgColorTopLeft, bgColorTopLeft, colorReqtSize, colorReqtSize};
}

QRect ColorButtons::swapBtnRect() const
{
    return {colorReqtSize + 1 + 2, 0, swapBtnPixmap.width(), swapBtnPixmap.height()};
}

QRect ColorButtons::resetBtnRect() const
{
    int dim{width() - (colorReqtSize + 1 + 2) - 2 * 2};
    return {2, (colorReqtSize + 1 + 2) + 2, dim, dim};
}

void ColorButtons::drawColorSquare(QPainter& p, QRect rect, QColor color)
{
    // First Border
    p.setBrush(Qt::NoBrush);
    p.setPen(Qt::black);
    p.drawRect(rect.x() - 1, rect.y() - 1, colorReqtSize+2, colorReqtSize+2);

    // Second border and color square
    p.setPen(Qt::white);
    p.setBrush(color);
    p.drawRect(rect);
}

void ColorButtons::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter p(this);

    int bgColorTopLeft{width() - (colorReqtSize + 1 + 2)};
    drawColorSquare(p, bgRect(), colors[1]);
    drawColorSquare(p, fgRect(), colors[0]);

    // Reset colors button
    p.setBrush(defaultColors[0]);
    p.drawRect(2, (colorReqtSize + 1 + 2) + 2, resetSquareSize, resetSquareSize);

    int dist{(bgColorTopLeft - resetSquareSize - 1) / 2};
    p.setBrush(defaultColors[1]);
    p.drawRect(2 + dist, ((colorReqtSize + 1 + 2) + 2) + dist, resetSquareSize, resetSquareSize);
    
    // Swap colors button
    p.drawPixmap(29,0, swapBtnPixmap);
}

void ColorButtons::mousePressEvent(QMouseEvent *event)
{
    QPoint clickPos = event->pos();
    
    if (swapBtnRect().contains(clickPos))
    {
        swapColors();
    }

    if (resetBtnRect().contains(clickPos))
    {
        resetColors();
    }
}