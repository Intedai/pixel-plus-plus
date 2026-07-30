#include "ColorWheel.hpp"

ColorWheel::ColorWheel(QWidget *parent)
    : QWidget(parent)
{
}

QSize ColorWheel::sizeHint() const
{
    return QSize(RADIUS * 2, RADIUS * 2);
}

void ColorWheel::drawPointer(QPainter& p)
{
    
    float h, s, v;
    selectedColor.getHsvF(&h, &s, &v);
    
    // If didn't change color basically (will probs change this)
    if (v == 0)
    {
        p.setPen(Qt::gray);
        p.setBrush(Qt::white);
    }
    else
    {
        p.setPen(Qt::black);
        p.setBrush(selectedColor);
    }

    QLineF line = QLineF::fromPolar(RADIUS * s, 360 * (1 - h));
    line.translate(rect().center());
    p.drawEllipse(line.p2(), 4, 4);
}

void ColorWheel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QPointF center = rect().center();
    
    // The color gradient 
    QConicalGradient hsvGradient(center, 0);

    for(int deg{0}; deg < 360; deg++)
    {
        QColor color = QColor::fromHsvF((360 - 1 - deg) / 360.0, 1, 1);
        hsvGradient.setColorAt(deg / 360.0, color);
    }

    // White gradient in the center
    QRadialGradient whiteGradient(center, RADIUS);
    whiteGradient.setColorAt(0, Qt::white);
    whiteGradient.setColorAt(1, Qt::transparent);

    // Transparent border
    p.setPen(Qt::transparent);
    
    // First draw the color gradient
    p.setBrush(hsvGradient);
    p.drawEllipse(rect());

    // Draw the white radial gradient on top
    p.setBrush(whiteGradient);
    p.drawEllipse(rect());

    drawPointer(p);
}

void ColorWheel::mousePressEvent(QMouseEvent *event)
{
    float h,s;

    QPointF center = rect().center();
    QPointF clickPos = event->pos();

    QLineF line(center, clickPos);

    s = qMin(1.0, line.length() / RADIUS);
    h = fmod(1.0 - line.angle()/360.0 + 1.0, 1.0);

    selectedColor.setHsvF(h,s, VALUE);
    
    if (event->button() == Qt::RightButton)
        emit ColorSelected(1, selectedColor);
    else // Can also be the scroll wheel
        emit ColorSelected(0, selectedColor);
    update();
}