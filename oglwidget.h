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

    // Einlesen der Daten aus .obj-Files
    bool readData();

    // Zeichnen eines 3D-Objekts aus Quads mit OpenGL
    void drawQuad();

    // Ursprünglicher Rotationswinkel
    int alpha = 0;

    // Wurde die .obj-Datei richtig eingelesen?
    bool readSuccess = false;

    // Bestimmung der Vertex-Valenzen
    void calculateVertexValence();

    // Bestimmung der Quad-Nachbarn
    void determineQuadNeighbours();

    // Catmull-Clark-Subdivision Sammelmethode
    void ccSubdivision();

    // Berechnung der Face-Masks
    void calculateFaceMasks();
    // Berechnung der Edge-Masks
    void calculateEdgeMasks();
    // Berechnung der Vertex-Masks
    void calculateVertexMasks();
    // Subdivision und Neuberechnung der Nachbarn und Valenzen
    void subdivideAndReconnectMesh();
    // Alle Quads ausgeben (postCC = mit Face- und Edge-Vertices)
    void printQuads(bool postCC);

    // Speichern der Vertices und Quads in einer Datei
    void printToFile();

};


#endif // OGLWIDGET_H
