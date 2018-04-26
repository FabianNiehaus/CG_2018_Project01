/*
 * Datum: 24.04.2018
 * Autoren: Tuyet Nguyen, Fabian Niehaus
 */

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

// Widget für soliden Würfel
class OGLWidget2 : public QOpenGLWidget,
                  protected QOpenGLFunctions
{
    Q_OBJECT

public:
    OGLWidget2(QWidget *parent = 0);
    ~OGLWidget2();

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
    vector<Vertex> vertices;
    vector<Quad> quads;
    bool readData();
    void drawQuad();

    int alpha = 0;

    bool readSuccess = false;
};


#endif // OGLWIDGET2_H
