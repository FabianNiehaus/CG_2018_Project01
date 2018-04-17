#include "oglwidget.h"

#define DEBUG

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
            vertices.push_back( Vertex(x,y,z,"v"));
        }

        if(key == "f"){
            file >> p1 >> p2 >> p3 >> p4;
            if( file.eof() ) break;
            quads.push_back( Quad(p1-1, p2-1, p3-1, p4-1));
        }
    }

    file.close();

    cout << "Objekt-Datei eingelesen!" << endl;
    return true;
}

void OGLWidget::drawQuad() // drawing a quad in OpenGL
{
    if(readSuccess){

        cout << endl;
        cout << "Zeichne Quads!" << endl;
        cout << endl;

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

            /*
            glBegin(GL_LINES);
                glColor3f(0.0f, 0.0f, 1.f);

                glVertex3d(v0.getX() * 0.5, v0.getY() * 0.5, v0.getZ() * 0.5);
                glVertex3d(v1.getX() * 0.5, v1.getY() * 0.5, v1.getZ() * 0.5);

                glVertex3d(v1.getX() * 0.5, v1.getY() * 0.5, v1.getZ() * 0.5);
                glVertex3d(v2.getX() * 0.5, v2.getY() * 0.5, v2.getZ() * 0.5);

                glVertex3d(v2.getX() * 0.5, v2.getY() * 0.5, v2.getZ() * 0.5);
                glVertex3d(v3.getX() * 0.5, v3.getY() * 0.5, v3.getZ() * 0.5);

                glVertex3d(v3.getX() * 0.5, v3.getY() * 0.5, v3.getZ() * 0.5);
                glVertex3d(v0.getX()*  0.5, v0.getY() * 0.5, v0.getZ() * 0.5);
            glEnd();
            */

            glBegin(GL_QUADS);

                QVector3D vecTemp = QVector3D::crossProduct(vec3-vec1,vec4-vec2);
                glNormal3d(vecTemp.x(), vecTemp.y(), vecTemp.z());
                glVertex3d(v0.getX() * 0.5, v0.getY() * 0.5, v0.getZ() * 0.5);

                //vecTemp = QVector3D::crossProduct(vec1-vec2,vec3-vec2);
                //glNormal3d(vecTemp.x(), vecTemp.y(), vecTemp.z());
                glVertex3d(v1.getX() * 0.5, v1.getY() * 0.5, v1.getZ() * 0.5);

                //vecTemp = QVector3D::crossProduct(vec2-vec3,vec4-vec3);
                //glNormal3d(vecTemp.x(), vecTemp.y(), vecTemp.z());
                glVertex3d(v2.getX() * 0.5, v2.getY() * 0.5, v2.getZ() * 0.5);

                //vecTemp = QVector3D::crossProduct(vec3-vec4,vec1-vec4);
                //glNormal3d(vecTemp.x(), vecTemp.y(), vecTemp.z());
                glVertex3d(v3.getX() * 0.5, v3.getY() * 0.5, v3.getZ() * 0.5);
            glEnd();

        }
    }
}


// Immer positive Modulos: https://stackoverflow.com/questions/14997165/fastest-way-to-get-a-positive-modulo-in-c-c
inline int pos_mod(int i, int n) {
    return (i % n + n) % n;
}

void OGLWidget::calculateVertexValence()
{
    cout << endl;
    cout << "Bestimme Vertex-Valenzen" << endl;
    cout << endl;

    for(unsigned int i = 0; i < vertices.size(); i++)
    {
        //cout << "Vertex: " << i << endl;

        Vertex  v = vertices.at(i);
        int valence = 0;

        for(unsigned int j = 0; j < quads.size(); j++) {
            Quad  q = quads.at(j);

            //cout << "Quad: " << j << endl;

            if(Vertex::compareVertices(vertices.at(q.getV(0)), v)) {valence++;}
            if(Vertex::compareVertices(vertices.at(q.getV(1)), v)) {valence++;}
            if(Vertex::compareVertices(vertices.at(q.getV(2)), v)) {valence++;}
            if(Vertex::compareVertices(vertices.at(q.getV(3)), v)) {valence++;}
        }

        vertices.at(i).setValence(valence);

#ifdef DEBUG_VERBOSE
        cout << "Vertex: " << i << " | Kanten: " << valence << endl;
#endif
    }
}



