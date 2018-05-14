/*
 * Datum: 14.05.2018
 * Autoren: Tuyet Nguyen, Fabian Niehaus
 */

#ifndef OGLSCENEWIDGET_H
#define OGLSCENEWIDGET_H


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
#include "cubesurface.h"
#include "beziersurface.h"
#include "sweepsurface.h"

using namespace std;


class OGLSceneWidget : public QOpenGLWidget,
                  protected QOpenGLFunctions
{
    Q_OBJECT

public:
    OGLSceneWidget(QWidget *parent = 0);
    ~OGLSceneWidget();

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
    // Würfel
    CubeSurface * cSurf1;
    CubeSurface * cSurf2;

    // Threeholes
    CubeSurface * tSurf1;
    CubeSurface * tSurf2;

    // Zahnräder
    CubeSurface * gSurf1;
    CubeSurface * gSurf2;
    CubeSurface * gSurf3;
    CubeSurface * gSurf4;

    // Bezier-Oberflächen
    BezierSurface * bSurf1;
    BezierSurface * bSurf2;

    // Berzier-Kurven bzw. Rotational Sweep Surfaces
    SweepSurface * sSurf1;
    SweepSurface * sSurf2;

    void drawLines(vector<Quad> quads, vector<Vertex> vertices);
    void drawQuad(vector<Quad> quads, vector<Vertex> vertices);
    void drawQuadrantSeparators();

    // Objekt sollen sich kontinuierlich drehen
    bool rotating = true;

    // Objekte sollen anfangs einmal rotiert werden
    bool rotation = true;

    // Rotationswinkel
    int alpha = 0;
};

#endif // OGLSCENEWIDGET_H
