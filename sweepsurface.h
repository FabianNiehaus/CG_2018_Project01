/*
 * Datum: 14.05.2018
 * Autoren: Tuyet Nguyen, Fabian Niehaus
 */

#ifndef SWEEPSURFACE_H
#define SWEEPSURFACE_H

#include <vector>
#include <QVector2D>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>

#include "vertex.h"
#include "vertexmatrix.h"
#include "quad.h"

using namespace std;

class SweepSurface
{
public:
    SweepSurface(string filename);

    // Daten lesen, Bezier-Kurve berechnen, Rotational Sweep Surface erstellen
    void performBlackMagic();

    vector<QVector2D> getPreBezierPoints() const;
    vector<QVector2D> getPostBezierPoints() const;

    vector<Vertex> getVertices() const;
    vector<Quad> getQuads() const;

private:
    string filename;
    bool readSuccess = false;

    // Punkte der Bezier-Kurve vor und nach der Berechnung
    vector<QVector2D> preBezierPoints;
    vector<QVector2D> postBezierPoints;

    // Vertices und Quads der Oberfläche
    vector<Vertex> sweepVertices;
    VertexMatrix sweepMesh;
    vector<Quad> sweepQquads;

    // Anzahl der Schritte für Bezier
    float resolution = 20;

    const float pi = 3.1415927;

    void readData();

    void calculateCubicBezierCurve();
    void createRotationalSweepSurface();
};

#endif // SWEEPSURFACE_H
