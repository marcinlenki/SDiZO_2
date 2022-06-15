#include "IncidenceMatrix.h"
using namespace std;

EdgeIncidenceMatrix::EdgeIncidenceMatrix(int srcVertex, int destVertex, int edgeWeight) {
    this->srcVertex = srcVertex;
    this->destVertex = destVertex;
    this->edgeWeight = edgeWeight;
}

IncidenceMatrix::IncidenceMatrix() {
    verticesNum = 0;
    edgesNum = 0;
    A = nullptr;
}

IncidenceMatrix::~IncidenceMatrix() {
    clear();
}

bool IncidenceMatrix::makeFromFile(const char *name, bool isDirected) {
    int tempV, tempE, vSrc, vDst, w, count = 0;
    ifstream inFile;
    inFile.open(name);

    if (!inFile.is_open()) {
        cout<<"Plik nie istnieje."<<endl;
        return false;
    }

    clear();

    inFile >> tempE >> tempV;
    if (tempV <= 0 || tempE <= 0) {
        cout<<"W pliku wykryto blednę dane."<<endl;
        return false;
    }

    edgesNum = tempE;
    verticesNum = tempV;
    A = new int * [verticesNum];
    for(int i = 0; i < verticesNum; i++) {
        A[i] = new int[edgesNum]{};
    }

    while(inFile >> vSrc >> vDst >> w) {
        A[vSrc][count] = w;
        A[vDst][count] = isDirected ? -w : w;
        count++;
    }

    return false;
}

void IncidenceMatrix::clear() {
    for(int i = 0; i < verticesNum; i++) {
        for(int j = 0; j < edgesNum; j++) {
            A[i][j] = 0;
        }

        delete [] A[i];
    }

    verticesNum = 0;
    edgesNum = 0;
    delete [] A;
}

void IncidenceMatrix::show() {
//    int vSrc = -1, vDst = 0, w;
//
//    if (verticesNum == 0) {
//        cout<<"Lista jest pusta."<<endl;
//        return;
//    }
//
//    cout<<"Liczba wierzchołków: " << verticesNum << endl;
//    cout<<"Liczba krawędzi: " << edgesNum << endl;
//
//    for(int i = 0; i < verticesNum; i++) {
//        cout<<"Wierzchołek " << i << ":\t";
//        for(int j = 0; j < edgesNum; j++) {
//            for(int k = 0; k < verticesNum; k++) {
//                if(A[k][j] > 0 && k == i) {
//                    vSrc = k;
//                    w = A[k][j];
//                } else if(A[k][j] != 0) {
//                    vDst = k;
//                }
//            }
//            if (vSrc != -1) {
//                cout << "(" << vDst << "," << w << ")\t";
//            }
//            vSrc = -1;
//        }
//
//        cout<<endl;
//    }

    if(A == nullptr) {
        cout<<"Graf jest pusty."<<endl;
        return;
    }

    cout<<"            " << " " << " \t";
    for(int i = 0; i < edgesNum; i ++) {
        cout<<" "<<i<<"  \t";
    }
    cout<<endl<<endl;

    for(int i = 0; i < verticesNum; i ++) {
        cout<<"Wierzchołek " << i << ":\t";
        for(int j = 0; j < edgesNum; j++) {
            if(A[i][j] < 0)
                cout<<A[i][j]<<"  \t";
            else
                cout<<" "<<A[i][j]<<"  \t";
        }
        cout<<endl;
    }
}

void IncidenceMatrix::generateRandomGraph(int vertices, int density, bool isDirected) {
    if(vertices <= 0 || density < 0) {
        cout<<"Wystąpił błąd, nie udało się stworzyć grafu."<<endl;
        return;
    }

    srand(time(nullptr));
    clear();

    int edges = vertices * (vertices - 1);
    if(!isDirected)
        edges = edges / 2;

    edges = edges * ((double)density/100);

    verticesNum = vertices;
    edgesNum = edges;
    A = new int * [verticesNum];
    for(int i = 0; i < verticesNum; i++) {
        A[i] = new int[edgesNum]{};
    }

    int randV, randV_dst,randW, eNum = 0;
    for(int i = 1; i < vertices; i++) {
        randV = rand() % i;
        randW = rand() % MAX_WEIGHT_M + 1;

        if (!isDirected) {
            A[i][eNum] = randW;
            A[randV][eNum] = randW;
            eNum++;
            edges--;
        } else {
            A[i][eNum] = randW;
            A[randV][eNum] = -randW;
            eNum++;
            edges--;

            randV = rand() % i;
            randW = rand() % MAX_WEIGHT_M + 1;

            A[i][eNum] = -randW;
            A[randV][eNum] = randW;
            eNum++;
            edges--;
        }
    }


    while(edges > 0) {
        randW = rand() % MAX_WEIGHT_M + 1;
        randV = rand() % vertices;      //src vertex
        randV_dst = rand() % vertices;

        if(randV_dst == randV)
            continue;

        if(search(randV, randV_dst) == -1)
            continue;

        A[randV][eNum] = randW;

        if (!isDirected)
            A[randV_dst][eNum] = randW;
        else
            A[randV_dst][eNum] = -randW;


        edges--;
        eNum++;
    }
}

