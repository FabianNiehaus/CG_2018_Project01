#include "cubesurface.h"

CubeSurface::CubeSurface(string filename)
{
    this->filename = filename;
}

void CubeSurface::performBlackMagic(int numOfSD)
{
    readData();

    if(readSuccess){
        calculateVertexValence();
        determineQuadNeighbours();
        for(int i = 0; i < numOfSD; i++){
            ccSubdivision();
        }
        //printToFile();
    }
}

vector<Vertex> CubeSurface::getVertices() const
{
    return vertices;
}

vector<Quad> CubeSurface::getQuads() const
{
    return quads;
}

vector<Quad> CubeSurface::getPreCCQuads() const
{
    return preCCQuads;
}

void CubeSurface::readData()
{
    ifstream file(filename.c_str());

    if(!file){
        cout << "error opening file" << endl;
    } else {
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
                if(file.eof()) break;
                file >> p1 >> p2 >> p3 >> p4;
                quads.push_back( Quad(p1-1, p2-1, p3-1, p4-1));
            }
        }

        file.close();

        cout << endl;
        cout << "[Cube] Objekt-Datei eingelesen!" << endl;

        readSuccess = true;
    }
}

// Immer positive Modulos: https://stackoverflow.com/questions/14997165/fastest-way-to-get-a-positive-modulo-in-c-c
inline int pos_mod(int i, int n) {
    return (i % n + n) % n;
}

void CubeSurface::calculateVertexValence()
{
    cout << endl;
    cout << "Bestimme Vertex-Valenzen" << endl;

    for(unsigned int i = 0; i < vertices.size(); i++)
    {
        //cout << "Vertex: " << i << endl;

        Vertex  v = vertices.at(i);
        int valence = 0;

        for(unsigned int j = 0; j < quads.size(); j++) {
            Quad  q = quads.at(j);

            //cout << "Quad: " << j << endl;

            for(int k = 0; k < 4; k++){
                if(q.getV(k) == i) valence++;
            }

        }

        vertices.at(i).setValence(valence);

#ifdef DEBUG_VERBOSE
        cout << "Vertex: " << i << " | Kanten: " << valence << endl;
#endif
    }
}



void CubeSurface::determineQuadNeighbours()
{
    cout << endl;
    cout << "Bestimme Nachbarn!" << endl;

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

        q = quads.at(i);
        int a = 1;
    }

#ifdef DEBUG_VERBOSE
    for(unsigned int i = 0; i < quads.size(); i++){
        cout << quads.at(i).toString() << endl;
    }
#endif

}

void CubeSurface::calculateFaceMasks(){
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

}

void CubeSurface::calculateEdgeMasks(){
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

                Vertex  f_0 = vertices.at(q.getF()); // Eigener Face-Vertex
                Vertex  f_1 = vertices.at(neighbour.getF()); // Face-Vertex des Nachbarn

                Vertex  e = Vertex::averageVertices(v_0, v_1, f_0, f_1); // Durschnitt aus v_e und f_e

                // Vertex-Typ auf Edge-Mask setzen
                e.setType("e");

                // Edge-Mask in der Liste der Vertices speichern und Index zwischenspeichern
                vertices.push_back(e);
                size_t index = vertices.size() - 1;

                // Index der Edge-Mask an der entsprechenden Stelle im Quad speichern
                quads.at(i).setE(j, index);

            //Eigener Index größer -> Edge-Mask von Nachbar übernehmen
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
}

void CubeSurface::calculateVertexMasks(){
    /* START: Berechne Vertex-Masks */

    // Jeden v-Vertex mal Valenz * (Valenz - 3) multiplizieren
    for(unsigned int i = 0; i < vertices.size(); i++){
        Vertex  v =  vertices.at(i);

        if(v.getType() == "v"){
            int n = v.getValence();
            vertices.at(i) = Vertex::multiplyVertex(v, n * (n - 3) );
        }
    }

    // Jeden v-Vertex jedes Quads mit den anliegenden e-Vertizes verrechnen und den f-Vertex abziehen
    for(unsigned int i = 0; i < quads.size(); i++){
        Quad q = quads.at(i);

        for(int j = 0; j < 4; j++){
            Vertex  v_in =  vertices.at(q.getV(j));

            int valence = v_in.getValence();

            Vertex vA1 =  vertices.at(q.getE( pos_mod(j-1, 4)));
            Vertex vA2 =  vertices.at(q.getE( pos_mod(j,4)));

            vA1 = Vertex::multiplyVertex(vA1, 2.0);
            vA2 = Vertex::multiplyVertex(vA2, 2.0);

            Vertex v_1 = Vertex::addVertices(v_in, vA1);
            Vertex v_2 = Vertex::addVertices(v_1, vA2);

            Vertex v_out = Vertex::subtractVertices(v_2, vertices.at(q.getF()));

            vertices.at(q.getV(j)) = v_out;
        }
    }

    // Jeden v-Vertex durch seine Valenz teilen
    for(unsigned int i = 0; i < vertices.size(); i++){
        Vertex  v =  vertices.at(i);

        if(v.getType() == "v"){
            int n = v.getValence();
            vertices.at(i) = Vertex::divideVertex(v, n * n);
        }

#ifdef DEBUG_VERBOSE
        cout << "Vertex: " << i << " . " << v.toString() << endl;
#endif
    }

    /* ENDE: Berechne Vertex-Masks */

}

