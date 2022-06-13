#ifndef PROJEKT_2_ADJACENCYLIST_H
#define PROJEKT_2_ADJACENCYLIST_H

#include "List.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

const int MAX_WEIGHT = 20;
const int MAX_INT = 2147483626;

class AdjacencyList {
public:
    int verticesNum;
    int edgesNum;
    List* adj;

    int findMin(const int* arr, const bool* visited, int length);
    void findPath(const int* arr, int vertex);

public:
    AdjacencyList();
    ~AdjacencyList();
    bool makeFromFile(const char* name, bool isDirected = true);
    void generateRandomGraph(int vertices, int density, bool isDirected = true);
    void clear();
    void show();
    void djikstraAdjacencyList(int start);
    bool bellmanFordAdjacencyList(int start);
    int primAdjacencyList(AdjacencyList* &A, int start);
    int kruskalAdjacencyList(AdjacencyList* &A);
};

#endif