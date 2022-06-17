/*
 * Klasa implementująca działanie listy dwukierunkowej.
 * Stworzona podczas pierwszego projektu.
 * Klasa została lekko zmodyfikowana na potrzebę tego projektu.
 */
#ifndef PROJEKT_LISTA_H
#define PROJEKT_LISTA_H


class List {
public:
    struct Edge {
        int destVertex;
        int edgeWeight;
        Edge *prev, *next;
    };

    Edge *head, *tail;

    bool isEmpty();
    void deleteNode(Edge* le);


    unsigned int listSize;
    List();
    ~List();
    bool show();
    Edge* search(int destVer);
    bool addEnd(int destVer, int edgeW);
    bool removeEnd();
    Edge* get(int index);

    void clear();
};

#endif
