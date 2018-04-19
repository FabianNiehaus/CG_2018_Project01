#include "vertex.h"

Vertex::Vertex(float x, float y, float z, string type)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->type = type;
}

Vertex::Vertex(float x, float y, float z, int valence, string type)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->n = valence;
    this->type = type;
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

int Vertex::getValence() const
{
    return n;
}

void Vertex::setValence(int value)
{
    n = value;
}

bool Vertex::compareVertices(Vertex v1, Vertex v2)
{
    if(v1.getX() == v2.getX()){
        if(v1.getY() == v2.getY()){
            if(v1.getZ() == v2.getZ()){
                return true;
            }
        }
    }
    return false;
}

string Vertex::toString()
{
    return "XYZT: " + to_string(x) + "|" + to_string(y) + "|" + to_string(z) + "|" + type;
}

Vertex Vertex::addVertices(Vertex v1, Vertex v2)
{
    return  Vertex(v1.getX() + v2.getX(), v1.getY() + v2.getY(), v1.getZ() + v2.getZ(), v1.getValence(), v1.getType());
}

Vertex Vertex::subtractVertices(Vertex v1, Vertex v2)
{
    return  Vertex(v1.getX() - v2.getX(), v1.getY() - v2.getY(), v1.getZ() - v2.getZ(), v1.getValence(), v1.getType());
}

Vertex Vertex::multiplyVertex(Vertex v, float m)
{
    return  Vertex(v.getX() * m, v.getY() * m, v.getZ() * m, v.getValence(), v.getType());
}

Vertex Vertex::divideVertex(Vertex v, float d)
{
    return  Vertex(v.getX() / d, v.getY() / d, v.getZ() / d, v.getValence(), v.getType());
}

Vertex Vertex::averageVertices(Vertex v1, Vertex v2)
{
    Vertex  v_temp =  Vertex(v1.getX() + v2.getX(), v1.getY() + v2.getY(), v1.getZ() + v2.getZ(), v1.getType());
    return  Vertex (v_temp.getX() / 2, v_temp.getY() / 2, v_temp.getZ() / 2, v1.getValence(), v1.getType());
}

Vertex Vertex::averageVertices(Vertex v1, Vertex v2, Vertex v3)
{
    Vertex  v_temp =  Vertex(v1.getX() + v2.getX() + v3.getX(), v1.getY() + v2.getY() + v3.getY(), v1.getZ() + v2.getZ() + v3.getZ(), v1.getType());
    return  Vertex (v_temp.getX() / 3, v_temp.getY() / 3, v_temp.getZ() / 3, v1.getValence(), v1.getType());
}

Vertex Vertex::averageVertices(Vertex v1, Vertex v2, Vertex v3, Vertex v4)
{
    Vertex  v_temp =  Vertex(v1.getX() + v2.getX() + v3.getX() + v4.getX(), v1.getY() + v2.getY() + v3.getY() + v4.getY(), v1.getZ() + v2.getZ() + v3.getZ() + v4.getZ(), v1.getType());
    return  Vertex (v_temp.getX() / 4, v_temp.getY() / 4, v_temp.getZ() / 4, v1.getValence(), v1.getType());
}

string Vertex::getType() const
{
    return type;
}

void Vertex::setType(const string &value)
{
    type = value;
}
