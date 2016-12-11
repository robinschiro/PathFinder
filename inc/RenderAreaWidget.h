#ifndef RENDERAREAWIDGET_H
#define RENDERAREAWIDGET_H

#include <QWidget>
#include <RenderArea.h>

class RenderAreaWidget : public QWidget
{
    Q_OBJECT

public:
   explicit RenderAreaWidget(RenderArea* area, QWidget* parent = 0);

   QSize minimumSizeHint() const Q_DECL_OVERRIDE;
   QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

private:
   RenderArea* renderArea;
};

#endif // RENDERAREAWIDGET_H
