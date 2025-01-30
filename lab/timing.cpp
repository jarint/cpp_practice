/*
    timing.cpp by Robert Plantilla
    Code for printArray and selectionSort provided by Si Zhang
*/

#include <iostream>
#include <chrono>
#include <utility>
#include <functional>

using namespace std;

template <typename T>
void printArray(T arr[], int size) {
    for (int i=0; i<size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

template <typename T, typename Compare = less<T>>
void selectionSort(T arr[], int size, Compare comp = Compare()) {
    for(int i=0; i<size-1; i++) {
        int min = i;
        for(int j=i+1; j<size; j++){
            if(comp(arr[j], arr[min])) {
                min = j;
            }
        }
        if (min != i) {
            swap(arr[i], arr[min]);
        }
    }
}

int main() {

    srand(time(0));

    int iterations = 5;
    //double timing[iterations] {};

    // put the next block in a for loop with i < iterations iterations.

    int iArray[] = {60, 20, 10, 30, 50, 40};
    int iSize = sizeof(iArray) / sizeof(iArray[0]);
    
    cout << "Original integer array: ";
    printArray(iArray, iSize);

    const auto start{std::chrono::high_resolution_clock::now()};
    selectionSort(iArray, iSize);
    const auto end{std::chrono::high_resolution_clock::now()};

    const std::chrono::duration<double> elapsed_seconds{end - start};

    cout << "Sorted integer array: ";
    printArray(iArray, iSize);
    cout << endl;

    const chrono::duration<double, micro> elapsed_micro {end - start};
    cout << "elapsed time (microseconds): " << elapsed_micro.count() << endl;
    return 0;
}