#ifndef QUAD_H
#define QUAD_H


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

private:
    //Eckpunkte
    int p1;
    int p2;
    int p3;
    int p4;

    //Nachbarn
    int a1;
    int a2;
    int a3;
    int a4;
};

#endif // QUAD_H
