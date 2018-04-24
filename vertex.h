/*
 * Datum: 24.04.2018
 * Autoren: Tuyet Nguyen, Fabian Niehaus
 */

#ifndef VERTEX_H
#define VERTEX_H

#include <string>

using namespace std;

class Vertex
{
public:
    Vertex(float x, float y, float z, string type);
    Vertex(float x, float y, float z, int valence, string type);

    float getX() const;
    void setX(float value);

    float getY() const;
    void setY(float value);

    float getZ() const;
    void setZ(float value);

    int getValence() const;
    void setValence(int value);

    static bool compareVertices(Vertex  v1, Vertex  v2);

    string toString();

    static Vertex  addVertices(Vertex  v1, Vertex  v2);
    static Vertex  subtractVertices(Vertex  v1, Vertex  v2);
    static Vertex  multiplyVertex(Vertex  v, float m);
    static Vertex  divideVertex(Vertex  v, float d);

    static Vertex  averageVertices(Vertex  v1, Vertex  v2);
    static Vertex  averageVertices(Vertex  v1, Vertex  v2, Vertex  v3);
    static Vertex  averageVertices(Vertex  v1, Vertex  v2, Vertex  v3, Vertex v4);

    string getType() const;
    void setType(const string &value);

private:
    // Vektor-Koordinaten
    float x;
    float y;
    float z;

    // Valenz
    int n;

    // Typ
    string type;
};

#endif // VERTEX_H
