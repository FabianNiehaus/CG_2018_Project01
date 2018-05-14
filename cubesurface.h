/*
 * Datum: 14.05.2018
 * Autoren: Tuyet Nguyen, Fabian Niehaus
 */

#ifndef CUBESURFACE_H
#define CUBESURFACE_H

#include <vector>
#include <string>

#include <iostream>
#include <iomanip>
#include <fstream>

#include "vertex.h"
#include "quad.h"

#include <cmath>

class CubeSurface
{
public:
    CubeSurface(string filename);

    // Daten einlesen, Valenzen und Nachbarn berechnen, CC-Subdivision
    void performBlackMagic(int numOfSD);

    vector<Vertex> getVertices() const;
    vector<Quad> getQuads() const;
    vector<Quad> getPreCCQuads() const;

private:
    string filename;

    vector<Vertex> vertices;
    vector<Quad> quads;

    // Quads vor der CC-Berechnung
    vector<Quad> preCCQuads;

    // Einlesen der Daten aus .obj-Files
    void readData();

    // Zeichnen eines 3D-Objekts aus Quads mit OpenGL
    void drawQuad();

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

#endif // CUBESURFACE_H
