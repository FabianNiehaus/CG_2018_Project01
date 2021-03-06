#include "oglwidget3.h"

bool OGLWidget3::readData()
{
    ifstream file("threeholes.obj");

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
            if(file.eof()) break;
            file >> p1 >> p2 >> p3 >> p4;
            quads.push_back(Quad(p1-1, p2-1, p3-1, p4-1));
        }
    }

    file.close();

    cout << "[W3] Objekt-Datei eingelesen!" << endl;
    return true;
}

void OGLWidget3::drawLines() // drawing a quad in OpenGL
{
    if(readSuccess){

        for(unsigned int i=0; i<quads.size();i++){
            Quad q = quads.at(i);

            Vertex v0 = vertices.at(q.getV(0));
            Vertex v1 = vertices.at(q.getV(1));
            Vertex v2 = vertices.at(q.getV(2));
            Vertex v3 = vertices.at(q.getV(3));

            glBegin(GL_LINES);
                glColor3f(0.0,0.0,0.0);

                glVertex3d(v0.getX(), v0.getY(), v0.getZ());
                glVertex3d(v1.getX(), v1.getY(), v1.getZ());

                glVertex3d(v1.getX(), v1.getY(), v1.getZ());
                glVertex3d(v2.getX(), v2.getY(), v2.getZ());

                glVertex3d(v2.getX(), v2.getY(), v2.getZ());
                glVertex3d(v3.getX(), v3.getY(), v3.getZ());

                glVertex3d(v3.getX(), v3.getY(), v3.getZ());
                glVertex3d(v0.getX(), v0.getY(), v0.getZ());
            glEnd();

        }
    }
}


OGLWidget3::OGLWidget3(QWidget *parent) // constructor
    : QOpenGLWidget(parent)
{
    // Setup the animation timer to fire every x msec
        animtimer = new QTimer(this);
        animtimer->start( 50 );

        // Everytime the timer fires, the animation is going one step forward
        connect(animtimer, SIGNAL(timeout()), this, SLOT(stepAnimation()));

        animstep = 0;
}

OGLWidget3::~OGLWidget3() // destructor
{

}

void OGLWidget3::stepAnimation()
{
    animstep++;    // Increase animation steps
    update();      // Trigger redraw of scene with paintGL
}

// define material color properties for front and back side
void OGLWidget3::SetMaterialColor( int side, float r, float g, float b){
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
void OGLWidget3::InitLightingAndProjection() // to be executed once before drawing
{

    glEnable( GL_DEPTH_TEST); // switch on z-buffer
    glDepthFunc( GL_LESS);

    glShadeModel( GL_FLAT);

    glMatrixMode( GL_PROJECTION); // define camera projection
    glLoadIdentity(); // reset matrix to identity (otherwise existing matrix will be multiplied with)
    glOrtho( -15, 15, -15, 15, -15, 15); // orthogonal projection (xmin xmax ymin ymax zmin zmax)

}

void OGLWidget3::initializeGL() // initializations to be called once
{
    initializeOpenGLFunctions();
    InitLightingAndProjection();

    readSuccess = readData();
}

void OGLWidget3::paintGL() // draw everything, to be called repeatedly
{
    glEnable(GL_NORMALIZE); // this is necessary when using glScale (keep normals to unit length)

    // set background color
    glClearColor(0.8, 0.8, 0.8, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw the scene
    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();				// Reset The Current Modelview Matrix
    glTranslated( 0 ,0 ,-1.0);     // Move 10 units backwards in z, since camera is at origin
    glScaled(2,2,2);       // scale objects
    glRotated( alpha, 0, 3, 1);     // continuous rotation
    alpha += 2;

    // define color: 1=front, 2=back, 3=both, followed by r, g, and b
    SetMaterialColor( 1, 1.0, 0.2, 0.2);  // front color is red
    SetMaterialColor( 2, 0.2, 0.2, 1.0); // back color is blue

    // draw a cylinder with default resolution
    drawLines();

    // make it appear (before this, it's hidden in the rear buffer)
    glFlush();
}

void OGLWidget3::resizeGL(int w, int h) // called when window size is changed
{
    // adjust viewport transform
    glViewport(0,0,w,h);
}

