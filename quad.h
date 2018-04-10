#ifndef QUAD_H
#define QUAD_H

#include <vector>

using namespace std;

class Quad
{
public:
    Quad(int p1, int p2, int p3, int p4);

    int getP1() const;
    void setP1(int value);

    int getP2() const;
    void setP2(int value);

    int getP3() const;
    void setP3(int value);

    int getP4() const;
    void setP4(int value);


    int getN1() const;
    void setN1(int value);

    int getN2() const;
    void setN2(int value);

    int getN3() const;
    void setN3(int value);

    int getN4() const;
    void setN4(int value);

private:
    //Eckpunkte
    int p1;
    int p2;
    int p3;
    int p4;

    //Nachbarn
    int n1;
    int n2;
    int n3;
    int n4;
};

#endif // QUAD_H
