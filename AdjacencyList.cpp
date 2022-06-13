#include "AdjacencyList.h"
using namespace std;

AdjacencyList::AdjacencyList() {
    this->verticesNum = 0;
    this->edgesNum = 0;
    this->adj = nullptr;
}

AdjacencyList::~AdjacencyList() {
    clear();
}

bool AdjacencyList::makeFromFile(const char *name, bool isDirected) {
    int tempV, tempE, vSrc, vDst, w;
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
    adj = new List[verticesNum];

    while(inFile >> vSrc >> vDst >> w) {
        adj[vSrc].addEnd(vDst, w);

        if (!isDirected)
            adj[vDst].addEnd(vSrc, w);
    }

    if (inFile.eof()) {
        cout<<"Wczytywanie danych zakończone."<<endl;
    } else if(inFile.fail()) {
        cout<<"Wczytywanie danych przerwane, nie udało się wczytać pliku."<<endl;
    } else {
        cout<<"Wczytywanie danych przerwane."<<endl;
    }

    inFile.close();
    return true;
}

void AdjacencyList::clear() {
    for(int i = 0; i < verticesNum; i++)
        adj[i].clear();

    verticesNum = 0;
    edgesNum = 0;
    adj = nullptr;
}

void AdjacencyList::show() {
    cout<<"Liczba wierzchołków: " << verticesNum << endl;
    cout<<"Liczba krawędzi: " << edgesNum << endl;


    for(int i = 0; i < verticesNum; i++) {
        cout<<"Wierzchołek " << i << ":\t";
        adj[i].show();
        cout<<endl;
    }

}

void AdjacencyList::generateRandomGraph(int vertices, int density, bool isDirected) {
    srand(time(nullptr));
    clear();
    verticesNum = vertices;
    adj = new List[verticesNum];

    int edges = vertices * (vertices - 1);
    if(!isDirected)
        edges = edges / 2;

    edges = edges * ((double)density/100);
    edgesNum = edges;

    int randV, randV_dst,randW;

    for(int i = 1; i < vertices; i++) {
        randV = rand() % i;
        randW = rand() % MAX_WEIGHT + 1;
        adj[i].addEnd(randV, randW);

        if (isDirected) {
            randV = rand() % i;
            randW = rand() % MAX_WEIGHT + 1;
            edges--;
        }
        adj[randV].addEnd(i, randW);

        edges--;
    }
    cout<<"aaa"<<endl;
    int d = 1;
//    while(edges-- > 0) {
//        cout<<d++<<endl;
//        randW = rand() % MAX_WEIGHT + 1;
//        randV = rand() % vertices;      //src vertex
//        randV_dst = rand() % vertices;
//
//        while(randV_dst == randV)
//            randV_dst = rand() % vertices;
//
//        while(adj[randV].search(randV_dst) != nullptr) {
//            randV_dst = rand() % vertices;
//
//            while(randV_dst == randV)
//                randV_dst = rand() % vertices;
//
//        }
//        adj[randV].addEnd(randV_dst, randW);
//
//        if (!isDirected)
//            adj[randV_dst].addEnd(randV, randW);
//    }

    while(edges > 0) {
        randW = rand() % MAX_WEIGHT + 1;
        randV = rand() % vertices;      //src vertex
        randV_dst = rand() % vertices;

        if(randV_dst == randV)
            continue;

        if(adj[randV].search(randV_dst) != nullptr)
            continue;

        adj[randV].addEnd(randV_dst, randW);

        if (!isDirected)
            adj[randV_dst].addEnd(randV, randW);

        edges--;
    }
}

void AdjacencyList::djikstraAdjacencyList(int start) {
    bool* alreadyVisited = new bool [verticesNum];
    int* d = new int[verticesNum];
    int* p = new int[verticesNum];
    int visitedVerNum = 0;

    for(int i = 0; i < verticesNum; i++) {
        alreadyVisited[i] = false;
        d[i] = MAX_INT;
        p[i] = -1;
    }

    d[start] = 0;

    while(visitedVerNum != verticesNum) {
        int u = findMin(d, alreadyVisited, verticesNum);
        alreadyVisited[u] = true;
        visitedVerNum++;


        for(int i = 0; i < adj[u].listSize; i++) {
            List::Edge* e = adj[u].get(i);
            int v = e->destVertex;
            int w = e->edgeWeight;

                if(d[v] > d[u] + w) {
                    d[v] = d[u] + w;
                    p[v] = u;
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
}

bool AdjacencyList::bellmanFordAdjacencyList(int start) {
    int* d = new int[verticesNum];
    int* p = new int[verticesNum];
    bool changeOccurred = true;

    for(int i = 0; i < verticesNum; i++) {
        d[i] = MAX_INT;
        p[i] = -1;
    }

    d[start] = 0;


    for (int i = 0; i < verticesNum - 1 && changeOccurred; i++) {
        changeOccurred = false;
        for(int j = 0; j < verticesNum; j++) {
            for(int k = 0; k < adj[j].listSize; k++) {
                List::Edge* e = adj[j].get(k);
                int v = e->destVertex;
                int w = e->edgeWeight;

//                cout<<"v = "<<v<<", w = "<<w<<endl;
//                cout<<"d[v]: "<< d[v] << ",\t d[j] + w: " << d[j] << " + " << w <<endl;

                if(d[v] > d[j] + w) {
//                    cout<<"warunek spelniony"<<endl;
                    d[v] = d[j] + w;
                    p[v] = j;
                    changeOccurred = true;
                }
            }
        }
    }

//    for(int i = 0; i < verticesNum; i++)
//        cout<<d[i]<<endl;
//
//    for(int i = 0; i < verticesNum; i++)
//        cout<<p[i]<<endl;

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

int AdjacencyList::findMin(const int *arr, const bool* visited, int length) {
    int min = MAX_INT, minVertexNum;

    for(int i = 0; i < length; i++) {
        if(arr[i] < min && !visited[i]) {
            min = arr[i];
            minVertexNum = i;
        }
    }

    return minVertexNum;
}

void AdjacencyList::findPath(const int *arr, int vertex) {
    int p = arr[vertex];

    if (p != -1) {
        findPath(arr, p);
    }

    cout<<vertex<<" ";
}


int AdjacencyList::primAdjacencyList(AdjacencyList* &A, int start) {
    A->verticesNum = verticesNum;
    A->edgesNum = verticesNum - 1;
    A->adj = new List[verticesNum];

    bool* alreadyVisited = new bool [verticesNum];
    int* keys = new int[verticesNum];
    int* p = new int[verticesNum];
    int visitedVerNum = 0, MST = 0, vSrc, vDst, w;

    for(int i = 0; i < verticesNum; i++) {
        alreadyVisited[i] = false;
        keys[i] = MAX_INT;
        p[i] = -1;
    }

    keys[start] = 0;

    while(visitedVerNum != verticesNum) {
        int u = findMin(keys, alreadyVisited, verticesNum);
        alreadyVisited[u] = true;
        visitedVerNum++;

        for(int i = 0; i < adj[u].listSize; i++) {
            List::Edge* e = adj[u].get(i);
            int v = e->destVertex;
            int w = e->edgeWeight;

            if(!alreadyVisited[v] && w < keys[v]) {
                keys[v] = w;
                p[v] = u;
            }
        }
    }

    for(int i = 1; i < verticesNum; i++) {
        vSrc = i;
        vDst = p[i];
        w = keys[i];

        A->adj[vSrc].addEnd(vDst, w);
        A->adj[vDst].addEnd(vSrc, w);
    }

    delete [] alreadyVisited;
    delete [] keys;
    delete [] p;

    return MST;
}
