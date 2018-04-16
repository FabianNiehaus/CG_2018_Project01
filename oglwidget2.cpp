#include "oglwidget2.h"

bool OGLWidget2::readData()
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
            vertices.push_back(Vertex(x,y,z,"v"));
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

void OGLWidget2::drawQuad() // drawing a quad in OpenGL
{
    if(readSuccess){

        cout << "Zeichne Lines" << endl;

        for(unsigned int i=0; i<quads.size();i++){
            Quad q = quads.at(i);

            Vertex v0 = vertices.at(q.getV(0));
            Vertex v1 = vertices.at(q.getV(1));
            Vertex v2 = vertices.at(q.getV(2));
            Vertex v3 = vertices.at(q.getV(3));

            /*
            glBegin(GL_LINES);
                glVertex3d(v0.getX() * 0.5, v0.getY() * 0.5, v0.getZ() * 0.5);
                glVertex3d(v1.getX() * 0.5, v1.getY() * 0.5, v1.getZ() * 0.5);

                glVertex3d(v1.getX() * 0.5, v1.getY() * 0.5, v1.getZ() * 0.5);
                glVertex3d(v2.getX() * 0.5, v2.getY() * 0.5, v2.getZ() * 0.5);

                glVertex3d(v2.getX() * 0.5, v2.getY() * 0.5, v2.getZ() * 0.5);
                glVertex3d(v3.getX() * 0.5, v3.getY() * 0.5, v3.getZ() * 0.5);

                glVertex3d(v3.getX() * 0.5, v3.getY() * 0.5, v3.getZ() * 0.5);
                glVertex3d(v0.getX() * 0.5, v0.getY() * 0.5, v0.getZ() * 0.5);
            glEnd();
            */

            QVector3D vec1 = QVector3D(v0.getX(), v0.getY(), v0.getZ());
            QVector3D vec2 = QVector3D(v1.getX(), v1.getY(), v1.getZ());
            QVector3D vec3 = QVector3D(v2.getX(), v2.getY(), v2.getZ());
            QVector3D vec4 = QVector3D(v3.getX(), v3.getY(), v3.getZ());

            glBegin(GL_QUADS);

                QVector3D vecTemp = QVector3D::crossProduct(vec3-vec2,vec3-vec1);

                glNormal3d(vecTemp.x(), vecTemp.y(), vecTemp.z());
                glVertex3d(v0.getX() * 0.5, v0.getY() * 0.5, v0.getZ() * 0.5);

                //vecTemp = QVector3D::crossProduct(vec1-vec2,vec3-vec2);
                glNormal3d(vecTemp.x(), vecTemp.y(), vecTemp.z());
                glVertex3d(v1.getX() * 0.5, v1.getY() * 0.5, v1.getZ() * 0.5);

                vecTemp = QVector3D::crossProduct(vec4-vec2,vec4-vec3);
                glNormal3d(vecTemp.x(), vecTemp.y(), vecTemp.z());
                glVertex3d(v2.getX() * 0.5, v2.getY() * 0.5, v2.getZ() * 0.5);

                //vecTemp = QVector3D::crossProduct(vec3-vec4,vec1-vec4);
                glNormal3d(vecTemp.x(), vecTemp.y(), vecTemp.z());
                glVertex3d(v3.getX() * 0.5, v3.getY() * 0.5, v3.getZ() * 0.5);
            glEnd();

        }
    }
}


OGLWidget2::OGLWidget2(QWidget *parent) // constructor
    : QOpenGLWidget(parent)
{

}

OGLWidget2::~OGLWidget2() // destructor
{

}


void OGLWidget2::initializeGL() // initializations to be called once
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
}

void OGLWidget2::paintGL() // draw everything, to be called repeatedly
{
    // set background color
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw the scene
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();				// Reset The Current Modelview Matrix
    glRotated( 45, 1, 1, 0);

    // draw a cylinder with default resolution
    drawQuad();
}

void OGLWidget2::resizeGL(int w, int h) // called when window size is changed
{
    // adjust viewport transform
    glViewport(0,0,w,h);
}

