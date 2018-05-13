#include "sweepsurface.h"

SweepSurface::SweepSurface(string filename)
{
    //preBezierPoints.push_back(QVector2D(0,0));
    //preBezierPoints.push_back(QVector2D(3,2));
    //preBezierPoints.push_back(QVector2D(4,-1));
    //preBezierPoints.push_back(QVector2D(7,1));

    this->filename = filename;
}

void SweepSurface::readData()
{

    ifstream file(filename.c_str());

    if(!file){
        cout << "error opening file" << endl;
    } else {

        float x,y;

        while(file){
            if(file.eof()) break;
            file >> x >> y;
            preBezierPoints.push_back( QVector2D(x,y));
        }

        file.close();

        cout << endl;
        cout << "[Sweep] Objekt-Datei eingelesen!" << endl;

        readSuccess = true;
    }
}

void SweepSurface::performBlackMagic()
{
    readData();
    if(readSuccess){
        calculateCubicBezierCurve();
        createRotationalSweepSurface();
    }
}

void SweepSurface::calculateCubicBezierCurve()
{
    for(float t = 0.0; t <= 1.0 * resolution; t++){

        QVector2D p1 = preBezierPoints.at(0);
        QVector2D p2 = preBezierPoints.at(1);
        QVector2D p3 = preBezierPoints.at(2);
        QVector2D p4 = preBezierPoints.at(3);

        float tr = t / resolution;

        QVector2D pT = pow(1-tr,3) * p1
                + 3 * tr * pow(1-tr,2) * p2
                + 3 * pow(tr,2) * (1-tr) * p3
                + pow(tr,3) * p4;

        postBezierPoints.push_back(pT);

        cout << pT.x() << "|" << pT.y() << endl;
    }
}

void SweepSurface::createRotationalSweepSurface()
{
    int counter = 0;

    sweepMesh.setSize(resolution + 1, resolution + 1);

    for(float s = -1.0 * resolution; s <= 1.0 * resolution; s += 2){
        for(unsigned int i = 0; i < postBezierPoints.size(); i++){

            QVector2D v2D = postBezierPoints.at(i);

            Vertex v = Vertex(v2D.x(), v2D.y() * sin(s / resolution * pi), v2D.y() * cos(s / resolution * pi), "v");

            sweepVertices.push_back(v);
            sweepMesh.setAt(counter, i, sweepVertices.size()-1);
        }
        counter++;
    }

    for(int i = 0; i < resolution; i++){
        for(int j = 0; j < resolution; j++){

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
