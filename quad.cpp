#include "quad.h"

Quad::Quad(int p1, int p2, int p3, int p4)
{
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->p4 = p4;
}

int Quad::getP1() const
{
    return p1;
}

void Quad::setP1(int value)
{
    p1 = value;
}

int Quad::getP2() const
{
    return p2;
}

void Quad::setP2(int value)
{
    p2 = value;
}

int Quad::getP3() const
{
    return p3;
}

void Quad::setP3(int value)
{
    p3 = value;
}

int Quad::getP4() const
{
    return p4;
}

void Quad::setP4(int value)
{
    p4 = value;
}

int Quad::getN1() const
{
    return n1;
}

void Quad::setN1(int value)
{
    n1 = value;
}

int Quad::getN2() const
{
    return n2;
}

void Quad::setN2(int value)
{
    n2 = value;
}

int Quad::getN3() const
{
    return n3;
}

void Quad::setN3(int value)
{
    n3 = value;
}

int Quad::getN4() const
{
    return n4;
}

void Quad::setN4(int value)
{
    n4 = value;
}

