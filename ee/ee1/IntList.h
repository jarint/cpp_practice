/**
 * @file IntList.h
 * @brief A basic singly-linked list
 *  
 * Declarations for a singly-linked list accessible at the head.
 * 
 */

#ifndef INT_LIST_H
#define INT_LIST_H

#include <cstdint>
#include <cstdlib>

// A link for a basic singly-linked list
struct Link {
    Link* next;
    int32_t data;
};

// List is accessible at the head,
// keeps track of number of items.
struct List {
    Link* head; // pointer to head
    size_t size; //number of elements in list
};

// add link to the head of a potentially empty list.
void addToHead( List& list, int32_t data );

// delete link from the head of a potentially empty list.
void deleteFromHead( List& list );

// clear a list by deleting all its links
void clear( List& list );

// dump the contents of the list to stdout
void print( const List& list );



#endif