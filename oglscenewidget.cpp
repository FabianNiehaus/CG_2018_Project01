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

void OGLSceneWidget::drawQuadrantSeparators()
{
    glBegin(GL_LINES);
        glVertex3d(-100,0,0);
        glVertex3d(100,0,0);

        glVertex3d(0,-100,0);
        glVertex3d(0,100,0);

        glVertex3d(0,-100,0);
        glVertex3d(0,100,0);

    glEnd();
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
    glOrtho( -20, 20, -20, 20, -20, 20); // orthogonal projection (xmin xmax ymin ymax zmin zmax)

}

void OGLSceneWidget::initializeGL() // initializations to be called once
{
    initializeOpenGLFunctions();
    InitLightingAndProjection();

    cSurf1 = new CubeSurface("cube.obj");
    cSurf2 = new CubeSurface("cube.obj");

    tSurf1 = new CubeSurface("threeholes.obj");
    tSurf2 = new CubeSurface("threeholes.obj");

    gSurf1 = new CubeSurface("gear.obj");
    gSurf2 = new CubeSurface("gear.obj");
    gSurf3 = new CubeSurface("gear.obj");
    gSurf4 = new CubeSurface("gear.obj");

    bSurf1 = new BezierSurface("bezier01.surf");
    bSurf2 = new BezierSurface("bezier02.surf");

    sSurf1 = new SweepSurface("curve01.curve");
    sSurf2 = new SweepSurface("curve02.curve");


    cSurf1->performBlackMagic(0);
    cSurf2->performBlackMagic(3);

    tSurf1->performBlackMagic(0);
    tSurf2->performBlackMagic(3);

    gSurf1->performBlackMagic(0);
    gSurf2->performBlackMagic(0);
    gSurf3->performBlackMagic(1);
    gSurf4->performBlackMagic(3);

    bSurf1->calculateBezier();
    bSurf2->calculateBezier();

    sSurf1->performBlackMagic();
    sSurf2->performBlackMagic();

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
    drawQuadrantSeparators();

    // Würfel ohne CC
    glLoadIdentity();
    SetMaterialColor( 1, 1.0, 0.2, 0.2);
    SetMaterialColor( 2, 0.2, 0.2, 1.0);
    glTranslated( -15 ,15 ,0);
    if(rotation) glRotated( 15, 1, -1, 0);
    if(rotating) {
        glTranslated(0,0,0);
        glRotated(alpha, 0, 0, 1);
        glTranslated(0,0,0);
    }
    glScaled(2,2,2);
    drawQuad(cSurf1->getQuads(), cSurf1->getVertices());

    // Würfel mit CC
    glLoadIdentity();
    SetMaterialColor( 1, 1.0, 0.2, 0.2);
    SetMaterialColor( 2, 0.2, 0.2, 1.0);
    glTranslated( -7.5 ,15 ,0);
    if(rotation) glRotated( 15, 1, -1, 0);
    if(rotating) {
        glTranslated(0,0,0);
        glRotated(alpha, 0, 0, 1);
        glTranslated(0,0,0);
    }
    glScaled(2,2,2);
    drawQuad(cSurf2->getQuads(), cSurf2->getVertices());

    // Threeholes ohne CC
    glLoadIdentity();
    SetMaterialColor( 1, 1.0, 0.2, 0.2);
    SetMaterialColor( 2, 0.2, 0.2, 1.0);
    glTranslated( -18.5 ,4.5 ,0);
    if(rotation) glRotated( 15, 1, -1, 0);
    if(rotating) {
        glTranslated(3.5,3,0);
        glRotated(alpha, 0, -1, 0);
        glTranslated(-3.5,-3,0);
    }
    glScaled(1,1,1);
    drawQuad(tSurf1->getQuads(), tSurf1->getVertices());

    // Threeholes mit CC
    glLoadIdentity();
    SetMaterialColor( 1, 1.0, 0.2, 0.2);
    SetMaterialColor( 2, 0.2, 0.2, 1.0);
    glTranslated( -11 ,4.5 ,0);
    if(rotation) glRotated( 15, 1, -1, 0);
    if(rotating) {
        glTranslated(3.5,3,0);
        glRotated(alpha, 0, -1, 0);
        glTranslated(-3.5,-3,0);
    }
    glScaled(1,1,1);
    drawQuad(tSurf2->getQuads(), tSurf2->getVertices());

    // Zahnrad als WF
    glLoadIdentity();
    SetMaterialColor( 1, 1.0, 0.2, 0.2);
    SetMaterialColor( 2, 0.2, 0.2, 1.0);
    glTranslated(7.5 ,15 ,0);
    if(rotation) glRotated( 15, 1, -1, 0);
    if(rotating) {
        glTranslated(0,0,0);
        glRotated(alpha, 0, 0, 1);
        glTranslated(0,0,0);
    }
    glScaled(1,1,1);
    drawLines(gSurf1->getQuads(), gSurf1->getVertices());

    // Zahnrad ohne CC
    glLoadIdentity();
    SetMaterialColor( 1, 1.0, 0.2, 0.2);
    SetMaterialColor( 2, 0.2, 0.2, 1.0);
    glTranslated(15 ,15 ,0);
    if(rotation) glRotated( 15, 1, -1, 0);
    if(rotating) {
        glTranslated(0,0,0);
        glRotated(alpha, 0, 0, 1);
        glTranslated(0,0,0);
    }
    glScaled(1,1,1);
    drawQuad(gSurf2->getQuads(), gSurf2->getVertices());


    // Zahnrad mit 1x CC
    glLoadIdentity();
    SetMaterialColor( 1, 1.0, 0.2, 0.2);
    SetMaterialColor( 2, 0.2, 0.2, 1.0);
    glTranslated(7.5 ,7.5 ,0);
    if(rotation) glRotated( 15, 1, -1, 0);
    if(rotating) {
        glTranslated(0,0,0);
        glRotated(alpha, 0, 0, 1);
        glTranslated(0,0,0);
    }
    glScaled(1,1,1);
    drawQuad(gSurf3->getQuads(), gSurf3->getVertices());

    // Zahnrad mit 3x CC
    glLoadIdentity();
    SetMaterialColor( 1, 1.0, 0.2, 0.2);
    SetMaterialColor( 2, 0.2, 0.2, 1.0);
    glTranslated( 15 ,7.5 ,0);
    if(rotation) glRotated( 15, 1, -1, 0);
    if(rotating) {
        glTranslated(0,0,0);
        glRotated(alpha, 0, 0, 1);
        glTranslated(0,0,0);
    }
    glScaled(1,1,1);
    drawQuad(gSurf4->getQuads(), gSurf4->getVertices());


    // Bezier 01
    glLoadIdentity();
    SetMaterialColor( 1, 1.0, 0.2, 0.2);
    SetMaterialColor( 2, 0.2, 0.2, 1.0);
    glTranslated( -9 ,-7.5 ,0);
    glScaled(2,2,2);
    if(rotation) glRotated( 90, 1, 0, 0.1);
    if(rotating) {
        glTranslated(1.5,1.5,0);
        glRotated(alpha, 0, 0, 1);
        glTranslated(-1.5,-1.5,0);
    }
    drawLines(bSurf1->getPreQuads(), bSurf1->getPreBezierVertices());
    drawQuad(bSurf1->getPostQuads(), bSurf1->getPostBezierVertices());

    // Bezier 02
    glLoadIdentity();
    SetMaterialColor( 1, 1.0, 0.2, 0.2);
    SetMaterialColor( 2, 0.2, 0.2, 1.0);
    glTranslated( -16.5 ,-15 ,0);
    glScaled(2,2,2);
    if(rotation) glRotated( 90, 1, 0, 0.1);
    if(rotating) {
        glTranslated(1.5,1.5,0);
        glRotated(alpha, 0, 0, 1);
        glTranslated(-1.5,-1.5,0);
    }
    drawLines(bSurf2->getPreQuads(), bSurf2->getPreBezierVertices());
    drawQuad(bSurf2->getPostQuads(), bSurf2->getPostBezierVertices());


    // Sweep 01
    glLoadIdentity();
    SetMaterialColor( 1, 1.0, 0.2, 0.2);
    SetMaterialColor( 2, 0.2, 0.2, 1.0);
    glTranslated(2.5,-7.5,0);
    if(rotation) glRotated(15, 0, 5, 1);
    if(rotating) {
        glTranslated(0,0,0);
        glRotated(alpha, -1, 0, 0);
        glTranslated(0,0,0);
    }
    glScaled(1,2,2);
    drawQuad(sSurf1->getQuads(), sSurf1->getVertices());

    // Sweep 02
    glLoadIdentity();
    SetMaterialColor( 1, 1.0, 0.2, 0.2);
    SetMaterialColor( 2, 0.2, 0.2, 1.0);
    glTranslated(7.5,-15,0);
    if(rotation) glRotated(15, 0, 5, 1);
    if(rotating) {
        glTranslated(0,0,0);
        glRotated(alpha, -1, 0, 0);
        glTranslated(0,0,0);
    }
    glScaled(1.5,1.5,1.5);
    drawQuad(sSurf2->getQuads(), sSurf2->getVertices());

    alpha += 2;

    // make it appear (before this, it's hidden in the rear buffer)
    glFlush();
}

void OGLSceneWidget::resizeGL(int w, int h) // called when window size is changed
{
    // adjust viewport transform
    glViewport(0,0,w,h);
}
