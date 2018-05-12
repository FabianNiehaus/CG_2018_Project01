#include "oglscenewidget.h"

void OGLSceneWidget::drawLines(vector<Quad> quads, vector<Vertex> vertices)
{

    for(unsigned int i=0; i<quads.size();i++){
        Quad q = quads.at(i);

        Vertex v0 = vertices.at(q.getV(0));
        Vertex v1 = vertices.at(q.getV(1));
        Vertex v2 = vertices.at(q.getV(2));
        Vertex v3 = vertices.at(q.getV(3));

        glBegin(GL_LINES);
            //glColor3f(0.0,0.0,0.0);

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

void OGLSceneWidget::drawQuad(vector<Quad> quads, vector<Vertex> vertices) // drawing a quad in OpenGL
{


    for(unsigned int i=0; i<quads.size();i++){
        Quad  q = quads.at(i);

        Vertex  v0 = vertices.at(q.getV(0));
        Vertex  v1 = vertices.at(q.getV(1));
        Vertex  v2 = vertices.at(q.getV(2));
        Vertex  v3 = vertices.at(q.getV(3));

        QVector3D vec1 = QVector3D(v0.getX(), v0.getY(), v0.getZ());
        QVector3D vec2 = QVector3D(v1.getX(), v1.getY(), v1.getZ());
        QVector3D vec3 = QVector3D(v2.getX(), v2.getY(), v2.getZ());
        QVector3D vec4 = QVector3D(v3.getX(), v3.getY(), v3.getZ());

        glBegin(GL_QUADS);

            QVector3D vecTemp = QVector3D::crossProduct(vec3-vec1,vec4-vec2);

            glNormal3d(vecTemp.x(), vecTemp.y(), vecTemp.z());

            glVertex3d(v0.getX(), v0.getY(), v0.getZ());
            glVertex3d(v1.getX(), v1.getY(), v1.getZ());
            glVertex3d(v2.getX(), v2.getY(), v2.getZ());
            glVertex3d(v3.getX(), v3.getY(), v3.getZ());

        glEnd();

    }
}

OGLSceneWidget::OGLSceneWidget(QWidget *parent) : QOpenGLWidget(parent) // constructor
{
    if(rotating){
    // Setup the animation timer to fire every x msec
        animtimer = new QTimer(this);
        animtimer->start( 50 );

        // Everytime the timer fires, the animation is going one step forward
        connect(animtimer, SIGNAL(timeout()), this, SLOT(stepAnimation()));

        animstep = 0;
    }
}

OGLSceneWidget::~OGLSceneWidget() // destructor
{

}

void OGLSceneWidget::stepAnimation()
{
    animstep++;    // Increase animation steps
    update();      // Trigger redraw of scene with paintGL
}

// define material color properties for front and back side
void OGLSceneWidget::SetMaterialColor( int side, float r, float g, float b){
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
void OGLSceneWidget::InitLightingAndProjection() // to be executed once before drawing
{

    // light positions and colors
    GLfloat LightPosition1[4] = { 10, 5, 10,  0};
    GLfloat LightPosition2[4] = { -5, 5, -10,  0};
    GLfloat ColorRedish[4] = { 1.0,  .8,  .8,  1}; // white with a little bit of red
    GLfloat ColorBlueish[4] = { .8,  .8,  1.0,  1};// white with a little bit of blue

    glEnable( GL_DEPTH_TEST); // switch on z-buffer
    glDepthFunc( GL_LESS);

    glShadeModel( GL_SMOOTH); // Gouraud shading

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

}

void OGLSceneWidget::initializeGL() // initializations to be called once
{
    initializeOpenGLFunctions();
    InitLightingAndProjection();

    cSurf1 = new CubeSurface("gear.obj");
    cSurf2 = new CubeSurface("gear.obj");
    bSurf = new BezierSurface();
    sSurf = new SweepSurface();


    cSurf1->performBlackMagic(0);
    cSurf2->performBlackMagic(3);
    bSurf->calculateBezier();
    sSurf->performBlackMagic();

}

void OGLSceneWidget::paintGL() // draw everything, to be called repeatedly
{
    glEnable(GL_NORMALIZE); // this is necessary when using glScale (keep normals to unit length)

    // set background color
    glClearColor(0.8, 0.8, 0.8, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw the scene
    glMatrixMode( GL_MODELVIEW);

    glLoadIdentity();
    glScaled(1,1,1);
    SetMaterialColor( 1, 1.0, 0.2, 0.2);  // front color is red
    SetMaterialColor( 2, 0.2, 0.2, 1.0); // back color is blue
    glTranslated( -6 ,5 ,0);
    if(rotation) glRotated( 15, 1, -1, 0);
    if(rotating) {
        glTranslated(0,0,0);
        glRotated(alpha, 0, 0, 1);
        glTranslated(0,0,0);
    }
    drawQuad(cSurf1->getQuads(), cSurf1->getVertices());

    glLoadIdentity();
    glScaled(1,1,1);
    SetMaterialColor( 1, 1.0, 0.2, 0.2);  // front color is red
    SetMaterialColor( 2, 0.2, 0.2, 1.0); // back color is blue
    glTranslated( 5 ,5 ,0);
    if(rotation) glRotated( 15, 1, -1, 0);
    if(rotating) {
        glTranslated(0,0,0);
        glRotated(alpha, 0, 0, 1);
        glTranslated(0,0,0);
    }
    drawQuad(cSurf2->getQuads(), cSurf2->getVertices());

    glLoadIdentity();
    glScaled(2,2,2);
    SetMaterialColor( 1, 1.0, 0.2, 0.2);  // front color is red
    SetMaterialColor( 2, 0.2, 0.2, 1.0); // back color is blue
    glTranslated( -5 ,-4 ,0);
    if(rotation) glRotated( 90, 1, 0, 0.1);
    if(rotating) {
        glTranslated(1.5,1.5,0);
        glRotated(alpha, 0, 0, 1);
        glTranslated(-1.5,-1.5,0);
    }
    drawLines(bSurf->getPreQuads(), bSurf->getPreBezierVertices());
    drawQuad(bSurf->getPostQuads(), bSurf->getPostBezierVertices());

    glLoadIdentity();
    glScaled(1,2,2);
    SetMaterialColor( 1, 1.0, 0.2, 0.2);  // front color is red
    SetMaterialColor( 2, 0.2, 0.2, 1.0); // back color is blue
    glTranslated(2,-4,0);
    if(rotation) glRotated(15, 0, 5, 1);
    if(rotating) {
        glTranslated(0,0,0);
        glRotated(alpha, -1, 0, 0);
        glTranslated(0,0,0);
    }
    drawQuad(sSurf->getQuads(), sSurf->getVertices());

    alpha += 2;

    // make it appear (before this, it's hidden in the rear buffer)
    glFlush();
}

void OGLSceneWidget::resizeGL(int w, int h) // called when window size is changed
{
    // adjust viewport transform
    glViewport(0,0,w,h);
}
