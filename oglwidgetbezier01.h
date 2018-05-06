#ifndef OGLWIDGETBEZIER01_H
#define OGLWIDGETBEZIER01_H


#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>
#include <QVector3D>

#include <vector>
#include <string>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "vertex.h"
#include "quad.h"
#include "vertexmatrix.h"

using namespace std;


class OGLWidgetBezier01 : public QOpenGLWidget,
                  protected QOpenGLFunctions
{
    Q_OBJECT

public:
    OGLWidgetBezier01(QWidget *parent = 0);
    ~OGLWidgetBezier01();

public slots:
    void stepAnimation();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void SetMaterialColor( int side, float r, float g, float b);
    void InitLightingAndProjection();

    QTimer* animtimer; // Timer needed to step animation every x msec
    int animstep;      // Current animation step (used to rotate triangle

private:
    vector<Vertex> preBezierVertices;
    vector<Vertex> postBezierVertices;

    vector<Quad> preBezierQuads;
    vector<Quad> postBezierQuads;

    bool readData();

    void drawLines();
    void drawQuad();

    void calculateBezier();
    float bernstein(int n, int i, float s);
    float choose(int n, int i);
    int fact(int n);

    int m = 3;
    int n = 3;

    VertexMatrix inputMat;
    VertexMatrix postBezierMat;

    int steps = 20;

    bool readSuccess = false;

    bool rotating = true;
    bool rotation = true;

    int alpha = 0;
};


#endif // OGLWIDGETBEZIER01_H
