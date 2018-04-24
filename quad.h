/*
 * Datum: 24.04.2018
 * Autoren: Tuyet Nguyen, Fabian Niehaus
 */

#ifndef QUAD_H
#define QUAD_H

#include <vector>
#include <string>

using namespace std;

class Quad
{
public:
    Quad(int v0, int v1, int v2, int v3);

    int getV(int index) const;
    void setV(int index, int value);

    int getQ(int index) const;
    void setQ(int index, int value);

    int getE(int index) const;
    void setE(int index, int value);

    int getF() const;
    void setF(int value);

    int findNeighbour(int index);

    string toString();

private:
    //Eckpunkt-Indizes
    int v[4];

    //Nachbar-Indizes
    int q[4];

    //Kantenpunkt-Indizes
    int e[4];

    //Facepunkt-Index
    int f;

};

#endif // QUAD_H
