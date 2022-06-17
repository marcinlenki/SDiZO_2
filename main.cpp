#include <iostream>
#include <chrono>
#include "AdjacencyList.h"
#include "IncidenceMatrix.h"

using namespace std;

const char * FILE_PATH = "/Users/marcinlenkiewicz/Desktop/Studia/SDiZO/Projekt_2/dane.txt";
IncidenceMatrix* incidenceMatrix;
AdjacencyList* adjacencyList;

IncidenceMatrix* MST_matrix;
AdjacencyList* MST_list;

void mainMenu()
{
    cout<<endl;
    cout<<"1. Problem MST"<<endl;
    cout<<"2. Problem najkrótszej drogi w grafie"<<endl;
    cout<<"3. Wyjście z programu"<<endl;
    cout<<"Wybór: ";
}

void menuStructs()
{
    cout<<endl;
    cout<<"1. Macierz incydencji"<<endl;
    cout<<"2. Lista sąsiedztwa"<<endl;
    cout<<"3. Zmień rozpatrywany problem"<<endl;
    cout<<"Wybór: ";
}

void menuMST()
{
    cout<<endl;
    cout<<"1. Wczytaj dane z pliku"<<endl;
    cout<<"2. Wygeneruj graf losowo"<<endl;
    cout<<"3. Wyświetl graf na ekranie"<<endl;
    cout<<"4. Algorytm Prima"<<endl;
    cout<<"5. Algorytm Kruskala"<<endl;
    cout<<"6. Zmień reprezentację grafu"<<endl;
    cout<<"Wybór: ";
}

void menuNSWG()
{
    cout<<endl;
    cout<<"1. Wczytaj dane z pliku"<<endl;
    cout<<"2. Wygeneruj graf losowo"<<endl;
    cout<<"3. Wyświetl graf na ekranie"<<endl;
    cout<<"4. Algorytm Dijkstry"<<endl;
    cout<<"5. Algorytm Forda-Bellmana"<<endl;
    cout<<"6. Zmień reprezentację grafu"<<endl;
    cout<<"Wybór: ";
}


