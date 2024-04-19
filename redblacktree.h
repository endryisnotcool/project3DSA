//redblacktree data structure
/*
 * IMPORTANT:
 * Much of this code is reused from Jack Hernandez's Project 1:
 * AVLTree AVL.h file. Some methods were also used from
 * The DSA publicly available slides, specifically
 * 4 - balanced trees
 */

#ifndef PROJECT3DSA_REDBLACKTREE_H
#define PROJECT3DSA_REDBLACKTREE_H

#include <vector>
#include <string>
#include "song.h"

using namespace std;

class RBTree {
private:

    //create node structure
    struct Node {

        //internal node variables
        const string NAME;
        vector<song> songs;
        Node* left;
        Node* right;
        bool red;

        //node constructor
        Node(string name, song newSong)
                : NAME(name), left(nullptr), right(nullptr), songs({newSong}), red(true)  {}
    };

    //RedBlackTree root variable
    Node* root {};

    //declare helper functions
    Node* rightRotate(Node* node);
    Node* leftRotate(Node* node);
    Node* insertHelper(Node* node, Node* parent, string name, song newSong, bool& balanced, bool& recoloring);
    Node* searchHelper(string name);

public:
    RBTree() : root(nullptr) {};

    void insert(string name, song newSong);
    vector<song> search(string name);
};

//right rotate around given node
RBTree::Node* RBTree::rightRotate(RBTree::Node* node) {
    //get temporary nodes
    Node* left = node->left;
    Node* rightSubtree = left->right;

    //perform rotation
    left->right = node;
    node->left = rightSubtree;

    //update root if rotated node was previously root
    if(this->root == node)
        this->root = left;

    //return new node
    return left;
}

//left rotate around given node
RBTree::Node* RBTree::leftRotate(RBTree::Node* node) {
    Node* right = node->right;
    Node* leftSubtree = right->left;

    //perform rotation
    right->left = node;
    node->right = leftSubtree;

    //update root if rotated node was previously root
    if(this->root == node)
        this->root = right;

    //return new node
    return right;
}


//private insert helper function
RBTree::Node* RBTree::insertHelper(RBTree::Node* node, RBTree::Node* parent, string name, song newSong, bool& balanced, bool& recoloring) {
    //insert node if place is found
    if (node == nullptr)
        return new Node(name, newSong);

    //search for correct spot
    if (name < node->NAME) {
        Node* newNode = insertHelper(node->left, node, name, newSong, balanced, recoloring);
        if(newNode->left == node || newNode->right == node)
            return newNode;
        else
            node->left = newNode;
    } else if (name > node->NAME) {
        Node* newNode = insertHelper(node->right, node, name, newSong, balanced, recoloring);
        if(newNode->left == node || newNode->right == node)
            return newNode;
        else
            node->right = newNode;
    }


    //balance tree

    if(balanced)
        return node;

    //if parent of newly inserted node is black, we good
    if (!node->red) {
        //if still in recoloring process, tree is not balanced here
        if(!recoloring)
            balanced = true;
        return node;
    }

    //if parent of newly inserted node is red, check uncle
    Node *uncle = parent->left;
    if (uncle == node)
        uncle = parent->right;

    //if uncle is red, flip colors
    if(recoloring || (uncle != nullptr && uncle->red)) {
        recoloring = true;

        //swap colors for uncle, node, and parent
        if(uncle!=nullptr)
            if(uncle->red)
                uncle->red = false;
            else
                uncle->red = true;

        if(node->red)
            node->red = false;
        else
            node->red = true;

        if(parent->red)
            parent->red = false;
        else
            parent->red = true;

        //if root ends up with its color swapped, we are done
        if(this->root->red) {
            this->root->red = false;
            balanced = true;
        }

        return node;
    }

    //if uncle is black, perform rotations
    Node* child = node->left;
    if(child == nullptr || !child->red)
        child = node->right;

    //left left case
    if (parent->left == node && node->left == child) {
        node->red = false;
        parent->red = true;
        balanced = true;
        node = rightRotate(parent);
    }

    //right right case
    if (parent->right == node && node->right == child) {
        node->red = false;
        parent->red = true;
        balanced = true;
        node = leftRotate(parent);
    }

    //left right case
    if (parent->left == node && node->right == child) {
        node = leftRotate(node);
        node->red = false;
        parent->red = true;
        balanced = true;
        node = rightRotate(parent);
    }

    //right left case
    if (parent->right == node && node->left == child) {
        node = rightRotate(node);
        node->red = false;
        parent->red = true;
        balanced = true;
        node = leftRotate(parent);
    }

    return node;
}

//private search helper function
RBTree::Node* RBTree::searchHelper(string name) {
    Node *node = this->root;

//searches by going to the right or left as needed
    while (true) {
        if (node == nullptr)
            return nullptr;
        else if (name < node->NAME)
            node = node->left;
        else if (name > node->NAME)
            node = node->right;
        else if (name == node->NAME)
            return node;
    }
}

//public insert function
void RBTree::insert(string name, song newSong) {

    //check if item with this name already exists
    Node* x = searchHelper(name);

    if(x != nullptr) {
        x->songs.push_back(newSong);
        return;
    }

    //create new node if one does not already exist for this name
    bool balanced = false;
    bool recoloring = false;
    if (this->root == nullptr) {  //create root if one does not already exist
        this->root = insertHelper(nullptr, nullptr, name, newSong, balanced, recoloring);
        this->root->red = false;
    } else
        insertHelper(this->root, nullptr, name, newSong, balanced, recoloring);
}

//public search function
//searches tree by name
vector<song> RBTree::search(string name) {
    Node* result = searchHelper(name);
    if(result == nullptr)
        return {};
    return result->songs;
}

#endif //PROJECT3DSA_REDBLACKTREE_H
