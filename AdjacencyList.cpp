#include "AdjacencyList.h"
using namespace std;

EdgeAdjacencyList::EdgeAdjacencyList(int srcVertex, int destVertex, int edgeWeight) {
    this->srcVertex = srcVertex;
    this->destVertex = destVertex;
    this->edgeWeight = edgeWeight;
}

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
    if (verticesNum == 0) {
        cout<<"Lista jest pusta."<<endl;
        return;
    }

    cout<<"Liczba wierzchołków: " << verticesNum << endl;
    cout<<"Liczba krawędzi: " << edgesNum << endl;


    for(int i = 0; i < verticesNum; i++) {
        cout<<"Wierzchołek " << i << ":\t";
        adj[i].show();
        cout<<endl;
    }

}

void AdjacencyList::generateRandomGraph(int vertices, int density, bool isDirected) {
    if(vertices <= 0 || density < 0) {
        cout<<"Wystąpił błąd, nie udało się stworzyć grafu."<<endl;
        return;
    }


    srand(time(nullptr));
    clear();
    verticesNum = vertices;
    adj = new List[verticesNum];

    // Wyliczenie krawędzi na podstawie liczby wierzchołków i gęstości.
    int edges = vertices * (vertices - 1);
    if(!isDirected)
        edges = edges / 2;

    edges = edges * ((double)density/100);
    edgesNum = edges;

    int randV, randV_dst,randW;

    // Zapewnienie spójności.
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

    // Generowanie pozostałych krawędzi.
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

bool AdjacencyList::djikstraAdjacencyList(int start) {
    if (start >= verticesNum)
        return false;

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
    return true;
}

bool AdjacencyList::bellmanFordAdjacencyList(int start) {
    if (start >= verticesNum)
        return false;

    int* d = new int[verticesNum];
    int* p = new int[verticesNum];

    // Zmienna logiczna służąca do przechowywania informacji czy podczas
    // wykonywania iteracji pętli zaszła jakaś zmiana w tablicach d i p.
    // Jeśli w pętli nie zaszła zmiana, można przerwać działanie pętli, przez co skracamy
    // czas działania.
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

                if(d[v] > d[j] + w) {
                    d[v] = d[j] + w;
                    p[v] = j;
                    changeOccurred = true;
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

int AdjacencyList::primAdjacencyList(AdjacencyList* &A, int start) {
    if (start >= verticesNum)
        return -1;

    A->verticesNum = verticesNum;
    A->edgesNum = verticesNum - 1;
    A->adj = new List[verticesNum];

    bool* alreadyVisited = new bool [verticesNum];
    int* keys = new int[verticesNum];
    int* p = new int[verticesNum];
    int visitedVerNum = 0, MST = 0, vSrc, vDst, W;

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

    for(int i = 0; i < verticesNum; i++) {
        MST += keys[i];
    }

    for(int i = 0; i < verticesNum; i++) {
        if(p[i] == - 1)
            continue;

        vSrc = i;
        vDst = p[i];
        W = keys[i];

        A->adj[vSrc].addEnd(vDst, W);
        A->adj[vDst].addEnd(vSrc, W);
    }

    delete [] alreadyVisited;
    delete [] keys;
    delete [] p;

    return MST;
}

int AdjacencyList::kruskalAdjacencyList(AdjacencyList *&MST_G) {
    MST_G->verticesNum = verticesNum;
    MST_G->edgesNum = verticesNum - 1;
    MST_G->adj = new List[verticesNum];

    int *groups = new int [verticesNum];
    auto** edges = new EdgeAdjacencyList * [edgesNum];
    int MST = 0, vSrc, vDst, w, eNum = 0;

    //MAKE-SET
    for(int i = 0; i < verticesNum; i++) {
        groups[i] = i;
    }

    for(int j = 0; j < verticesNum; j++) {
        for(int k = 0; k < adj[j].listSize; k++) {
            List::Edge* le = adj[j].get(k);
            vSrc = j;
            vDst = le->destVertex;
            w = le->edgeWeight;

            // Warunek zapewniający, że w grafie nieskierowanym dana krawędź zostanie dodane tylko raz.
            if(vSrc < vDst) {
                auto* e = new EdgeAdjacencyList(vSrc, vDst, w);
                edges[eNum++] = e;
            }
        }
    }

    // Sortowanie krawędzi po wadze.
    // Zastosowano sortowanie bąbelkowe.
    for(int i = 0; i < edgesNum; i++) {
        for(int j = 1; j < edgesNum - i; j++) {
            if(edges[j-1]->edgeWeight > edges[j]->edgeWeight) {
                swap(edges[j-1], edges[j]);
            }
        }
    }

    for(int i = 0; i < edgesNum; i++) {
        auto* e = edges[i];

        //FIND-SET(u) != FIND_SET(v)
        if(groups[e->srcVertex] != groups[e->destVertex]) {

            //Dodawanie krawędzi do MST_G
            MST_G->adj[e->srcVertex].addEnd(e->destVertex, e->edgeWeight);
            MST_G->adj[e->destVertex].addEnd(e->srcVertex, e->edgeWeight);
            MST += e->edgeWeight;

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

// Funkcja działa na zasadzie p[p[p[...p[v]]]].
void AdjacencyList::findPath(const int *arr, int vertex) {
    int p = arr[vertex];

    if (p != -1) {
        findPath(arr, p);
    }

    cout<<vertex<<" ";
}