bool IncidenceMatrix::djikstraIncidenceMatrix(int start) {
    if (start >= verticesNum)
        return false;

    bool* alreadyVisited = new bool [verticesNum];
    int* d = new int[verticesNum];
    int* p = new int[verticesNum];
    int visitedVerNum = 0;

    for(int i = 0; i < verticesNum; i++) {
        alreadyVisited[i] = false;
        d[i] = MAX_INT_M;
        p[i] = -1;
    }

    d[start] = 0;

    while(visitedVerNum != verticesNum) {
        int v, w;
        int u = findMin(d, alreadyVisited, verticesNum);
        alreadyVisited[u] = true;
        visitedVerNum++;


        for(int i = 0; i < edgesNum; i++) {
            if (A[u][i] > 0) {
                for(int j = 0; j < verticesNum; j++) {
                    if(A[j][i] != 0 && j != u) {
                        v = j;
                        w = - A[j][i];

                        if(d[v] > d[u] + w) {
                            d[v] = d[u] + w;
                            p[v] = u;
                        }
                    }
                }
            }
        }
    }


    cout<<"-----------------------------------------------------------"<<endl;
    cout<<"\t\t\t\tWierzchołek startowy: "<<start<<endl;
    cout<<"-----------------------------------------------------------"<<endl;
    cout<<"Wierzchołek\t\tKoszt ścieżki\t\tZnaleziona ścieżka"<<endl;
    for(int i = 0; i < verticesNum; i++) {
        if(i == start)
            continue;

        cout<<" \t"<<i<<"  \t\t\t\t"<<d[i]<<"\t\t\t\t";
        findPath(p, i);
        cout<<endl;
    }
    cout<<"-----------------------------------------------------------"<<endl;
    cout<<"-----------------------------------------------------------"<<endl;

    delete [] alreadyVisited;
    delete [] d;
    delete [] p;
    return true;
}

bool IncidenceMatrix::bellmanFordIncidenceMatrix(int start) {
    if (start >= verticesNum)
        return false;

    int* d = new int[verticesNum];
    int* p = new int[verticesNum];
    bool changeOccurred = true;

    for(int i = 0; i < verticesNum; i++) {
        d[i] = MAX_INT_M;
        p[i] = -1;
    }

    d[start] = 0;

    for (int i = 0; i < verticesNum - 1 && changeOccurred; i++) {
        changeOccurred = false;
        for(int j = 0; j < verticesNum; j++) {                     //j -> srcV
            for (int k = 0; k < edgesNum; k++) {                    //k -> edges counter
                if (A[j][k] > 0) {
                    for (int m = 0; m < verticesNum; m++) {
                        if (A[m][k] != 0 && m != j) {
                            int v = m;
                            int w = -A[m][k];

//                            if(p[start] != -1) {
//                                cout<<v<<" "<<j<<" "<<w<<endl;
//                            }

                            if (d[v] > d[j] + w) {
                                d[v] = d[j] + w;
                                p[v] = j;
                                changeOccurred = true;
                            }
                        }
                    }
                }
            }
        }
    }

    cout<<"-----------------------------------------------------------"<<endl;
    cout<<"\t\t\t\tWierzchołek startowy: "<<start<<endl;
    cout<<"-----------------------------------------------------------"<<endl;
    cout<<"Wierzchołek\t\tKoszt ścieżki\t\tZnaleziona ścieżka"<<endl;
    for(int i = 0; i < verticesNum; i++) {
        if(i == start)
            continue;

        cout<<" \t"<<i<<"  \t\t\t\t"<<d[i]<<"\t\t\t\t";
        findPath(p, i);
        cout<<endl;
    }
    cout<<"-----------------------------------------------------------"<<endl;
    cout<<"-----------------------------------------------------------"<<endl;

    delete [] d;
    delete [] p;
    return true;
}

int IncidenceMatrix::primIncidenceMatrix(IncidenceMatrix *&MST_G, int start) {
    if (start >= verticesNum)
        return -1;

    MST_G->verticesNum = verticesNum;
    MST_G->edgesNum = verticesNum - 1;
    MST_G->A = new int * [verticesNum];
    for(int i = 0; i < verticesNum; i++) {
        MST_G->A[i] = new int[verticesNum - 1]{};  // !
    }


    bool* alreadyVisited = new bool [verticesNum];
    int* keys = new int[verticesNum];
    int* p = new int[verticesNum];
    int visitedVerNum = 0, MST = 0, vSrc, vDst, W;

    for(int i = 0; i < verticesNum; i++) {
        alreadyVisited[i] = false;
        keys[i] = MAX_INT_M;
        p[i] = -1;
    }

    keys[start] = 0;

    while(visitedVerNum != verticesNum) {
        int u = findMin(keys, alreadyVisited, verticesNum);
        alreadyVisited[u] = true;
        visitedVerNum++;

        for(int i = 0; i < edgesNum; i++) {
            if (A[u][i] > 0) {
                for(int j = 0; j < verticesNum; j++) {
                    if(A[j][i] != 0 && j != u) {
                        int v = j;
                        int w = A[j][i];

                        if(!alreadyVisited[v] && w < keys[v]) {
                            keys[v] = w;
                            p[v] = u;
                        }
                    }
                }
            }
        }
    }

    for(int i = 0; i < verticesNum; i++) {
        MST += keys[i];
    }

    for(int i = 0, eNum = 0; i < verticesNum; i++) {
        if(p[i] == - 1)
            continue;

        vSrc = i;
        vDst = p[i];
        W = keys[i];

        MST_G->A[vSrc][eNum] = W;
        MST_G->A[vDst][eNum] = W;
        eNum++;
    }

    delete [] alreadyVisited;
    delete [] keys;
    delete [] p;

    return MST;
}

