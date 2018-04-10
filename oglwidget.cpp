#include "oglwidget.h"

bool OGLWidget::readData()
{
    ifstream file("cubeobj.sec");

    if(!file){
        cout << "error opening file" << endl;
        return false;
    }

    string key;
    float x,y,z;
    int p1,p2,p3,p4;

    while(file){
        file >> key;

        if(key == "v"){
            file >> x >> y >> z;
            vertices.push_back(Vertex(x,y,z));
        }

        if(key == "f"){
            file >> p1 >> p2 >> p3 >> p4;
            if( file.eof() ) break;
            quads.push_back(Quad(p1-1, p2-1, p3-1, p4-1));
        }
    }

    file.close();

    cout << "Objekt-Datei eingelesen!" << endl;
    return true;
}

void OGLWidget::drawQuad() // drawing a quad in OpenGL
{
    if(readSuccess){

        cout << "Zeichne Quads" << endl;

        for(unsigned int i=0; i<quads.size();i++){
            Quad q = quads.at(i);

            Vertex v1 = vertices.at(q.getP1());
            Vertex v2 = vertices.at(q.getP2());
            Vertex v3 = vertices.at(q.getP3());
            Vertex v4 = vertices.at(q.getP4());

            glBegin(GL_QUADS); // each 4 points define a polygon
                //float colorScale = (((float)i+1.0f) / (float)quads.size());
                //glColor3f(1.0 * colorScale, 1.0 * colorScale, 1.0 * colorScale);

                glNormal3f(v2.getX() * 0.5 - v1.getX() * 0.5, v2.getY() * 0.5 - v1.getY() * 0.5, v2.getZ() * 0.5 - v1.getZ() * 0.5);
                glVertex3d(v1.getX() * 0.5, v1.getY() * 0.5, v1.getZ() * 0.5);
                glVertex3d(v2.getX() * 0.5, v2.getY() * 0.5, v2.getZ() * 0.5);

                glNormal3f(v4.getX() * 0.5 - v3.getX() * 0.5, v4.getY() * 0.5 - v3.getY() * 0.5, v4.getZ() * 0.5 - v3.getZ() * 0.5);
                glVertex3d(v3.getX() * 0.5, v3.getY() * 0.5, v3.getZ() * 0.5);
                glVertex3d(v4.getX() * 0.5, v4.getY() * 0.5, v4.getZ() * 0.5);
            glEnd(); // concludes GL_QUADS

        }
    }
}

void OGLWidget::calculateVertexValence()
{
    for(unsigned int i = 0; i < vertices.size(); i++)
    {
        //cout << "Vertex: " << i << endl;

        Vertex v = vertices.at(i);
        int valence = 0;

        for(unsigned int j = 0; j < quads.size(); j++) {
            Quad q = quads.at(j);

            //cout << "Quad: " << j << endl;

            if(Vertex::compareVertices(&vertices.at(q.getP1()), &v)) {valence++;}
            if(Vertex::compareVertices(&vertices.at(q.getP2()), &v)) {valence++;}
            if(Vertex::compareVertices(&vertices.at(q.getP3()), &v)) {valence++;}
            if(Vertex::compareVertices(&vertices.at(q.getP4()), &v)) {valence++;}
        }

        v.setEdges(valence);

        cout << "Vertex: " << i << " | Kanten: " << valence << endl;
    }
}



void OGLWidget::determineQuadNeighbours()
{
    for(unsigned int i = 0; i < quads.size(); i++){
        Quad q = quads.at(i);

        Vertex v1 = vertices.at(q.getP1());
        Vertex v2 = vertices.at(q.getP2());
        Vertex v3 = vertices.at(q.getP3());
        Vertex v4 = vertices.at(q.getP4());

        for(unsigned int j= 0; j < quads.size(); j++){

            if(j != i){
                Quad qTemp = quads.at(j);

                bool p1Match = false;
                bool p2Match = false;
                bool p3Match = false;
                bool p4Match = false;

                Vertex vTemp1 = vertices.at(qTemp.getP1());
                Vertex vTemp2 = vertices.at(qTemp.getP2());
                Vertex vTemp3 = vertices.at(qTemp.getP3());
                Vertex vTemp4 = vertices.at(qTemp.getP4());

                if( Vertex::compareVertices(&v1, &vTemp1) ||
                    Vertex::compareVertices(&v1, &vTemp2) ||
                    Vertex::compareVertices(&v1, &vTemp3) ||
                    Vertex::compareVertices(&v1, &vTemp4) ) p1Match = true;

                if( Vertex::compareVertices(&v2, &vTemp1) ||
                    Vertex::compareVertices(&v2, &vTemp2) ||
                    Vertex::compareVertices(&v2, &vTemp3) ||
                    Vertex::compareVertices(&v2, &vTemp4) ) p2Match = true;

                if( Vertex::compareVertices(&v3, &vTemp1) ||
                    Vertex::compareVertices(&v3, &vTemp2) ||
                    Vertex::compareVertices(&v3, &vTemp3) ||
                    Vertex::compareVertices(&v3, &vTemp4) ) p3Match = true;

                if( Vertex::compareVertices(&v4, &vTemp1) ||
                    Vertex::compareVertices(&v4, &vTemp2) ||
                    Vertex::compareVertices(&v4, &vTemp3) ||
                    Vertex::compareVertices(&v4, &vTemp4) ) p4Match = true;


                if(p1Match && p2Match){
                    q.setN1(j);
                    cout << "Quad: " << i << " | Nachbar 1 | Index: " << j << endl;
                }
                else if(p2Match && p3Match){
                    q.setN2(j);
                    cout << "Quad: " << i << " | Nachbar 2 | Index: " << j << endl;
                }
                else if(p3Match && p4Match){
                    q.setN3(j);
                    cout << "Quad: " << i << " | Nachbar 3 | Index: " << j << endl;
                }
                else if(p4Match && p1Match){
                    q.setN4(j);
                    cout << "Quad: " << i << " | Nachbar 4 | Index: " << j << endl;
                }

            }
        }
    }
}


OGLWidget::OGLWidget(QWidget *parent) // constructor
    : QOpenGLWidget(parent)
{

}

OGLWidget::~OGLWidget() // destructor
{

}


void OGLWidget::initializeGL() // initializations to be called once
{
    // * https://www.ntu.edu.sg/home/ehchua/programming/opengl/CG_Examples.html

    initializeOpenGLFunctions();

    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL); // *
    glShadeModel(GL_SMOOTH); // *
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // *

    readSuccess = readData();

    if(readSuccess){
        calculateVertexValence();
        determineQuadNeighbours();
    }
}

void OGLWidget::paintGL() // draw everything, to be called repeatedly
{
    //glEnable(GL_NORMALIZE); // this is necessary when using glScale (keep normals to unit length)

    // set background color
    glClearColor(0,0,0,1); // bright blue
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw the scene
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();				// Reset The Current Modelview Matrix
    //glTranslated( 0 ,0 , 0.0);     // Move 10 units backwards in z, since camera is at origin
    glRotated( 45, 1, 1, 0);
    //glScaled( 2.0, 2.0, 2.0);

    // draw a cylinder with default resolution
    drawQuad();

    // make it appear (before this, it's hidden in the rear buffer)
    //glFlush();
}

void OGLWidget::resizeGL(int w, int h) // called when window size is changed
{
    // adjust viewport transform
    glViewport(0,0,w,h);
}

