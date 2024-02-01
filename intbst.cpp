//intbst.cpp
//Implements class IntBST
//Alexandru Gherghescu, 1/24/24
#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() { 
    root = nullptr;
}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if (!n) return;

    clear(n->left);
    clear(n->right);

    delete n;
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if (!root) {
        root = new Node(value);
        return true;
    }
    return insert(value, *&root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    /******if (!n) {
        n = new Node(value);
        return true;
    } 

    if (contains(value)) return false;

    if (value < n->info) {
        if (n->left == nullptr) {
            Node* l = new Node(value);
            n->left = l;
            l->parent = n;
            return true;
        }
        return insert(value, n->left);
    } else if (value > n->info) {
        if (n->right == nullptr) {
            Node* r = new Node(value);
            n->right = r;
            r->parent = n;
            return true;
        }
        return insert(value, n->right);
    } 
    ****/
    return false;

}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if (!n) return;

    cout << n->info << " ";

    printPreOrder(n->left);
    printPreOrder(n->right);
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}

void IntBST::printInOrder(Node *n) const {
    if (!n) return;

    printInOrder(n->left);

    cout << n->info << " ";

    printInOrder(n->right);
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);   
}
// return sum of values in tree
int IntBST::sum() const {
    return sum(*&root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if (!n) return 0;

    return n->info + sum(n->left) + sum(n->right);
}

// return count of values
int IntBST::count() const {
    return count(*&root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if (!n) return 0;
    
    return 1 + count(n->left) + count(n->right);
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if (!n) return nullptr;
    
    while (n != nullptr) {
        if (value < n->info) {
            n = n->left;
        } else if (value > n->info) {
            n = n->right;
        } else if (n->info == value) {
            return n;
        }
    }
    return nullptr;
}
// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {

    Node* node = root;
    while (node != nullptr) {
        if (value < node->info) {
            node = node->left;
        } else if (value > node->info) {
            node = node->right;
        } else if (node->info == value) {
            return true;
        }
    }
    return false;
}
// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const {
    // Keep finding "max value" less than value
    /******if (!root || !contains(value) || count() == 1) return nullptr;
    else {
        Node* node = root;
        Node* predecessor = nullptr;
        while (node->info != value) {
            if (value < node->info) node = node->left;
            else {
                predecessor = node;
                node = node->right;
            }
        }

        if (node->left) {
            predecessor = node->left;

            while (predecessor->right) {
                predecessor = predecessor->right;
            }
        }
        return predecessor;
    }
    *******/
    
    return nullptr;
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    return -1; // REPLACE THIS NON-SOLUTION
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    /******if (!root || !contains(value) || count() == 1) return nullptr;
    else {
        Node* node = root;
        Node* successor = nullptr;
        while (node->info != value) {
            if (value < node->info) {
                successor = node;
                node = node->left;
            } else {
                node = node->right; 
            }
        }

        if (node->right) {
            successor = node->right;

            while (successor->left) {
                successor = successor->left;
            }
        }
        return successor;
    }
    *******/
    
    return nullptr;
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    return -1; // REPLACE THIS NON-SOLUTION
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
     if (!contains(value)) return false;

    Node* node = getNodeFor(value, root);

    if (!(node->left) && !(node->right)) {
        // No Children

        if (node == root) root = nullptr;
        else {
            if (node->parent->left == node) node->parent->left = nullptr;
            else node->parent->right = nullptr;
        }

        delete node;
        return true;
    } 
    
    if (!(node->left) || !(node->right)) {
        // Single left child

        Node* childNode = node->left ? node->left : node->right;

        if (node == root) root = childNode;
        else {
            if (node->parent->left == node) node->parent->left = childNode;
            else node->parent->right = childNode;
        }

        childNode->parent = node->parent;

        delete node;
        return true;
    } 
    

    Node* successor = getSuccessorNode(value);
    node->info = successor->info;

    if (successor->right) {
        if (successor->parent->left == successor) successor->parent->left = successor->right;
        else successor->parent->right = successor->right;

        successor->right->parent = successor->parent;
    } else {
        if (successor->parent->left == successor) successor->parent->left = nullptr;
        else successor->parent->right = nullptr;
    }

    delete successor;
    return true;

}
