/*
 * Datum: 24.04.2018
 * Autoren: Tuyet Nguyen, Fabian Niehaus
 */

#ifndef OGLWIDGET_H
#define OGLWIDGET_H

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

#include <cmath>

using namespace std;

//Widget mit Subdivision
class OGLWidget : public QOpenGLWidget,
                  protected QOpenGLFunctions
{
    Q_OBJECT

public:
    OGLWidget(QWidget *parent = 0);
    ~OGLWidget();

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

    // Ursprünglicher Rotationswinkel
    int alpha = 0;

    void drawQuad();
};


#endif // OGLWIDGET_H
