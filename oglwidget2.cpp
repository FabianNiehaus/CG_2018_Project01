#include "oglwidget2.h"

bool OGLWidget2::readData()
{
    ifstream file("cube.obj");

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
                glVertex3d(v0.getX(), v0.getY(), v0.getZ());
                glVertex3d(v1.getX(), v1.getY(), v1.getZ());

                glVertex3d(v1.getX(), v1.getY(), v1.getZ());
                glVertex3d(v2.getX(), v2.getY(), v2.getZ());

                glVertex3d(v2.getX(), v2.getY(), v2.getZ());
                glVertex3d(v3.getX(), v3.getY(), v3.getZ());

                glVertex3d(v3.getX(), v3.getY(), v3.getZ());
                glVertex3d(v0.getX(), v0.getY(), v0.getZ());
            glEnd();
            */

            QVector3D vec1 = QVector3D(v0.getX(), v0.getY(), v0.getZ());
            QVector3D vec2 = QVector3D(v1.getX(), v1.getY(), v1.getZ());
            QVector3D vec3 = QVector3D(v2.getX(), v2.getY(), v2.getZ());
            QVector3D vec4 = QVector3D(v3.getX(), v3.getY(), v3.getZ());

            glBegin(GL_QUADS);

                QVector3D vecTemp = QVector3D::crossProduct(vec4-vec2,vec3-vec1);

                glNormal3d(vecTemp.x(), vecTemp.y(), vecTemp.z());
                glVertex3d(v0.getX(), v0.getY(), v0.getZ());

                //vecTemp = QVector3D::crossProduct(vec1-vec2,vec3-vec2);
                //glNormal3d(vecTemp.x(), vecTemp.y(), vecTemp.z());
                glVertex3d(v1.getX(), v1.getY(), v1.getZ());

                //vecTemp = QVector3D::crossProduct(vec4-vec2,vec4-vec3);
                //glNormal3d(vecTemp.x(), vecTemp.y(), vecTemp.z());
                glVertex3d(v2.getX(), v2.getY(), v2.getZ());

                //vecTemp = QVector3D::crossProduct(vec3-vec4,vec1-vec4);
                //glNormal3d(vecTemp.x(), vecTemp.y(), vecTemp.z());
                glVertex3d(v3.getX(), v3.getY(), v3.getZ());
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

// define material color properties for front and back side
void OGLWidget2::SetMaterialColor( int side, float r, float g, float b){
    float	amb[4], dif[4], spe[4];
    int	i, mat;

    dif[0] = r; // diffuse color as defined by r,g, and b
    dif[1] = g;
    dif[2] = b;
    for( i=0; i<3; i++){
        amb[i] = .1 * dif[i]; // ambient color is 10 percent of diffuse
        spe[i] = .5; // specular color is just white / gray
    }
    amb[3] = dif[3] = spe[3] = 1.0; // alpha component is always 1
    switch( side){
        case 1:	mat = GL_FRONT; break;
        case 2:	mat = GL_BACK; break;
        default: mat = GL_FRONT_AND_BACK; break;
    }
    glMaterialfv( mat, GL_AMBIENT, amb); // define ambient, diffuse and specular components
    glMaterialfv( mat, GL_DIFFUSE, dif);
    glMaterialfv( mat, GL_SPECULAR, spe);
    glMaterialf( mat, GL_SHININESS, 50.0); // Phong constant for the size of highlights
}

// initialize Open GL lighting and projection matrix
void OGLWidget2::InitLightingAndProjection() // to be executed once before drawing
{
    // light positions and colors
    GLfloat LightPosition1[4] = { 10, 5, 10,  0};
    GLfloat LightPosition2[4] = { -5, 5, -10,  0};
    GLfloat ColorRedish[4] = { 1.0,  .8,  .8,  1}; // white with a little bit of red
    GLfloat ColorBlueish[4] = { .8,  .8,  1.0,  1};// white with a little bit of blue

    glEnable( GL_DEPTH_TEST); // switch on z-buffer
    glDepthFunc( GL_LESS);

    glShadeModel( GL_SMOOTH); // Gouraud shading
    //glShadeModel( GL_FLAT);

    glEnable( GL_LIGHTING); // use lighting
    glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, 1); // draw both sides

    // define and switch on light 0
    glLightfv( GL_LIGHT0, GL_POSITION, LightPosition1);
    glLightfv( GL_LIGHT0, GL_DIFFUSE,  ColorRedish);
    glLightfv( GL_LIGHT0, GL_SPECULAR, ColorRedish);
    glEnable( GL_LIGHT0);

    // define and switch on light 1
    glLightfv( GL_LIGHT1, GL_POSITION, LightPosition2);
    glLightfv( GL_LIGHT1, GL_DIFFUSE,  ColorBlueish);
    glLightfv( GL_LIGHT1, GL_SPECULAR, ColorBlueish);
    glEnable( GL_LIGHT1);

    glMatrixMode( GL_PROJECTION); // define camera projection
    glLoadIdentity(); // reset matrix to identity (otherwise existing matrix will be multiplied with)
    glOrtho( -15, 15, -15, 15, -15, 15); // orthogonal projection (xmin xmax ymin ymax zmin zmax)
    //glFrustum( -10, 10, -8, 8, 2, 20); // perspective projektion
}

void OGLWidget2::initializeGL() // initializations to be called once
{
    // * https://www.ntu.edu.sg/home/ehchua/programming/opengl/CG_Examples.html

    initializeOpenGLFunctions();
    InitLightingAndProjection();

    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); //

    readSuccess = readData();
}

void OGLWidget2::paintGL() // draw everything, to be called repeatedly
{
    glEnable(GL_NORMALIZE); // this is necessary when using glScale (keep normals to unit length)

    // set background color
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw the scene
    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();				// Reset The Current Modelview Matrix
    glTranslated( 0 ,0 ,-10.0);     // Move 10 units backwards in z, since camera is at origin
    glScaled( 5.0, 5.0, 5.0);       // scale objects
    glRotated( 45, 1, 1, 0);     // continuous rotation
    //alpha += 5;

    // define color: 1=front, 2=back, 3=both, followed by r, g, and b
    SetMaterialColor( 1, 1.0, .2, .2);  // front color is red
    SetMaterialColor( 2, 0.2, 0.2, 1.0); // back color is blue

    // draw a cylinder with default resolution
    drawQuad();

    // make it appear (before this, it's hidden in the rear buffer)
    glFlush();
}

void OGLWidget2::resizeGL(int w, int h) // called when window size is changed
{
    // adjust viewport transform
    glViewport(0,0,w,h);
}

