#include "bst.h"
#include <iostream>

void printTreeInOrder(const Node* root) {
    if (!root) return;
    printTreeInOrder(root->left);
    std::cout << "(" << (int)root->p.x << "," << (int)root->p.y << ") " << "Key: " << root->key << "\n";
    printTreeInOrder(root->right);
}

int main() {
    // Initialize an empty BST
    Node* root = nullptr;

    // Array of points to insert
    Point points[5] {{1u,10u}, {3u,8u}, {5u,7u}, {7u,4u}, {9u,2u}};
    
    // Insert points into BST
    for(int i = 0; i < 5; i++) {
        if (root == nullptr) {
            root = new Node{nullptr, nullptr, points[i], code(points[i])};
        } else {
            insert(*root, points[i]);
        }
    }
    
    // Print tree in order
    std::cout << "BST In-Order Traversal:\n";
    printTreeInOrder(root);
    std::cout << "\n";

    // Search for a point
    Point searchPoint {5u, 7u};
    const Node* found = search(*root, searchPoint);
    if (found) {
        std::cout << "Found point: (" << (int)found->p.x << "," << (int)found->p.y << ")\n";
    } else {
        std::cout << "Point not found!\n";
    }
    
    // Remove a point
    Point removePoint {3u, 8u};
    root = remove(root, removePoint);
    std::cout << "\nBST After Removing (3,8):\n";
    printTreeInOrder(root);

    // Get BST size
    std::cout << "\nBST Size: " << size(*root) << "\n";

    // Dump BST into an array
    Point dumpArray[5];
    size_t N = size(*root);
    dump(*root, dumpArray, N);
    std::cout << "\nDumped BST Points:\n";
    for (size_t i = 0; i < N; i++) {
        std::cout << "(" << (int)dumpArray[i].x << "," << (int)dumpArray[i].y << ")\n";
    }

    // Clear tree
    root = clear(root);
    std::cout << "\nBST Cleared. Root: " << (root == nullptr ? "nullptr" : "not null") << "\n";
    
    return 0;
}