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
    vector<Vertex> vertices;
    vector<Quad> quads;
    bool readData();
    void drawQuad();

    int alpha = 0;

    bool readSuccess = false;

    void calculateVertexValence();
    void determineQuadNeighbours();

    void ccSubdivision();

    void printToFile();

    void calculateFaceMasks();
    void calculateEdgeMasks();
    void calculateVertexMasks();
    void subdivideAndReconnectMesh();
    void printQuads(bool postCC);

};


#endif // OGLWIDGET_H
