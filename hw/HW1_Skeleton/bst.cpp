/**
 * @file bst.cpp
 * @brief A binary search tree for 2D points.
 *  
 * Implementation of BST operations.
 */

#include "bst.h"
#include <algorithm>


// Given the root node of a BST, insert a 2D point.
// Performs any memory allocations needed. 
// Maintains the BST property.
//
// Returns true if the node is successfully added.
// Returns false if the point already exists in the BST.
bool insert( Node& root, const Point& p ) {
    // YOUR CODE HERE
    return false;
}

// Builds a BST from scrath from points provided in an array (of size N).
// The build should first sort the points and then
// add them to the BST in an order that would ensure that the resulting
// tree is balanced.
//
// Performs memory allocations that are needed.
//
// Returns pointer to the root node of the built tree.
Node* build( Point points[], size_t N) {
    // First sort the points in place based on their Morton codes
    std::sort(points, points+N, 
        [](const Point& a, const Point& b) {
            return code(a) < code(b);
        }
    );
    
    // YOUR CODE HERE
    return nullptr;
}

// Searches for a point given the root node of a BST.
//
// Returns pointer to the node if found,
// or a nullptr if the node does not exist in the tree.
Node* search(const Node& root, const Point& p) {
    // YOUR CODE HERE
    return nullptr;
}

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
bool remove( Node& root, const Point& p) {
    // YOUR CODE HERE
    return false;
}

// Clear a tree given its root.
// Performs memory deletions that are needed.
void clear( Node& root ) {
    // YOUR CODE HERE
}

// Returns the number of nodes in a BST given its root.
size_t size( const Node& root) {
    // YOUR CODE HERE
    return 0;
}

// Dumps points contained in a BST into the supplied array of size N, 
// where N is the total number of nodes in the BST.
// The dump should be performed via an inorder traversal of the BST.  
void dump( const Node& root, Point points[], size_t N ){
    // YOUR CODE HERE
}
