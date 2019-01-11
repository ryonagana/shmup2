#include "render.h"

RenderScene::RenderScene(QWidget *parent) : QGLWidget(parent)
{


}


void RenderScene::initializeGL(){
    initializeOpenGLFunctions();
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glDisable(GL_DEPTH_TEST);
}

void RenderScene::glDraw(){

}

void RenderScene::resizeGL(int width, int height){

}

void RenderScene::updateGL(){

}
