// intbst.cpp
// Implements class IntBST
// YOUR NAME(S), DATE

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() : root(nullptr) { 

}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if (n) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if (!root) {
        root = new Node(value); // Empty BST case
        return true;
    }
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if (value == n->info) {
        return false;
    }

    if (value < n->info) { // Check if left or right
        if (n->left) { // Check if there is a node
            return insert(value, n->left); // Move to the left
        } else {
            n->left = new Node(value); // This places the node after finding an empty slot
            n->left->parent = n;
            return true; // Return true when it is found
        }
    } else {
        if (n->right) { // Same logic as left just to the right
            return insert(value, n->right);
        } else {
            n->right = new Node(value);
            n->right->parent = n;
            return true;
        }
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if (n) {
        cout << n->info << " ";
        printPreOrder(n->left);
        printPreOrder(n->right);
    }
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
    if (n) {
        printInOrder(n->left);
        cout << n->info << " ";
        printInOrder(n->right);
    }
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if (n) {   
        printPostOrder(n->left);
        printPostOrder(n->right);
        cout << n->info << " "; // Print AFTER children
    }
}

// return sum of values in tree
int IntBST::sum() const {
   return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if (!n) return 0;

    return sum(n->left) + sum(n->right) + n->info;
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if (!n) return 0;

    return count(n->left) + count(n->right) + 1;
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if (!n) return nullptr;
    
    if (value == n->info) return n;

    if (value < n->info){
        return getNodeFor(value, n->left);
    }
    else 
        return getNodeFor(value, n->right);
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    return getNodeFor(value, root) != nullptr;
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node *n = getNodeFor(value, root);
    if (!n) return nullptr;

    if (n->left) {
        Node* p = n->left;
        while (p->right) {
            p = p->right;
        }
        return p;
    }

    Node* p = n->parent;
    while (p && n == p->left) {
        n = p;
        p = p->parent;
    }

    return p;
    
}


int IntBST::getPredecessor(int value) const{
    Node* pred = getPredecessorNode(value);
    if (!pred) return 0;
    return pred->info;
}


IntBST::Node* IntBST::getSuccessorNode(int value) const {
    Node* n = getNodeFor(value, root);   // find node
    if (!n) return nullptr;              // value not in tree

    
    if (n->right) {
        Node* s = n->right;
        while (s->left) {
            s = s->left;
        }
        return s;
    }

    
    Node* s = n->parent;
    while (s && n == s->right) {  
        n = s;
        s = s->parent;
    }

    return s; 


int IntBST::getSuccessor(int value) const{
    Node* succ = getSuccessorNode(value);
    if (!succ) return 0;
    return succ->info;
}


bool IntBST::remove(int value) {
    Node *n = getNodeFor(value, root);
    if (!n) return false;

    if (n->left && n->right) {
        Node* succ = getSuccessorNode(value);

        n->info = succ->info;

        n = succ;
    }

    Node* child = (n->left) ? n-?left: n->right;

    if (child) {
        child->parent = n->parent;
    }

    if (!n->parent) {
        root = child;
    } else if (n == n->parent->left){
        n->parent->right = child;
    }

    delete n;
    return true;
    
}