/*
 * Klasa reprezentująca graf w pamięci komputera za pomocą listy sąsiedztwa.
 */

#ifndef PROJEKT_2_ADJACENCYLIST_H
#define PROJEKT_2_ADJACENCYLIST_H

#include "List.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

const int MAX_WEIGHT = 20;  // Maksymalna waga krawędzi  (zawsze dodatnia!)
const int MAX_INT = 2147483626;

// Pomocnicza struktura reprezentująca pojedynczą krawędź.
// Przechowuje wierzchołek początkowy, końcowy oraz wagę krawędzi.
// Struktura wykorzystywana w algorytmie Kruskala.
struct EdgeAdjacencyList {
    int destVertex;
    int srcVertex;
    int edgeWeight;

    EdgeAdjacencyList(int srcVertex, int destVertex, int edgeWeight);
    EdgeAdjacencyList() = default;
};

// Do implementacji listy użyto klasę List, stworzoną podczas poprzedniego projektu.
class AdjacencyList {
public:
    int verticesNum;
    int edgesNum;
    List* adj;  // Alokowana dynamicznie lista sąsiedztwa.

    // Funkcja zwracająca indeks minimalnej wartości w tablicy.
    // Nie uwzględnia wartości, które zostały wcześniej uznane za minimalne.
    // Funkcja ma za zadanie imitować działanie kopca typu MIN.
    int findMin(const int* arr, const bool* visited, int length);

    // Funkcja rekurencyjna, służąca do wyświetlenia najkrótszej ścieżki, po znalezieniu
    // wszystkich rodziców i dróg w algorytmach Dijkstry oraz Bellmana-Forda.
    void findPath(const int* arr, int vertex);

public:
    AdjacencyList();
    ~AdjacencyList();

    // Funkcja tworząca graf z pliku tekstowego.
    bool makeFromFile(const char* name, bool isDirected = true);

    // Funkcja generująca losowy skierowany lub nieskierowany graf.
    // Zapewnia spójność grafu przy warunku, że:
    // -> |E| >= |V| - 1 przy grafach nieskierowanych
    // -> |E| >= 2 * (|V| - 1) przy grafach skierowanych
    void generateRandomGraph(int vertices, int density, bool isDirected = true);

    void clear();
    void show();

    // Algorytmy znajdowania najkrótszej drogi w grafie.
    // Działają na spójnych, skierowanych grafach.
    // Do implementacji kolejki wykorzystują naiwną implementację z tablicą.
    bool djikstraAdjacencyList(int start);
    bool bellmanFordAdjacencyList(int start);

    // Algorytmy znajdowania minimalnego drzewa rozpinającego.
    // Działają na spójnych, nieskierowanych grafach.
    int primAdjacencyList(AdjacencyList* &A, int start);
    int kruskalAdjacencyList(AdjacencyList* &MST_G);
};

#endif