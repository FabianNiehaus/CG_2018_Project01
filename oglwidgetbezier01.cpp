#include "oglwidgetbezier01.h"

#define DEBUG
// #define DEBUG_VERBOSE

bool OGLWidgetBezier01::readData()
{
    ifstream file("bezierInput.mesh");

    if(!file){
        cout << "error opening file" << endl;
        return false;
    }

    vector<vector<vector<float>>> values(3);
    int xyz = 0;
    string line;

    while( getline(file, line)){

        if(line.empty()){
            xyz++;
        }

        stringstream linestream(line);

        float value;
        vector<float> singleRow(0);

        while(linestream >> value){
           singleRow.push_back(value);
        }

        if(!line.empty()) values.at(xyz).push_back(singleRow);
    }

    file.close();

    int cols =values.at(0).at(0).size();
    int rows = values.at(0).size();

    inputMat.setSize(rows, cols);

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){

            float x = values.at(0).at(i).at(j);
            float y = values.at(1).at(i).at(j);
            float z = values.at(2).at(i).at(j);

            preBezierVertices.push_back(Vertex(x,y,z,"v"));
            inputMat.setAt(i,j, preBezierVertices.size()-1);
        }
    }

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){

            preBezierQuads.push_back(
                        Quad(
                            inputMat.at(i,j),
                            inputMat.at(i,j+1),
                            inputMat.at(i+1,j+1),
                            inputMat.at(i+1,j)
                            ));
        }
    }

    cout << "[Bezier] Objekt-Datei eingelesen!" << endl;
    return true;
}

void OGLWidgetBezier01::drawLines()
{

    for(unsigned int i=0; i<preBezierQuads.size();i++){
        Quad q = preBezierQuads.at(i);

        Vertex v0 = preBezierVertices.at(q.getV(0));
        Vertex v1 = preBezierVertices.at(q.getV(1));
        Vertex v2 = preBezierVertices.at(q.getV(2));
        Vertex v3 = preBezierVertices.at(q.getV(3));

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



void OGLWidgetBezier01::drawQuad() // drawing a quad in OpenGL
{
    if(readSuccess){

        for(unsigned int i=0; i<postBezierQuads.size();i++){
            Quad  q = postBezierQuads.at(i);

            Vertex  v0 = postBezierVertices.at(q.getV(0));
            Vertex  v1 = postBezierVertices.at(q.getV(1));
            Vertex  v2 = postBezierVertices.at(q.getV(2));
            Vertex  v3 = postBezierVertices.at(q.getV(3));

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
}

void OGLWidgetBezier01::calculateBezier()
{

    postBezierMat.setSize(steps+1, steps+1);

    for(float s = 0.0; s < (1.0 + 1.0 / steps); s += 1.0 / steps){
        for(float t = 0.0; t < (1.0 + 1.0 / steps); t += 1.0 / steps){

            Vertex v = Vertex(0.0f,0.0f,0.0f,"v");

            for(int i = 0; i <= m; i++){
                for(int j = 0; j <= n; j++){

                    Vertex vIn = Vertex(preBezierVertices.at(inputMat.at(i,j)));

                    Vertex vTemp = Vertex::multiplyVertex(vIn, bernstein(m,i,s) * bernstein(n,j,t));

                    v = Vertex::addVertices(v, vTemp);

#ifdef DEBUG_VERBOSE
    cout << "Bezier: " << s << " " << t << " " << i << " " << j << " vIn: " << vIn.toString() << " vTemp: " << vTemp.toString() << " Res: " << v.toString() << endl;
#endif
                }
            }

#ifdef DEBUG
            cout << "(" << s * steps << "," << t * steps << ") New: " << v.toString() << endl;
#endif

            postBezierVertices.push_back(v);
            postBezierMat.setAt((int)(s * steps), (int)(t * steps), postBezierVertices.size()-1);
        }
    }

    for(int i = 0; i < steps; i++){
        for(int j = 0; j < steps; j++){

            postBezierQuads.push_back(
                        Quad(
                            postBezierMat.at(i,j),
                            postBezierMat.at(i,j+1),
                            postBezierMat.at(i+1,j+1),
                            postBezierMat.at(i+1,j)
                            ));
        }
    }

}

float OGLWidgetBezier01::bernstein(int n, int i, float s)
{
    float bernstein = 0.0;

    bernstein = choose(n,i);
    bernstein *= pow(s,i);
    bernstein *= pow(1.0-s, n-i);

#ifdef DEBUG_VERBOSE
    cout << "Bernst.: " << n << " " << i << " " << s << " Res:" << bernstein << endl;
#endif

    return bernstein;
}

float OGLWidgetBezier01::choose(int n, int i)
{
    float choose = 0.0;

    int top = fact(n);
    int div = fact(i) * fact(n-i);

    if((float)div != 0.0) choose = (float)top / (float)div;
    else choose = 1;

#ifdef DEBUG_VERBOSE
    cout << "Choose: " << n << " " << i << " Res:" << choose << endl;
#endif

    return choose;
}

int OGLWidgetBezier01::fact(int n)
{
    int input = n;
    int fact = 0;

    while(n > 0){
        fact *= n;
        n--;
    }

#ifdef DEBUG_VERBOSE
    cout << "Fact.: " << input << " Res:" << fact << endl;
#endif

    return fact;
}

OGLWidgetBezier01::OGLWidgetBezier01(QWidget *parent) : QOpenGLWidget(parent) // constructor
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

OGLWidgetBezier01::~OGLWidgetBezier01() // destructor
{

}

void OGLWidgetBezier01::stepAnimation()
{
    animstep++;    // Increase animation steps
    update();      // Trigger redraw of scene with paintGL
}

// define material color properties for front and back side
void OGLWidgetBezier01::SetMaterialColor( int side, float r, float g, float b){
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
void OGLWidgetBezier01::InitLightingAndProjection() // to be executed once before drawing
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

void OGLWidgetBezier01::initializeGL() // initializations to be called once
{
    initializeOpenGLFunctions();
    InitLightingAndProjection();

    readSuccess = readData();
    calculateBezier();

}

void OGLWidgetBezier01::paintGL() // draw everything, to be called repeatedly
{
    glEnable(GL_NORMALIZE); // this is necessary when using glScale (keep normals to unit length)

    // set background color
    glClearColor(0.8, 0.8, 0.8, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw the scene
    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();
    glTranslated( -1.5 ,0 ,0);
    glScaled(2,2,2);
    if(rotation) glRotated( 90, 1, 0, 0.1);
    if(rotating) {
        glTranslated(1.5,1.5,0);
        alpha += 2;
        glRotated(alpha, 0, 0, 1);
        glTranslated(-1.5,-1.5,0);
    }

    // define color: 1=front, 2=back, 3=both, followed by r, g, and b
    SetMaterialColor( 1, 1.0, 0.2, 0.2);  // front color is red
    SetMaterialColor( 2, 0.2, 0.2, 1.0); // back color is blue

    // draw a cylinder with default resolution
    drawLines();
    drawQuad();

    // make it appear (before this, it's hidden in the rear buffer)
    glFlush();
}

void OGLWidgetBezier01::resizeGL(int w, int h) // called when window size is changed
{
    // adjust viewport transform
    glViewport(0,0,w,h);
}
