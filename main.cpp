#include <iostream>
#include "AdjacencyList.h"

using namespace std;

const char * FILE_PATH = "/Users/marcinlenkiewicz/Desktop/Studia/SDiZO/Projekt_2/dane.txt";

int licz(int& liczba) {
    liczba = 10;

    return 20;
}

int main() {
    AdjacencyList* adjacencyList = new AdjacencyList;
    AdjacencyList* MST = new AdjacencyList;

    adjacencyList->makeFromFile(FILE_PATH, false);
//    adjacencyList->generateRandomGraph(6, 50);

//    adjacencyList->show();

    adjacencyList->primAdjacencyList(MST, 0);

    cout<<endl<<endl;

    MST->show();





    delete adjacencyList;
    delete MST;
    return 0;
}

