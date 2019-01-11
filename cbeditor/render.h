#ifndef RENDER_H
#define RENDER_H

#include <QWidget>
#include <QPaintEngine>
#include <QGraphicsScene>
#include <QtOpenGL>
#include <QGLWidget>
#include <QOpenGLFunctions>


class RenderScene : public QGLWidget, QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit RenderScene(QWidget *parent = nullptr);

    virtual void updateGL() override;

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int width, int height) override;
    virtual void glDraw() override;



private:

protected:

signals:

public slots:


};

#endif // RENDER_H
