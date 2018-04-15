#ifndef OGLWIDGET2_H
#define OGLWIDGET2_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>
#include <QVector3D>

#include <vector>
#include <string>

#include <iostream>
#include <iomanip>
#include <fstream>

#include "vertex.h"
#include "quad.h"

using namespace std;


class OGLWidget2 : public QOpenGLWidget,
                  protected QOpenGLFunctions
{
    Q_OBJECT

public:
    OGLWidget2(QWidget *parent = 0);
    ~OGLWidget2();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    vector<Vertex> vertices;
    vector<Quad> quads;
    bool readData();
    void drawQuad();

    bool readSuccess = false;
};


#endif // OGLWIDGET2_H
