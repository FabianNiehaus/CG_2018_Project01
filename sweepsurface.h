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

    void readData();

    void performBlackMagic();

    vector<QVector2D> getPreBezierPoints() const;
    vector<QVector2D> getPostBezierPoints() const;

    vector<Vertex> getVertices() const;
    vector<Quad> getQuads() const;

private:
    string filename;
    bool readSuccess = false;

    vector<QVector2D> preBezierPoints;
    vector<QVector2D> postBezierPoints;

    vector<Vertex> sweepVertices;
    VertexMatrix sweepMesh;

    vector<Quad> sweepQquads;

    float resolution = 20;

    const float pi = 3.1415927;

    void calculateCubicBezierCurve();
    void createRotationalSweepSurface();
};

#endif // SWEEPSURFACE_H
