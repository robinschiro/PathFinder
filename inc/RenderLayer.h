#ifndef RENDERLAYER_H
#define RENDERLAYER_H

#include <QPainterPath>
#include <QColor>

class RenderLayer
{
public:
   RenderLayer();
   QPainterPath path;
   QColor fillColor1;
   QColor fillColor2;
   int penWidth;
   QColor penColor;
   Qt::PenStyle penStyle;

public:
    void setFillRule(Qt::FillRule rule);
    void setFillGradient(const QColor &color1, const QColor &color2);
    void setPenWidth(int canvasWidth);
    void setPenColor(const QColor &color);

    void ConcatenateLayerPath(RenderLayer& layer);

private:

};

#endif // RENDERLAYER_H