int main() {
    bool quit = false, changeProblem = false, changeStruct = false;
    int choiceProblem, choiceStruct, choiceOptions, verticesNum = 0, density = 0, MST;


//                          PROCEDURA MIERZENIA CZASU

//    adjacencyList = new AdjacencyList();
//    incidenceMatrix = new IncidenceMatrix();
//    MST_list = new AdjacencyList();
//    MST_matrix = new IncidenceMatrix();
//
//
//    int vertices [5]{10,15,25,50, 100};
//    int densityT;
//    long long sum;
//
//    for(int vN = 0; vN < 5; vN++) {
//        cout << "POMIAR " << vN << endl << endl;
//        // POMIAR 1
//        densityT = 25;
//        sum = 0;
//        for (int i = 0; i < 100; i++) {
//            incidenceMatrix->generateRandomGraph(vertices[vN], densityT, false);
//            // Start measuring time
//            auto begin = std::chrono::high_resolution_clock::now();
//
//            incidenceMatrix->kruskalIncidenceMatrix(MST_matrix);
//
//            // Stop measuring time and calculate the elapsed time
//            auto end = std::chrono::high_resolution_clock::now();
//            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
//            sum += elapsed.count();
//        }
//        cout << "Czas w ns dla liczby wierzchołków = " << vertices[vN] << " i gęstości = " << densityT << ":  " << sum / 100
//             << endl;
//
//        // POMIAR 2
//        densityT = 50;
//        sum = 0;
//        for (int i = 0; i < 100; i++) {
//            incidenceMatrix->generateRandomGraph(vertices[vN], densityT, false);
//            // Start measuring time
//            auto begin = std::chrono::high_resolution_clock::now();
//
//            incidenceMatrix->kruskalIncidenceMatrix(MST_matrix);
//
//            // Stop measuring time and calculate the elapsed time
//            auto end = std::chrono::high_resolution_clock::now();
//            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
//            sum += elapsed.count();
//        }
//        cout << "Czas w ns dla liczby wierzchołków = " << vertices[vN] << " i gęstości = " << densityT << ":  " << sum / 100
//             << endl;
//
//
//        // POMIAR 3
//        densityT = 75;
//        sum = 0;
//        for (int i = 0; i < 100; i++) {
//            incidenceMatrix->generateRandomGraph(vertices[vN], densityT, false);
//            // Start measuring time
//            auto begin = std::chrono::high_resolution_clock::now();
//
//            incidenceMatrix->kruskalIncidenceMatrix(MST_matrix);
//
//            // Stop measuring time and calculate the elapsed time
//            auto end = std::chrono::high_resolution_clock::now();
//            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
//            sum += elapsed.count();
//        }
//        cout << "Czas w ns dla liczby wierzchołków = " << vertices[vN] << " i gęstości = " << densityT << ":  " << sum / 100
//             << endl;
//
//
//        // POMIAR 4
//        densityT = 99;
//        sum = 0;
//        for (int i = 0; i < 100; i++) {
//            incidenceMatrix->generateRandomGraph(vertices[vN], densityT, false);
//            // Start measuring time
//            auto begin = std::chrono::high_resolution_clock::now();
//
//            incidenceMatrix->kruskalIncidenceMatrix(MST_matrix);
//
//            // Stop measuring time and calculate the elapsed time
//            auto end = std::chrono::high_resolution_clock::now();
//            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
//            sum += elapsed.count();
//        }
//        cout << "Czas w ns dla liczby wierzchołków = " << vertices[vN] << " i gęstości = " << densityT << ":  " << sum / 100
//             << endl;
//
//        cout<<endl<<endl;
//    }
//
//    delete MST_matrix;
//    delete MST_list;
//    delete incidenceMatrix;
//    delete adjacencyList;


    while(!quit) {
        mainMenu();
        cin >> choiceProblem;
        cin.clear();
        cin.ignore(10000, '\n');
        switch (choiceProblem) {
            case 1:
                changeProblem = false;
                while (!changeProblem) {
                    menuStructs();
                    cin >> choiceStruct;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    switch (choiceStruct) {
                        case 1:
                            changeStruct = false;
                            incidenceMatrix = new IncidenceMatrix();
                            MST_matrix = new IncidenceMatrix();
                            while(!changeStruct) {
                                menuMST();
                                cin >> choiceOptions;
                                cin.clear();
                                cin.ignore(10000, '\n');
                                switch (choiceOptions) {
                                    case 1:
                                        incidenceMatrix->makeFromFile(FILE_PATH, false);
                                        break;
                                    case 2:
                                        cout << "Podaj liczbę krawędzi grafu do wygenerowania: ";
                                        cin >> verticesNum;
                                        cin.clear();
                                        cin.ignore(10000, '\n');
                                        cout << "Podaj gęstość grafu do wygenerowania: ";
                                        cin >> density;
                                        cin.clear();
                                        cin.ignore(10000, '\n');
                                        incidenceMatrix->generateRandomGraph(verticesNum, density, false);
                                        break;
                                    case 3:
                                        cout << endl << endl;
                                        incidenceMatrix->show();
                                        cout << endl << endl;
                                        break;
                                    case 4:
                                        cout << "Podaj wierzchołek początkowy: ";
                                        cin >> verticesNum;
                                        cin.clear();
                                        cin.ignore(10000, '\n');
                                        MST = incidenceMatrix->primIncidenceMatrix(MST_matrix, verticesNum);
                                        if (MST == -1)
                                            cout << "Podano nieprawidłowy wierzchołek!" << endl;
                                        else {
                                            cout << endl << endl;
                                            MST_matrix->show();
                                            cout << endl << endl;
                                            cout << "MST = " << MST << endl;
                                        }
                                        break;
                                    case 5:
                                        MST = incidenceMatrix->kruskalIncidenceMatrix(MST_matrix);
                                        cout << endl << endl;
                                        MST_matrix->show();
                                        cout << endl << endl;
                                        cout << "MST = " << MST << endl;
                                        break;
                                    case 6:
                                        changeStruct = true;
                                        delete incidenceMatrix;
                                        delete MST_matrix;
                                        break;
                                    default:
                                        cout<<"Wybrano niewłaściwą opcję."<<endl;
                                        break;
                                }
                            }
                            break;
                        case 2:
                            changeStruct = false;
                            adjacencyList = new AdjacencyList();
                            MST_list = new AdjacencyList;
                            while(!changeStruct) {
                                menuMST();
                                cin >> choiceOptions;
                                cin.clear();
                                cin.ignore(10000, '\n');
                                switch (choiceOptions) {
                                    case 1:
                                        adjacencyList->makeFromFile(FILE_PATH, false);
                                        break;
                                    case 2:
                                        cout << "Podaj liczbę krawędzi grafu do wygenerowania: ";
                                        cin >> verticesNum;
                                        cin.clear();
                                        cin.ignore(10000, '\n');
                                        cout << "Podaj gęstość grafu do wygenerowania: ";
                                        cin >> density;
                                        cin.clear();
                                        cin.ignore(10000, '\n');
                                        adjacencyList->generateRandomGraph(verticesNum, density, false);
                                        break;
                                    case 3:
                                        cout << endl << endl;
                                        adjacencyList->show();
                                        cout << endl << endl;
                                        break;
                                    case 4:
                                        cout << "Podaj wierzchołek początkowy: ";
                                        cin >> verticesNum;
                                        cin.clear();
                                        cin.ignore(10000, '\n');
                                        MST = adjacencyList->primAdjacencyList(MST_list, verticesNum);
                                        if (MST == -1)
                                            cout << "Podano nieprawidłowy wierzchołek!" << endl;
                                        else {
                                            cout << endl << endl;
                                            MST_list->show();
                                            cout << endl << endl;
                                            cout << "MST = " << MST << endl;
                                        }
                                        break;
                                    case 5:
                                        MST = adjacencyList->kruskalAdjacencyList(MST_list);
                                        cout << endl << endl;
                                        MST_list->show();
                                        cout << endl << endl;
                                        cout << "MST = " << MST << endl;
                                        break;
                                    case 6:
                                        changeStruct = true;
                                        delete adjacencyList;
                                        delete MST_list;
                                        break;
                                    default:
                                        cout<<"Wybrano niewłaściwą opcję."<<endl;
                                        break;
                                }
                            }
                            break;
                        case 3:
                            changeProblem = true;
                            break;

                        default:
                            cout<<"Wybrano niewłaściwą opcję."<<endl;
                            break;
                    }
                }
                break;

            case 2:
                changeProblem = false;
                while(!changeProblem) {
                    menuStructs();
                    cin >> choiceStruct;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    switch (choiceStruct) {
                        case 1:
                            changeStruct = false;
                            incidenceMatrix = new IncidenceMatrix();
                            MST_matrix = new IncidenceMatrix();
                            while (!changeStruct) {
                                menuNSWG();
                                cin >> choiceOptions;
                                cin.clear();
                                cin.ignore(10000, '\n');
                                switch (choiceOptions) {
                                    case 1:
                                        incidenceMatrix->makeFromFile(FILE_PATH, true);
                                        break;
                                    case 2:
                                        cout << "Podaj liczbę krawędzi grafu do wygenerowania: ";
                                        cin >> verticesNum;
                                        cin.clear();
                                        cin.ignore(10000, '\n');
                                        cout << "Podaj gęstość grafu do wygenerowania: ";
                                        cin >> density;
                                        cin.clear();
                                        cin.ignore(10000, '\n');
                                        incidenceMatrix->generateRandomGraph(verticesNum, density, true);
                                        break;
                                    case 3:
                                        cout << endl << endl;
                                        incidenceMatrix->show();
                                        cout << endl << endl;
                                        break;
                                    case 4:
                                        cout << "Podaj wierzchołek początkowy: ";
                                        cin >> verticesNum;
                                        cin.clear();
                                        cin.ignore(10000, '\n');
                                        if(!incidenceMatrix->djikstraIncidenceMatrix(verticesNum))
                                            cout << "Podano nieprawidłowy wierzchołek!" << endl;
                                        break;
                                    case 5:
                                        cout << "Podaj wierzchołek początkowy: ";
                                        cin >> verticesNum;
                                        cin.clear();
                                        cin.ignore(10000, '\n');
                                        if(!incidenceMatrix->bellmanFordIncidenceMatrix(verticesNum))
                                            cout << "Podano nieprawidłowy wierzchołek!" << endl;
                                        break;
                                    case 6:
                                        changeStruct = true;
                                        delete incidenceMatrix;
                                        delete MST_matrix;
                                        break;
                                    default:
                                        cout << "Wybrano niewłaściwą opcję." << endl;
                                        break;
                                }
                            }
                            break;
                        case 2:
                            changeStruct = false;
                            adjacencyList = new AdjacencyList();
                            MST_list = new AdjacencyList;
                            while (!changeStruct) {
                                menuMST();
                                cin >> choiceOptions;
                                cin.clear();
                                cin.ignore(10000, '\n');
                                switch (choiceOptions) {
                                    case 1:
                                        adjacencyList->makeFromFile(FILE_PATH, true);
                                        break;
                                    case 2:
                                        cout << "Podaj liczbę krawędzi grafu do wygenerowania: ";
                                        cin >> verticesNum;
                                        cin.clear();
                                        cin.ignore(10000, '\n');
                                        cout << "Podaj gęstość grafu do wygenerowania: ";
                                        cin >> density;
                                        cin.clear();
                                        cin.ignore(10000, '\n');
                                        adjacencyList->generateRandomGraph(verticesNum, density, true);
                                        break;
                                    case 3:
                                        cout << endl << endl;
                                        adjacencyList->show();
                                        cout << endl << endl;
                                        break;
                                    case 4:
                                        cout << "Podaj wierzchołek początkowy: ";
                                        cin >> verticesNum;
                                        cin.clear();
                                        cin.ignore(10000, '\n');
                                        if(!adjacencyList->djikstraAdjacencyList(verticesNum))
                                            cout << "Podano nieprawidłowy wierzchołek!" << endl;
                                        break;
                                    case 5:
                                        cout << "Podaj wierzchołek początkowy: ";
                                        cin >> verticesNum;
                                        cin.clear();
                                        cin.ignore(10000, '\n');
                                        if(!adjacencyList->bellmanFordAdjacencyList(verticesNum))
                                            cout << "Podano nieprawidłowy wierzchołek!" << endl;
                                        break;
                                    case 6:
                                        changeStruct = true;
                                        delete adjacencyList;
                                        delete MST_list;
                                        break;
                                    default:
                                        cout << "Wybrano niewłaściwą opcję." << endl;
                                        break;
                                }
                            }
                            break;
                        case 3:
                            changeProblem = true;
                            break;

                        default:
                            cout << "Wybrano niewłaściwą opcję." << endl;
                            break;
                    }
                }
                break;
            case 3:
                cout<<"Wychodzenie z programu..."<<endl;
                quit = true;
                break;

            default:
                cout << "Wybrano niewłaściwą opcję." << endl;
                break;
        }

    }

    return 0;
}