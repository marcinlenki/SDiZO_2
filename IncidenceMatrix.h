#ifndef PROJEKT_2_INCIDENCEMATRIX_H
#define PROJEKT_2_INCIDENCEMATRIX_H

#include <iostream>
#include <fstream>
#include <algorithm>

const int MAX_WEIGHT_M = 200;
const int MAX_INT_M = 2147483626;

struct EdgeIncidenceMatrix {
    int destVertex;
    int srcVertex;
    int edgeWeight;

    EdgeIncidenceMatrix(int srcVertex, int destVertex, int edgeWeight);
    EdgeIncidenceMatrix() {};
};

class IncidenceMatrix {
public:
    int verticesNum;
    int edgesNum;
    int** A;
    int search(int srcVertex, int dstVertex);
    int findMin(const int* arr, const bool* visited, int length);
    void findPath(const int* arr, int vertex);

public:
    IncidenceMatrix();
    ~IncidenceMatrix();
    bool makeFromFile(const char *name, bool isDirected = true);
    void generateRandomGraph(int vertices, int density, bool isDirected = true);
    void clear();
    void show();
    bool djikstraIncidenceMatrix(int start);
    bool bellmanFordIncidenceMatrix(int start);
    int primIncidenceMatrix(IncidenceMatrix* &MST_G, int start);
    int kruskalIncidenceMatrix(IncidenceMatrix* &MST_G);
};


#endif
