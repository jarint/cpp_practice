/**
 * @file bst.h
 * @brief A binary search tree for 2D points.
 *  
 * Declarations for a binary search tree (BST) that can store 2D points.
 * Morton codes are used as keys.
 * 
 */

#ifndef BST_H
#define BST_H

#include <cstdint>
#include <cstdlib>

// struct to hold 2D points
struct Point {
    uint8_t x;
    uint8_t y;
};

// A node in a BST
struct Node {
    Node* left; // pointer to left child
    Node* right; // pointer to right child
    Point p; // 2D point
    uint16_t key; // Morton code of 2D point
};

// Helper function to interleave with zeros
inline uint16_t interleave_with_zeros(uint8_t byte) {
    uint16_t result = byte;
    result = (result ^ (result << 4)) & 0x0F0F;
    result = (result ^ (result << 2)) & 0x3333;
    result = (result ^ (result << 1)) & 0x5555;
    return result;
}

// Returns the Morton code for a 2D point.
inline uint16_t code( const Point& p ) {    
    // Calculate and return Morton code by using 
    // the interleave_with_zeros() function.
    // Inline function,
    // YOUR CODE HERE 
    return 0u;
}

// Given the root node of a BST, inserts a 2D point.
// Performs any memory allocations needed. 
// Maintains the BST property.
//
// Returns true if the node is successfully added.
// Returns false if the point already exists in the BST.
bool insert( Node& root, const Point& p );

// Builds a BST from scrath from points provided in an array (of size N).
// The build should first sort the points and then
// add them to the BST in an order that would ensure that the resulting
// tree is balanced.
//
// Performs memory allocations that are needed.
//
// Returns pointer to the root node of the built tree.
Node* build( Point points[], size_t N);

// Searches for a point given the root node of a BST.
//
// Returns pointer to the node if found,
// or a nullptr if the node does not exist in the tree.
Node* search(const Node& root, const Point& p);

// Removes a node from a BST given the root node and the point
// corresponding to the node that is to be removed.
// Tree should maintain BST property after removal of node.
// To remove an interior node that has both children, copy from the 
// inorder successor from the right subtree, and remove the successor.
// 
// Peforms any memory deletions that may be needed.
//
// Returns true if the node is successfully removed,
// or false if the node does not exist in the tree.
bool remove( Node& root, const Point& p);

// Clear a tree given its root.
// Performs memory deletions that are needed.
void clear( Node& root );

// Returns the number of nodes in a BST given its root.
size_t size( const Node& root);

// Dumps points contained in a BST into the supplied array of size N, 
// where N is the total number of nodes in the BST.
// The dump should be performed via an inorder traversal of the BST.  
void dump( const Node& root, Point points[], size_t N );

#endif