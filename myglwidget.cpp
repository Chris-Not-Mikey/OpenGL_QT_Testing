// Include GLEW
#include <GL/glew.h>
#include <OpenGL/gl3.h>

// Include GLFW
//#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>


// myglwidget.cpp

#include <QtWidgets>
//#include <QtOpenGL>
#include <stdio.h>
#include "myglwidget.h"


glm::mat4 MVP_grid, MVP_probe, Model_probe, Model_grid, Projection, View;

int read_stl(std::string fname, GLfloat * &vertices, GLfloat * &colors);

MyGLWidget::MyGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;
}

MyGLWidget::~MyGLWidget()
{
}

QSize MyGLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize MyGLWidget::sizeHint() const
{
    return QSize(400, 400);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

void MyGLWidget::setXRotation(int angle)
{
    //qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = 16*angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setYRotation(int angle)
{
    //qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = 16*angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setZRotation(int angle)
{
    //qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = 16*angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::initializeGL()
{
    glewInit();
    GLuint myBufferID;

    GLfloat verts[]{
        +0.0f, +1.0f,
        -1.0f, -1.0f,
        +1.0f, -1.0f,
    };

    __glewGenBuffers(1, &myBufferID);
    __glewBindBuffer(GL_ARRAY_BUFFER, myBufferID);
    __glewBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    __glewEnableVertexAttribArray(0);
    __glewVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    //qglClearColor(Qt::black);

    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glShadeModel(GL_SMOOTH);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);

    //static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
    //glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void MyGLWidget::paintGL()
{

   glViewport(0,0, width(), height());
   glDrawArrays(GL_TRIANGLES, 0, 3);

}

void MyGLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-2, +2, -2, +2, 1.0, 15.0);
#else
    glOrtho(-2, +2, -2, +2, 1.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}

void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 20 * dy);
        setYRotation(yRot + 20 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 20 * dy);
        setZRotation(zRot + 20 * dx);
    }

    lastPos = event->pos();
}

void MyGLWidget::draw()
{

}
    
    
