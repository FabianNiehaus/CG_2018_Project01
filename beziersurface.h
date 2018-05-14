/*
 * Datum: 14.05.2018
 * Autoren: Tuyet Nguyen, Fabian Niehaus
 */

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
    BezierSurface(string filename);

    vector<Quad> getPreQuads();
    vector<Quad> getPostQuads();

    void calculateBezier();

    vector<Vertex> getPreBezierVertices() const;
    vector<Vertex> getPostBezierVertices() const;

private:
    string filename;
    bool readSuccess = false;

    vector<Vertex> preBezierVertices;
    vector<Vertex> postBezierVertices;

    vector<Quad> preBezierQuads;
    vector<Quad> postBezierQuads;

    int m = 3;
    int n = 3;

    VertexMatrix preBezierMat;
    VertexMatrix postBezierMat;

    // Anzahl der Schritte für Bezier
    int resolution = 20;

    void readData();

    float bernstein(int n, int i, float s);
    float nChooseK(int n, int i);

};

#endif // BEZIERSURFACE_H
