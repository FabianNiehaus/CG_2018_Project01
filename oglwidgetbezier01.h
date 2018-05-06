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
#include "beziersurface.h"
#include "sweepsurface.h"

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
    BezierSurface bSurf;
    SweepSurface sSurf;

    void drawLines(vector<Quad> quads, vector<Vertex> vertices);
    void drawQuad(vector<Quad> quads, vector<Vertex> vertices);
    void drawLine(vector<QVector2D> points);

    bool rotating = true;
    bool rotation = true;

    int alpha = 0;
};


#endif // OGLWIDGETBEZIER01_H
