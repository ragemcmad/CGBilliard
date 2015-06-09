#include "myglwidget.h"
#include <QKeyEvent>
#include <QWheelEvent>
#include <QOpenGLBuffer>
#include <qdebug.h>




MyGLWidget::MyGLWidget(QWidget *parent) : QGLWidget(parent)
{
    this->isPressed = false;
    //this->sso = new SonnensystemObjekt();
    this->cam = new myCam();
    this->timer = new QTimer(parent);
    QObject::connect(this->timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(25);
}



MyGLWidget::~MyGLWidget()
{
    delete this->timer;
    //delete this->sso;

}

void MyGLWidget::update()
{
    //receiveRotationZ(counter);
    counter++;
    updateGL();
}

void MyGLWidget::wheelEvent(QWheelEvent *event)
{
//    if (event->delta()>0){
//        this->cam->zoomIn();
//    } else {
//        this->cam->zoomOut();
//    }
//    qDebug() << "scroll " <<event->delta();
}

void MyGLWidget::mousePressEvent(QMouseEvent *e){
    this->isPressed = true;
    this->mousepositionOldX = e->x();
    this->mousepositionOldY = e->y();

}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e){
    if (this->isPressed){
        this->cam->camRotate(mousepositionOldX-e->x(),mousepositionOldY-e->y());
    }

    this->mousepositionOldX = e->x();
    this->mousepositionOldY = e->y();

}

void MyGLWidget::mouseReleaseEvent(QMouseEvent *e){
    this->isPressed = false;
}

void MyGLWidget::keyPressEvent(QKeyEvent * event)
{

    if(event->key() == Qt::Key_A)
        this->cam->camMove(1,0);
    if(event->key() == Qt::Key_W)
        this->cam->camMove(0,1);
    if(event->key() == Qt::Key_S)
        this->cam->camMove(0,-1);
    if(event->key() == Qt::Key_D)
        this->cam->camMove(-1,0);


//    qDebug() << event->key();
//    if(event->key() == Qt::Key_Up)
//        this->cam->camUp();
//    else if(event->key()== Qt::Key_Down)
//        this->cam->camDown();
//    else if(event->key()== Qt::Key_Left)
//        this->cam->camLeft();
//    else if(event->key()== Qt::Key_Right)
//        this->cam->camRight();
//    else if(event->key()== 56)
//        this->cam->moveUp();
//    else if(event->key()== 50)
//        this->cam->moveDown();
//    else if(event->key()== 52)
//        this->cam->moveLeft();
//    else if(event->key()== 54)
//        this->cam->moveRight();
//    else if(event->key()== 49)
//        this->cam->moveFront();
    //else if(event->key()== 57)
        //this->cam->moveBack();

    else
        QGLWidget::keyPressEvent(event);
    updateGL();

}



void MyGLWidget::paintGL()
{
    // Clear buffer to set color and alpha
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Apply model view transformations
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glTranslatef(this->distanceX, this->distanceY, this->distanceZ);
    //glRotatef(this->rotationZ,0,1,1);

    //QMatrix4x4 m;
    //m.setToIdentity();
    //this->sso->render(m, cam, counter);
    this->scene.renderScene(cam);
}

void MyGLWidget::resizeGL(int width, int height)
{
   // Compute aspect ratio
   height = (height == 0) ? 1 : height;
   //GLfloat aspect = (GLfloat)width / (GLfloat)height;

   // Set viewport to cover the whole window
   glViewport(0, 0, width, height);

   // Set projection matrix to a perspective projection
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum(-0.05 , 0.05, -0.05, 0.05, 0.1, 100.0);
   //gluPerspective(45.0f, aspect, 0.1, 100.0);
}

void MyGLWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


    glClearDepth(1.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    this->counter = 0;
    //sso->buildSystem();
    this->scene.initScene();
    this->cam->aktivatePlaymode(QVector3D(this->scene.secondaryObjects->at(0)->worldMatrix.column(3).x(),this->scene.secondaryObjects->at(0)->worldMatrix.column(3).y(),this->scene.secondaryObjects->at(0)->worldMatrix.column(3).z()));
}
