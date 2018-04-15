#include "vertex.h"

Vertex::Vertex(float x, float y, float z, string type)
{
    this->x = x;
    this->y = y;
    this->z = z;
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

string Vertex::toString()
{
    string s = "";

    s = "XYZT: " + to_string(x) + "|" + to_string(y) + "|" + to_string(z) + "|" + type;

    return s;
}

Vertex *Vertex::addVertices(Vertex *v1, Vertex *v2)
{
    return new Vertex(v1->getX() + v2->getX(), v1->getY() + v2->getY(), v1->getZ() + v2->getZ(), v1->getType());
}

Vertex *Vertex::subtractVertices(Vertex *v1, Vertex *v2)
{
    return new Vertex(v1->getX() - v2->getX(), v1->getY() - v2->getY(), v1->getZ() - v2->getZ(), v1->getType());
}

Vertex *Vertex::multiplyVertex(Vertex *v, float m)
{
    return new Vertex(v->getX() * m, v->getY() * m, v->getZ() * m, v->getType());
}

Vertex *Vertex::divideVertex(Vertex *v, float d)
{
    return new Vertex(v->getX() / d, v->getY() / d, v->getZ() / d, v->getType());
}

string Vertex::getType() const
{
    return type;
}

void Vertex::setType(const string &value)
{
    type = value;
}
