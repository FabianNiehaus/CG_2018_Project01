#include "quad.h"

Quad::Quad(int v0, int v1, int v2, int v3)
{
    v[0] = v0;
    v[1] = v1;
    v[2] = v2;
    v[3] = v3;
}

int Quad::getV(int index) const
{
    if(index > -1 && index < 4) return v[index];
    else return -1;
}

void Quad::setV(int index, int value)
{
    if(index > -1 && index < 4) v[index] = value;
}

int Quad::getQ(int index) const
{
    if(index > -1 && index < 4) return q[index];
    else return -1;
}

void Quad::setQ(int index, int value)
{
    if(index > -1 && index < 4) q[index] = value;
}

int Quad::getE(int index) const
{
    if(index > -1 && index < 4) return e[index];
    else return -1;
}

void Quad::setE(int index, int value)
{
    if(index > -1 && index < 4) e[index] = value;
}

int Quad::getF() const
{
    return f;
}

void Quad::setF(int value)
{
    f = value;
}

string Quad::toString()
{
    return "Eckpunkte: " + to_string(v[0]) + "|" + to_string(v[1]) + "|" + to_string(v[2]) + "|" + to_string(v[3]) + "|"
            + " # Nachbarn: " + to_string(q[0]) + "|" + to_string(q[1]) + "|" + to_string(q[2]) + "|" + to_string(q[3]);
}


