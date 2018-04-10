#include "vertex.h"

Vertex::Vertex(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

float Vertex::getX() const
{
    return x;
}

void Vertex::setX(float value)
{
    x = value;
}

float Vertex::getY() const
{
    return y;
}

void Vertex::setY(float value)
{
    y = value;
}

float Vertex::getZ() const
{
    return z;
}

void Vertex::setZ(float value)
{
    z = value;
}

int Vertex::getEdges() const
{
    return edges;
}

void Vertex::setEdges(int value)
{
    edges = value;
}
