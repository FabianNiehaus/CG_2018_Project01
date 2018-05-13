#include "beziersurface.h"

// #define DEBUG
// #define DEBUG_VERBOSE

BezierSurface::BezierSurface(string filename)
{
    this->filename = filename;
}

vector<Quad> BezierSurface::getPreQuads(){
    return preBezierQuads;
}

vector<Quad> BezierSurface::getPostQuads(){
    return postBezierQuads;
}

void BezierSurface::readData()
{
    ifstream file(filename.c_str());

    if(!file){
        cout << "error opening file" << endl;
    } else {

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

        preBezierMat.setSize(rows, cols);

        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){

                float x = values.at(0).at(i).at(j);
                float y = values.at(1).at(i).at(j);
                float z = values.at(2).at(i).at(j);

                preBezierVertices.push_back(Vertex(x,y,z,"v"));
                preBezierMat.setAt(i,j, preBezierVertices.size()-1);
            }
        }

        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){

                preBezierQuads.push_back(
                            Quad(
                                preBezierMat.at(i,j),
                                preBezierMat.at(i,j+1),
                                preBezierMat.at(i+1,j+1),
                                preBezierMat.at(i+1,j)
                                ));
            }
        }

        cout << "[Bezier] Objekt-Datei eingelesen!" << endl;
        readSuccess = true;
    }
}

void BezierSurface::calculateBezier()
{
    readData();

    if(readSuccess){
        postBezierMat.setSize(steps+1, steps+1);

        for(float s = 0.0; s < (1.0 + 1.0 / steps); s += 1.0 / steps){
            for(float t = 0.0; t < (1.0 + 1.0 / steps); t += 1.0 / steps){

                Vertex v = Vertex(0.0f,0.0f,0.0f,"v");

                for(int i = 0; i <= m; i++){
                    for(int j = 0; j <= n; j++){

                        Vertex vIn = Vertex(preBezierVertices.at(preBezierMat.at(i,j)));

                        Vertex vTemp = Vertex::multiplyVertex(vIn, bernstein(m,i,s) * bernstein(n,j,t));

                        v = Vertex::addVertices(v, vTemp);

    #ifdef DEBUG_VERBOSE
        cout << "Bezier: " << s << " " << t << " " << i << " " << j << " vIn: " << vIn.toString() << " vTemp: " << vTemp.toString() << " Res: " << v.toString() << endl;
    #endif
                    }
                }

    #ifdef DEBUG_VERBOSE
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

}

vector<Vertex> BezierSurface::getPreBezierVertices() const
{
    return preBezierVertices;
}

vector<Vertex> BezierSurface::getPostBezierVertices() const
{
    return postBezierVertices;
}

float BezierSurface::bernstein(int n, int i, float s)
{
    float bernstein = 0.0;

    bernstein = nChooseK(n,i);
    bernstein *= pow(s,i);
    bernstein *= pow(1.0-s, n-i);

#ifdef DEBUG_VERBOSE
    cout << "Bernst.: " << n << " " << i << " " << s << " Res:" << bernstein << endl;
#endif

    return bernstein;
}

float BezierSurface::nChooseK(int n, int k)
{

    if(k > n){
        return 0;
    }

    if(k == 0){
        return 1;
    }

    if(k > n/2){
        return nChooseK(n,n-k);
    }

    return n * nChooseK(n-1,k-1) / k;

}
