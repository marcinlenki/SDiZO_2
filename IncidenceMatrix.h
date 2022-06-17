/*
 * Klasa reprezentująca graf w pamięci komputera za pomocą macierzy incydencji.
 * Większość funkcji w tej klasie ma takie samo zastosowanie i działanie jak odpowiadające funkcje
 * w klasie "AdjacencyList". Różnią się jedynie implementacją. W celu zapoznania się z opisami funkcji
 * należy przejść do pliku nagłówkowego "AdjacencyList.h".
 */

#ifndef PROJEKT_2_INCIDENCEMATRIX_H
#define PROJEKT_2_INCIDENCEMATRIX_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

const int MAX_WEIGHT_M = 20;
const int MAX_INT_M = 2147483626;

struct EdgeIncidenceMatrix {
    int destVertex;
    int srcVertex;
    int edgeWeight;

    EdgeIncidenceMatrix(int srcVertex, int destVertex, int edgeWeight);
    EdgeIncidenceMatrix() = default;
};

class IncidenceMatrix {
public:
    int verticesNum;
    int edgesNum;
    int** A;    // Alokowana dynamicznie macierz incydencji.

    // Pomocnicza funkcja służąca do sprawdzenia, czy między wierzchołkiem początkowym a
    // końcowym istnieje już połączenie.
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