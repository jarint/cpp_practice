#include "bst.h"
#include <algorithm>

bool insert(Node& root, const Point& p) {
    uint16_t p_key = code(p);
    Node* current_node = &root;

    while (true) {
        if (p_key < current_node->key) { 
            // traverse left subtree
            if (current_node->left) {
                current_node = current_node->left;
            } else { 
                // insert node left
                current_node->left = new Node{nullptr, nullptr, p, p_key};
                return true;
            }
        } else if (p_key > current_node->key) { 
            // traverse right subtree
            if (current_node->right) {
                current_node = current_node->right;
            } else { 
                // insert node right
                current_node->right = new Node{nullptr, nullptr, p, p_key};
                return true;
            }
        } else {
            return false; // Node exists
        }
    }
}

Node* build_helper(Point points[], size_t start, size_t end) {
    if (start >= end) {
        return nullptr; // no elements to add
    }
    
    size_t mid = start + (end - start) / 2; // Find middle
    Node* node = new Node{nullptr, nullptr, points[mid], code(points[mid])};

    node->left = build_helper(points, start, mid); // build left subtree
    node->right = build_helper(points, mid + 1, end); // build right subtree
    
    return node;
}

Node* build(Point points[], size_t n) {
    std::sort(points, points + n, [](const Point& a, const Point& b) { 
        return code(a) < code(b); 
    });

    return build_helper(points, 0, n);
}

const Node* search(const Node& root, const Point& p) {
    uint16_t p_key = code(p);
    const Node* current_node = &root;

    while (current_node) {
        if (p_key < current_node->key) {
            // move left
            current_node = current_node->left;
        } else if (p_key > current_node->key) {
            // move right
            current_node = current_node->right;
        } else {
            // node found
            return current_node;
        }
    }
    
    // node not found
    return nullptr;
}

Node* find_minimum_node(Node* root) {
    while (root && root->left) {
        // Move to leftmost node
        root = root->left;
    }
    
    return root;
}

Node* remove(Node* root, const Point& p) {
    if (!root) {
        // Base case: node not found
        return nullptr;
    }

    uint16_t p_key = code(p);

    if (p_key < root->key) {
        // Remove from left subtree
        Node* new_left_node = remove(root->left, p);
        if (new_left_node) {
            root->left = new_left_node;
        }
    } else if (p_key > root->key) {
        // Remove from right subtree
        Node* new_right_node = remove(root->right, p);
        if (new_right_node) {
            root->right = new_right_node;
        }
    } else {
        if (!root->left) { 
            // No left child, replace right
            Node* temp_node = root->right;
            delete root;
            return temp_node;
        } 
        
        if (!root->right) { 
            // No right child, replace left
            Node* temp_node = root->left;
            delete root;
            return temp_node;
        }
        
        // node has two children
        // find smallest node in right subtree to replace the current node with
        // recursively remove successor from the right subtree.
        Node* temp_node = find_minimum_node(root->right);
        root->p = temp_node->p; 
        root->key = temp_node->key;
        root->right = remove(root->right, temp_node->p);
    }
    
    return root;
}

Node* clear(Node* root) {
    if (!root) {
        //tree is empty
        return nullptr;
    }

    // Clear left subtree
    clear(root->left);
    // Clear right subtree
    clear(root->right);
    // Delete current node
    delete root;

    // Return null as new root
    return nullptr;
}

size_t size(const Node& root) {
    if (!&root) {
        return 0;
    }
    
    return 1 + size(*root.left) + size(*root.right);
}

void dump_helper(const Node* root, Point points[], size_t n, size_t& index) {
    if (!root || index >= n) {
        // tree empty || array full
        return;
    }

    // dump left
    dump_helper(root->left, points, n, index);
    
    if (index < n) {
        // Store current node
        points[index++] = root->p;
    }

    // dump right
    dump_helper(root->right, points, n, index);
}

void dump(const Node& root, Point points[], size_t n) {
    size_t index = 0;
    dump_helper(&root, points, n, index); // inorder traversal
}