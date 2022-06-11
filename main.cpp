#include <iostream>
using namespace std;

int *createArray(int);

int main() {
    int* arr = createArray(10);

    for (int i = 0; i < 10; i++)
        cout<<arr[i];


    delete [] arr;
    return 0;
}

int *createArray(int n) {
    int* newArr = new int[10];

    for (int i = 0; i < 10; i ++)
        newArr[i] = n;

    return newArr;
}
