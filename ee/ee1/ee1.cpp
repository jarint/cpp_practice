/**
*
* Implementation for EE1
*
*
*
 */


#include <iostream>
#include <chrono>
#include <utility>
#include <functional>
#include <cstring>

#include "IntList.h"


using namespace std;


// Simple printing function for array
template <typename T>
void printArray(T arr[], int size) {
    for (int i=0; i<size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Selection Sort implementation
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

// LinkedList addToHead Method
void addToHead( List& list, int32_t data ) {
    // create a new link
    Link* link = new Link { nullptr, data };

    if ( list.size == 0 ) {
        // handle an empty list
        list.head = link;
    } else {
        // handle a non-empty list
        link->next = list.head;
        list.head = link; 
    }
    list.size++;
}

// LinkedList deleteFromHead Method
void deleteFromHead( List& list ) {
    if(list.size > 0) {
        if (list.size == 1) {
            delete list.head;
            list.head = nullptr; 
        } else {
            Link* ahead = list.head->next;
            delete list.head;
            list.head = ahead;
        }
        list.size--;
    }
}

// print Method for linked list
void print( const List& list ) {
    cout << "{";
    for( Link* link = list.head; link != nullptr; link = link->next ) {
        cout << link->data << ", ";
    }
    cout << "}" << endl;
}

int main() {
    srand(time(0));
    
    int k[] {5, 10, 15, 20, 25};

    int iterations = 5;
    double timing[iterations] {};
    for(int i=0; i<iterations; i++) {
        int iArray[10000] {};
        int iSize = sizeof(iArray) / sizeof(iArray[0]);
        for(int i = 0; i<iSize; i++)
        {
            iArray[i]=rand(); //% ((iSize + 1) * 10);
        }
        
        //cout << "Original integer array: ";
        //printArray(iArray, iSize);

        const auto t1 {chrono::high_resolution_clock::now()};
        selectionSort(iArray, iSize);
        const auto t2 {chrono::high_resolution_clock::now()};

        //cout << "Sorted integer array: ";
        //printArray(iArray, iSize);
        //cout << endl;

        const chrono::duration<double, micro> elapsed_micro {t2 - t1};
        timing[i] = elapsed_micro.count();
    }
    printArray(timing, iterations);


        List list {nullptr, 0};

    print( list );
    for(size_t i = 0; i < 10; i++) {
        addToHead( list, i );
        print( list );
    }

    cout << endl;

    for(size_t i = 0; i < 10; i++ ) {
        deleteFromHead( list );
        print( list ); 
    }

    return 0;







}