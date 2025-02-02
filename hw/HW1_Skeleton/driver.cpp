/**
 * @file driver.cpp
 *  
 * Driver file that can be used to write test cases 
 * that test BST implementation.
 * Please don't submit this file.
 */

#include "bst.h"
#include <iostream>

int main() {
    // Dummy driver, use this main method to perform any testing 
    // you would like to do.

    Node node {nullptr, nullptr, {0u,0u}, 0u};

    Point points[5] {{1u,10u}, {3u,8u}, {5u,7u}, {7u,4u}, {9u,2u}};
    for(int i = 0; i < 5; i++) {
        std::cout << "(" << (int)(points[i].x) << "," << (int)(points[i].y) << ")" << "\n";
    }
    std::cout << "\n";
    std::cout << "(" << (int)node.p.x << "," << (int)node.p.y << ")" << "\n";
}