int IncidenceMatrix::kruskalIncidenceMatrix(IncidenceMatrix *&MST_G) {
    MST_G->verticesNum = verticesNum;
    MST_G->edgesNum = verticesNum - 1;
    MST_G->A = new int * [verticesNum];
    for(int i = 0; i < verticesNum; i++) {
        MST_G->A[i] = new int[verticesNum - 1]{}; // !
    }

    bool found = false;
    int *groups = new int [verticesNum];
    auto** edges = new EdgeIncidenceMatrix * [edgesNum];
    int MST = 0, vSrc, vDst, w;

    //MAKE-SET
    for(int i = 0; i < verticesNum; i++) {
        groups[i] = i;
    }

    for(int i = 0; i < edgesNum; i++) {
        for(int j = 0; j < verticesNum && !found; j++) {
            if (A[j][i] > 0) {
                for (int m = 0; m < verticesNum; m++) {
                    if (A[m][i] != 0 && m != j) {
                        vSrc = j;
                        vDst = m;
                        w = A[m][i];

                        auto* e = new EdgeIncidenceMatrix(vSrc, vDst, w);
                        edges[i] = e;
                        found = true;
                    }
                }
            }
        }
        found = false;
    }

    for(int i = 0; i < edgesNum; i++) {
        for(int j = 1; j < edgesNum - i; j++) {
            if(edges[j-1]->edgeWeight > edges[j]->edgeWeight) {
                swap(edges[j-1], edges[j]);
            }
        }
    }

//    for(int i = 0; i < edgesNum; i++)
//        cout<<edges[i]->destVertex<<edges[i]->srcVertex<<edges[i]->edgeWeight<<endl;

    int eNum = 0;

    for(int i = 0; i < edgesNum; i++) {
        auto* e = edges[i];

//        for(int j = 0; j < verticesNum; j++) {
//            cout<<groups[j]<<endl;
//        }
//        cout<<"src: "<<edges[i]->srcVertex<<", dst: "<<edges[i]->destVertex<<", w = "<<edges[i]->edgeWeight<<endl;


        //FIND-SET(u) != FIND_SET(v)
        if(groups[e->srcVertex] != groups[e->destVertex]) {
//            cout<<"warunek spełniony"<<endl<<endl;
            //Dodawanie krawędzi do MST_G
            MST_G->A[e->srcVertex][eNum] = e->edgeWeight;
            MST_G->A[e->destVertex][eNum++] = e->edgeWeight;
            MST += e->edgeWeight;


//            for(int j = 0; j < verticesNum; j++) {
//                if(groups[j] == groups[e->destVertex])
//                    groups[e->destVertex] = groups[e->srcVertex];
//            }
//
//            for(int j = 0; j < verticesNum; j++) {
//                if(groups[j] == e->destVertex)
//                    groups[j] = groups[e->srcVertex];
//            }

            //UNION (u, v)
            //u -> srcVertex
            //v -> destVertex
            int changeTo = e->srcVertex;
            int changeFrom = e->destVertex;
            int temp = groups[changeFrom];

            for(int j = 0; j < verticesNum; j++) {
                if(groups[j] == temp) {
                    groups[j] = groups[changeTo];
                }
            }
        }
    }


    for(int i = 0; i < edgesNum; i++) {
        delete edges[i];
    }

    delete [] edges;
    delete [] groups;
    return MST;
}

int IncidenceMatrix::search(int srcVertex, int dstVertex) {
    for(int i = 0; i < edgesNum; i++) {
        if(A[srcVertex][i] > 0 && A[dstVertex][i] != 0)
            return -1;
    }

    return 1;
}

int IncidenceMatrix::findMin(const int *arr, const bool *visited, int length) {
    int min = MAX_INT_M, minVertexNum;

    for(int i = 0; i < length; i++) {
        if(arr[i] < min && !visited[i]) {
            min = arr[i];
            minVertexNum = i;
        }
    }

    return minVertexNum;
}

void IncidenceMatrix::findPath(const int *arr, int vertex) {
    int p = arr[vertex];

    if (p != -1) {
        findPath(arr, p);
    }

    cout<<vertex<<" ";
}