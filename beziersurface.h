#ifndef BEZIERSURFACE_H
#define BEZIERSURFACE_H

#include <cmath>

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

class BezierSurface
{
public:
    BezierSurface();

    vector<Quad> getPreQuads();
    vector<Quad> getPostQuads();

    void calculateBezier();

    vector<Vertex> getPreBezierVertices() const;
    vector<Vertex> getPostBezierVertices() const;

private:
    vector<Vertex> preBezierVertices;
    vector<Vertex> postBezierVertices;

    vector<Quad> preBezierQuads;
    vector<Quad> postBezierQuads;

    int m = 3;
    int n = 3;

    VertexMatrix preBezierMat;
    VertexMatrix postBezierMat;

    int steps = 20;

    bool readSuccess = false;

    void readData();

    float bernstein(int n, int i, float s);
    float nChooseK(int n, int i);

    void determineDegree();

};

#endif // BEZIERSURFACE_H
