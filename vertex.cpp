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

bool Vertex::compareVertices(Vertex *v1, Vertex *v2)
{
    if(v1->getX() == v2->getX()){
        if(v1->getY() == v2->getY()){
            if(v1->getZ() == v2->getZ()){
                return true;
            }
        }
    }
    return false;
}