void CubeSurface::subdivideAndReconnectMesh(){
    // Subdivision . Aus jedem Quad vier entsprechende machen
    vector<Quad > quadsTemp;
    for(unsigned int i = 0; i < quads.size(); i++){
        Quad q = quads.at(i);

        for(int j = 0; j < 4; j++){

            int v0 = q.getV( pos_mod(j,4) );
            int v1 = q.getE( pos_mod(j,4) );
            int v2 = q.getF();
            int v3 = q.getE( pos_mod(j-1,4) );

            vertices.at(v0).setType("v");
            vertices.at(v1).setType("v");
            vertices.at(v2).setType("v");
            vertices.at(v3).setType("v");

            Quad q_new = Quad(v0, v1, v2, v3);

            quadsTemp.push_back(q_new);
        }
    }

    quads = quadsTemp;

    calculateVertexValence();
    determineQuadNeighbours();
}

void CubeSurface::printQuads(bool postCC){
    cout << endl;
    cout << "Gebe Quads aus!" << endl;
    for(unsigned int i = 0; i < quads.size(); i++){
        Quad q = quads.at(i);

        cout << "##########" << endl;
        cout << "Quad: " << i << endl;
        cout << " -- " << endl;
        cout << "v0: " << q.getV(0) << " | " << vertices.at(q.getV(0)).toString() << endl;
        cout << "v1: " << q.getV(1) << " | " << vertices.at(q.getV(1)).toString() << endl;
        cout << "v2: " << q.getV(2) << " | " << vertices.at(q.getV(2)).toString() << endl;
        cout << "v3: " << q.getV(3) << " | " << vertices.at(q.getV(3)).toString() << endl;
        cout << " -- " << endl;

        if(postCC){
            cout << "f: " <<  q.getF() << " | " << vertices.at(q.getF()).toString() << endl;
            cout << " -- " << endl;
            cout << "e0: " << q.getE(0) << " | " << vertices.at(q.getE(0)).toString() << endl;
            cout << "e1: " << q.getE(1) << " | " << vertices.at(q.getE(1)).toString() << endl;
            cout << "e2: " << q.getE(2) << " | " << vertices.at(q.getE(2)).toString() << endl;
            cout << "e3: " << q.getE(3) << " | " << vertices.at(q.getE(3)).toString() << endl;
            cout << " -- " << endl;
        }

        cout << "q0: " << q.getQ(0) << endl;
        cout << "q1: " << q.getQ(1) << endl;
        cout << "q2: " << q.getQ(2) << endl;
        cout << "q3: " << q.getQ(3) << endl;
        cout << " -- " << endl;

    }

}

void CubeSurface::ccSubdivision()
{
    cout << endl;
    cout << "Starte Catmull-Clark-Subdivision!" <<endl;
    cout << endl;

    calculateFaceMasks();
    calculateEdgeMasks();
    calculateVertexMasks();
    //printQuads(true);
    subdivideAndReconnectMesh();
    //printQuads(false);
}

void CubeSurface::printToFile()
{
    ofstream outFile;

    outFile.open("output.obj");

    for(unsigned int i = 0; i < vertices.size(); i++){
        Vertex  v = vertices.at(i);
        outFile << "v" << " " << v.getX() << " " << v.getY() << " " << v.getZ() << " " << v.getValence() << endl;
    }

    for(unsigned int i = 0; i < quads.size(); i++){
        Quad  q = quads.at(i);
        outFile << "f" << " " << q.getV(0) << " " << q.getV(1) << " " << q.getV(2) << " " << q.getV(3)
                << " " << q.getQ(0) << " " << q.getQ(1) << " " << q.getQ(2) << " " << q.getQ(3) << endl;
    }

}
