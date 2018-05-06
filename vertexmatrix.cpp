#include "vertexmatrix.h"

VertexMatrix::VertexMatrix()
{

}

int VertexMatrix::at(int i, int j)
{
    return matrix.at(i).at(j);
}

void VertexMatrix::setAt(int i, int j, int v)
{
    matrix.at(i).at(j) = v;
}

void VertexMatrix::setSize(int m, int n)
{
    matrix.resize(m);
    for(unsigned int i = 0; i < matrix.size(); i++){
        matrix.at(i).resize(n);
    }
}
