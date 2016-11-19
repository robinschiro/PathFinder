#include "inc/RenderLayer.h"

RenderLayer::RenderLayer()
{
   penWidth = 1;
   penStyle = Qt::SolidLine;
}

void RenderLayer::setFillRule(Qt::FillRule rule)
{
    path.setFillRule(rule);
}

void RenderLayer::setFillGradient(const QColor &color1, const QColor &color2)
{
    fillColor1 = color1;
    fillColor2 = color2;
}

void RenderLayer::setPenWidth(int width)
{
    penWidth = width;
}

void RenderLayer::setPenColor(const QColor &color)
{
    penColor = color;
}
