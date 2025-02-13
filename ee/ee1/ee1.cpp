/**
*
* Implementation for EE1
* Author: Jarin Thundathil
*
 */

#include <iostream>
#include <chrono>
#include <utility>
#include <functional>
#include <cstring>
#include <vector>

#include "IntList.h"

using namespace std;


// LinkedList addToHead Method
void addToHead( List& list, int32_t data ) {
    Link* link = new Link { nullptr, data };
    
    if ( list.size == 0 ) {
        list.head = link;
    } else {
        link->next = list.head;
        list.head = link; 
    }
    list.size++;
}

// LinkedList deleteFromHead Method (Fixed)
void deleteFromHead( List& list ) {
    if(list.head != nullptr) {
        Link* temp = list.head;
        list.head = list.head->next;
        delete temp;
        list.size--;
    }
}


// Selection Sort for Linked List (Fixed)
void selectionSortLinkedList(List& list) {
    if (list.head == nullptr) return; // Avoid segmentation fault for empty list
    
    for (Link* i = list.head; i != nullptr; i = i->next) {
        Link* min = i;
        for (Link* j = i->next; j != nullptr; j = j->next) {
            if (j->data < min->data) {
                min = j;
            }
        }
        if (min != i) {
            swap(i->data, min->data);
        }
    }
}

// Selection Sort for Array
template <typename T, typename Compare = less<T>>
void selectionSortArray(T arr[], int size, Compare comp = Compare()) {
    for(int i=0; i<size-1; i++) {
        int min = i;
        for(int j = i + 1; j < size; j++){
            if(comp(arr[j], arr[min])) {
                min = j;
            }
        }
        if (min != i) {
            swap(arr[i], arr[min]);
        }
    }
}

// print Method for linked list
void printLinkedList( const List& list ) {
    cout << "{";
    for( Link* link = list.head; link != nullptr; link = link->next ) {
        cout << link->data << ", ";
    }
    cout << "}" << endl;
}

// Simple printing function for array
template <typename T>
void printArray(T arr[], int size) {
    for (int i=0; i<size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    srand(time(0));

    vector<int> input_sizes = {32, 1024, 32768, 1048576}; // 2^5, 2^10, 2^15, 2^20
    int num_runs[] = {100, 50, 5, 2};

    for (size_t idx = 0; idx < input_sizes.size(); idx++) {
        int n = input_sizes[idx];
        int runs = num_runs[idx];

        double array_time_total = 0;
        double linked_list_time_total = 0;

        int* arr = new int[n];
        List linkedList;
        memset(&linkedList, 0, sizeof(List));

        for (int r = 0; r < runs; r++) {
            vector<int> values(n);
            for (int &v : values) v = rand();

            // Copy values into array
            memcpy(arr, values.data(), n * sizeof(int));

            deleteFromHead(linkedList);  // Reset linked list
            for (int i = n - 1; i >= 0; i--) {  // Insert backwards
                addToHead(linkedList, values[i]);
            }

            // Time selection sort on array
            auto t1 = chrono::high_resolution_clock::now();
            selectionSortArray(arr, n);
            auto t2 = chrono::high_resolution_clock::now();
            array_time_total += chrono::duration<double, micro>(t2 - t1).count();

            // Time selection sort on linked list
            t1 = chrono::high_resolution_clock::now();
            selectionSortLinkedList(linkedList);
            t2 = chrono::high_resolution_clock::now();
            linked_list_time_total += chrono::duration<double, micro>(t2 - t1).count();

        }

        delete[] arr;
        deleteFromHead(linkedList);

        // cout
        cout << n << " " << (array_time_total / runs) << " " << (linked_list_time_total / runs) << endl;
    }

    return 0;
}