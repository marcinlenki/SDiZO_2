#include <iostream>
#include "List.h"

using namespace std;

List::List() {
    this->listSize = 0;
    this->head = nullptr;
    this->tail = nullptr;
}

List::~List() {
    clear();
}

bool List::show() {
    if (isEmpty())
        return false;

    Edge* le = head;

    while (le != nullptr) {
        cout << "(" << le->destVertex << "," << le->edgeWeight << ")\t";
        le = le->next;
    }

    return true;
}

List::Edge *List::search(int destVer) {
    Edge *le = head;

    while (le != nullptr && le->destVertex != destVer) {
        le = le->next;
    }

    return le;
}

bool List::addEnd(int destVer, int edgeW) {
    Edge *le = new Edge;

    le->destVertex = destVer;
    le->edgeWeight = edgeW;
    le->prev = tail;
    le->next = nullptr;


    if (head != nullptr)
        tail->next = le;
    else
        head = le;

    tail = le;

    listSize++;

    return true;
}

bool List::removeEnd() {
    if(head != nullptr) {
        if(head->next != nullptr) {
            tail = tail->prev;
            deleteNode(tail->next);
            tail->next = nullptr;
        } else {
            deleteNode(head);
            head = nullptr;
            tail = nullptr;
        }

        listSize--;
        return true;
    }

    return false;
}

List::Edge *List::get(int index) {
    Edge *le = head;

    while (le != nullptr && index-- != 0) {
        le = le->next;
    }

    return le;
}

void List::clear() {
    Edge *le = head;
    Edge *nextNode;

    while(le != nullptr) {
        nextNode = le->next;
        deleteNode(le);
        listSize--;
        le = nextNode;
    }

    head = nullptr;
    tail = nullptr;
}

void List::deleteNode(Edge* le) {
    le->prev = nullptr;
    le->next = nullptr;
    delete le;
}

bool List::isEmpty() {
    return listSize == 0;
}