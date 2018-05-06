#ifndef VERTEXMATRIX_H
#define VERTEXMATRIX_H

#include <vector>

#include "vertex.h"

using namespace std;

class VertexMatrix
{
public:
    VertexMatrix();

    int at(int i, int j);
    void setAt(int i, int j, int v);

    void setSize(int m, int n);

private:
    vector<vector<int>> matrix;
};

#endif // VERTEXMATRIX_H
