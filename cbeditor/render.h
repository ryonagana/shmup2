#ifndef RENDER_H
#define RENDER_H

#include <QWidget>
#include <QPaintEngine>
#include <QGraphicsScene>

class RenderScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit RenderScene(QWidget *parent = nullptr);




signals:

public slots:
};

#endif // RENDER_H
