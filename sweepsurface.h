#ifndef SWEEPSURFACE_H
#define SWEEPSURFACE_H

#include <vector>
#include <QVector2D>
#include <cmath>
#include <iostream>

#include "vertex.h"
#include "vertexmatrix.h"
#include "quad.h"

using namespace std;

class SweepSurface
{
public:
    SweepSurface();

    void performBlackmagic();

    vector<QVector2D> getPreBezierPoints() const;
    vector<QVector2D> getPostBezierPoints() const;

    vector<Vertex> getVertices() const;
    vector<Quad> getQuads() const;

private:
    vector<QVector2D> preBezierPoints;
    vector<QVector2D> postBezierPoints;

    vector<Vertex> sweepVertices;
    VertexMatrix sweepMesh;

    vector<Quad> sweepQquads;

    int steps = 20;

    const float pi = 3.1415927;

    void calculateCubicBezierCurve();
    void createRotationalSweepSurface();
};

#endif // SWEEPSURFACE_H
