#include "sweepsurface.h"

SweepSurface::SweepSurface()
{
    preBezierPoints.push_back(QVector2D(0,0));
    preBezierPoints.push_back(QVector2D(3,2));
    preBezierPoints.push_back(QVector2D(4,-1));
    preBezierPoints.push_back(QVector2D(7,1));
}

void SweepSurface::performBlackmagic()
{
    calculateCubicBezierCurve();
    createRotationalSweepSurface();
}

void SweepSurface::calculateCubicBezierCurve()
{
    for(float t = 0.0; t <= 1.0 + (1.0 / steps); t += (1.0 / steps)){

        QVector2D p1 = preBezierPoints.at(0);
        QVector2D p2 = preBezierPoints.at(1);
        QVector2D p3 = preBezierPoints.at(2);
        QVector2D p4 = preBezierPoints.at(3);

        QVector2D pT = pow(1-t,3) * p1
                + 3 * t * pow(1-t,2) * p2
                + 3 * pow(t,2) * (1-t) * p3
                + pow(t,3) * p4;

        postBezierPoints.push_back(pT);

        cout << pT.x() << "|" << pT.y() << endl;
    }
}

void SweepSurface::createRotationalSweepSurface()
{
    int counter = 0;

    sweepMesh.setSize(steps+1, steps+1);

    for(float s = -1.0; s <= 1.1; s += 2.0 / steps){
        for(int i = 0; i < postBezierPoints.size(); i++){

            QVector2D v2D = postBezierPoints.at(i);

            Vertex v = Vertex(v2D.x(), v2D.y() * sin(s*pi), v2D.y() * cos(s*pi), "v");

            sweepVertices.push_back(v);
            sweepMesh.setAt(counter, i, sweepVertices.size()-1);
        }
        counter++;
    }

    for(int i = 0; i < steps; i++){
        for(int j = 0; j < steps; j++){

            sweepQquads.push_back(
                        Quad(
                            sweepMesh.at(i,j),
                            sweepMesh.at(i,j+1),
                            sweepMesh.at(i+1,j+1),
                            sweepMesh.at(i+1,j)
                            ));
        }
    }
}

vector<QVector2D> SweepSurface::getPreBezierPoints() const
{
    return preBezierPoints;
}

vector<QVector2D> SweepSurface::getPostBezierPoints() const
{
    return postBezierPoints;
}

vector<Vertex> SweepSurface::getVertices() const
{
    return sweepVertices;
}

vector<Quad> SweepSurface::getQuads() const
{
    return sweepQquads;
}
