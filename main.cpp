#include <iostream>
#include "AdjacencyList.h"
#include "IncidenceMatrix.h"

using namespace std;

const char * FILE_PATH = "/Users/marcinlenkiewicz/Desktop/Studia/SDiZO/Projekt_2/dane.txt";


int main() {
    IncidenceMatrix* incidenceMatrix = new IncidenceMatrix();
    AdjacencyList* MST = new AdjacencyList();
    AdjacencyList* adjacencyList = new AdjacencyList();

//    incidenceMatrix->makeFromFile(FILE_PATH, false);
    adjacencyList->makeFromFile(FILE_PATH, false);

//    incidenceMatrix->show();
//    adjacencyList->show();

//    incidenceMatrix->primIncidenceMatrix(MST, 0);
    int m = adjacencyList->kruskalAdjacencyList(MST);

    cout<<m<<endl;

    MST->show();



    delete incidenceMatrix;
    delete adjacencyList;
    delete MST;
    return 0;
}