void OGLWidget::determineQuadNeighbours()
{
    cout << endl;
    cout << "Bestimme Nachbarn!" << endl;
    cout << endl;

    for(unsigned int i = 0; i < quads.size(); i++){
        Quad  q = quads.at(i);

        for(int j = 0; j < 4; j++){

            int a = q.getV( pos_mod(j,4) );
            int b = q.getV( pos_mod(j+1, 4) );

            for(unsigned int k = 0; k < quads.size(); k++){

                if(k != i){
                    // Nachbarkandidat
                    Quad  qTemp = quads.at(k);

                    if( (a == qTemp.getV(0) || a == qTemp.getV(1) || a == qTemp.getV(2) || a == qTemp.getV(3))
                            && (b == qTemp.getV(0) || b == qTemp.getV(1) || b == qTemp.getV(2) || b == qTemp.getV(3)))
                    {
                        quads.at(i).setQ(j, k);
                    }
                }
            }
        }
    }

#ifdef DEBUG
    for(unsigned int i = 0; i < quads.size(); i++){
        cout << quads.at(i).toString() << endl;;
    }
}
#endif

void OGLWidget::ccSubdivision()
{
    cout << endl;
    cout << "Starte Catmull-Clark-Subdivision!" <<endl;
    cout << endl;

    // Berechne Face-Mask f für jeden Quad
    for(unsigned int i = 0; i < quads.size(); i++){
        Quad  q = quads.at(i);

        Vertex  v0 = vertices.at(q.getV(0));
        Vertex  v1 = vertices.at(q.getV(1));
        Vertex  v2 = vertices.at(q.getV(2));
        Vertex  v3 = vertices.at(q.getV(3));

        float xFace = (v0.getX() + v1.getX() + v2.getX() + v3.getX()) / 4;
        float yFace = (v0.getY() + v1.getY() + v2.getY() + v3.getY()) / 4;
        float zFace = (v0.getZ() + v1.getZ() + v2.getZ() + v3.getZ()) / 4;

        Vertex  vFace =  Vertex(xFace, yFace, zFace, "f");

        vertices.push_back(vFace);
        size_t index = vertices.size() - 1;

        quads.at(i).setF(index);

#ifdef DEBUG_VERBOSE
        cout << "Quad: " << i << " | Face: " << index << " . " << vFace.toString() << endl;
#endif
    }

    // Berechne Edge-Masks e_j für jeden Quad
    for(unsigned int i = 0; i < quads.size(); i++){
        Quad  q = quads.at(i);

        // Durchlaufe die 4 Nachbarn
        for(unsigned int j = 0; j < 4; j++){

            Quad  neighbour = quads.at(q.getQ(j));

            // Eigener Index kleiner als der des Nachbarn . Edge-Mask selbst berechnen: e_i = 0,5  (v_i + v_i+1)
            if( i < (unsigned int)q.getQ(j)){

                Vertex  v_0 = vertices.at(q.getV( pos_mod(j, 4))); // 'linker' Eckpunkt-Vertex
                Vertex  v_1 = vertices.at(q.getV( pos_mod(j+1, 4))); // 'rechter' Eckpunkt-Vertex
                Vertex  v_e = Vertex::averageVertices(v_0, v_1); // Durchschnitt der angrenzenden Eckpunkt-Vertex

                Vertex  f_0 = vertices.at(q.getF()); // Eigener Face-Vertex
                Vertex  f_1 = vertices.at(neighbour.getF()); // Face-Vertex des Nachbarn
                Vertex  f_e = Vertex::averageVertices(f_0, f_1); // Durchschnitt der angrenzenden Face-Vertices

                Vertex  e = Vertex::averageVertices(v_e, f_e); // Durschnitt aus v_e und f_e

                // Vertex-Typ auf Edge-Mask setzen
                e.setType("e");

                // Edge-Mask in der Liste der Vertices speichern und Index zwischenspeichern
                vertices.push_back(e);
                size_t index = vertices.size() - 1;

                // Index der Edge-Mask an der entsprechenden Stelle im Quad speichern
                quads.at(i).setE(j, index);

            //Eigener Index größer . Edge-Mask von Nachbar übernehmen
            } else {

                // Alle Kanten des Nachbarn durchlaufen
                for(unsigned int k = 0; k < 4; k++){

                    // Prüfen, welche Kante geteilt wird
                    int comp = neighbour.getQ(k);
                    if( i == comp ){
                        // Index der Edge-Mask an der entsprechenden Stelle im Quad speichern
                        quads.at(i).setE(j, neighbour.getE(k));
                    }

                }

            }

        }

#ifdef DEBUG_VERBOSE
        cout << "Quad: " << i << " | Edge-Indizes: " << qTemp.getE(0) << "|" << qTemp.getE(1) << "|" << qTemp.getE(2) << "|" << qTemp.getE(3) << endl;
#endif
    }

    /* START: Berechne Vertex-Masks */

    // Jeden v-Vertex mal Valenz  (Valenz - 3) multiplizieren
    for(unsigned int i = 0; i < vertices.size(); i++){
        Vertex  v =  vertices.at(i);

        if(v.getType() == "v"){
            int n = v.getValence();
            v = Vertex::multiplyVertex(v, n * (n - 3) );
            vertices.at(i) = v;
        }
    }

    // Jeden v-Vertex jedes Quads mit den anliegenden e-Vertizes verrechnen und den f-Vertex abziehen
    for(unsigned int i = 0; i < quads.size(); i++){
        Quad  q =  quads.at(i);

        for(int j = 0; j < 4; j++){
            Vertex  v =  vertices.at(q.getQ(j));

            Vertex vA1 =  vertices.at(q.getE( pos_mod(j-1, 4)));
            Vertex vA2 =  vertices.at(q.getE( pos_mod(j,4)));

            vA1 = Vertex::multiplyVertex(vA1, 2.0);
            vA2 = Vertex::multiplyVertex(vA2, 2.0);

            v = Vertex::addVertices(v, vA1);
            v = Vertex::addVertices(v, vA2);
            v = Vertex::subtractVertices(v, vertices.at(q.getF()));

            vertices.at(q.getQ(j)) = v;
        }
    }

    // Jeden v-Vertex durch seine Valenz teilen
    for(unsigned int i = 0; i < vertices.size(); i++){
        Vertex  v =  vertices.at(i);

        if(v.getType() == "v"){
            int n = v.getValence();
            v = Vertex::divideVertex(v, n * n);
            vertices.at(i) = v;
        }

#ifdef DEBUG_VERBOSE
        cout << "Vertex: " << i << " . " << v.toString() << endl;
#endif
    }
    /* ENDE: Berechne Vertex-Masks */

    // Subdivision . Aus jedem Quad vier entsprechende machen
    vector<Quad > quadsTemp;
    for(unsigned int i = 0; i < quads.size(); i++){
        Quad  q = quads.at(i);

        for(int j = 0; j < 4; j++){
            Quad q_new = Quad(q.getV( pos_mod(j,4) ), q.getE( pos_mod(j,4) ), q.getF(), q.getE( pos_mod(j-1,4) ) );

            quadsTemp.push_back(q_new);
        }
    }

    quads = quadsTemp;

    calculateVertexValence();
    determineQuadNeighbours();

#ifdef DEBUG
    for(unsigned int i = 0; i < quads.size(); i++){
        cout << quads.at(i).toString() << endl;
    }
#endif

}

void OGLWidget::printToFile()
{
    ofstream outFile;

    outFile.open("output.obj");

    for(unsigned int i = 0; i < vertices.size(); i++){
        Vertex  v = vertices.at(i);
        outFile << "v" << " " << v.getX() << " " << v.getY() << " " << v.getZ() << " " << v.getValence() << endl;;
    }

    for(unsigned int i = 0; i < quads.size(); i++){
        Quad  q = quads.at(i);
        outFile << "f" << " " << q.getV(0) << " " << q.getV(1) << " " << q.getV(2) << " " << q.getV(3)
                << " " << q.getQ(0) << " " << q.getQ(1) << " " << q.getQ(2) << " " << q.getQ(3) << endl;
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
    //  https://www.ntu.edu.sg/home/ehchua/programming/opengl/CG_Examples.html

    initializeOpenGLFunctions();

    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL); //
    glShadeModel(GL_SMOOTH); //
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); //

    readSuccess = readData();

    if(readSuccess){
        calculateVertexValence();
        determineQuadNeighbours();
        ccSubdivision();
        //ccSubdivision();
        //ccSubdivision();
        printToFile();
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

