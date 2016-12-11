#include "RenderAreaWidget.h"

RenderAreaWidget::RenderAreaWidget(RenderArea* area, QWidget* parent) :
   QWidget(parent),
   renderArea(area)
{
   setBackgroundRole(QPalette::Base);
}

QSize RenderAreaWidget::minimumSizeHint() const
{
    return QSize(renderArea->canvasWidth + 2*renderArea->offset,
                 renderArea->canvasHeight + 2*renderArea->offset);
}

QSize RenderAreaWidget::sizeHint() const
{
    return minimumSizeHint();
}

void RenderAreaWidget::paintEvent(QPaintEvent *)
{
   QPainter painter(this);
   renderArea->paintLayers(painter);
}
