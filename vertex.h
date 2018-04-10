#ifndef VERTEX_H
#define VERTEX_H


class Vertex
{
public:
    Vertex(float x, float y, float z);
    float getX() const;
    void setX(float value);

    float getY() const;
    void setY(float value);

    float getZ() const;
    void setZ(float value);

    int getEdges() const;
    void setEdges(int value);

private:
    float x;
    float y;
    float z;

    int edges;
};

#endif // VERTEX_H
