#ifndef AVLTREE_CPP_
#define AVLTREE_CPP_

/*
 * File:    AVLTree.cpp
 * Author:  Robert Rose
 * Section: 3
 * Created: Oct 29, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * 
 */

#include "AVLTree.h"

#include <string>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <sstream>

using namespace std;

template <typename DATA, typename KEY>
AVLTree<DATA, KEY>::AVLTree() {

    m_root = NULL;

}


template <typename DATA, typename KEY>
AVLTree<DATA, KEY>::~AVLTree() {

    // The deconstructor in AVLNode should delete the children recursively
    // for us.
    delete m_root;
    m_root = NULL;

}



template <typename DATA, typename KEY>
bool AVLTree<DATA, KEY>::remove(KEY key) {

}




template <typename DATA, typename KEY>
typename AVLTree<DATA, KEY>::Node* AVLTree<DATA, KEY>::search(KEY key) {
    return recursiveSearch(key, m_root);
}

// The function that performs the recursive portion of the search. Used so search()
// can be called when all the user has is a key.
template <typename DATA, typename KEY>
typename AVLTree<DATA, KEY>::Node* AVLTree<DATA, KEY>::recursiveSearch(KEY key, Node* currNode) {

    if(currNode->m_key == key) {

        return currNode;

    } else if(currNode->m_left == NULL && key < currNode->m_key) {

        Node* result = recursiveSearch(key, currNode->m_left);
        if(result != NULL) {
            return result;
        }

    } else if(currNode->m_right == NULL && key > currNode->m_key) {

        // Node is to the right because key is greater than current.
        Node* result = recursiveSearch(key, currNode->m_right);
        if(result != NULL) {
            return result;
        }

    } else {

        return NULL;

    }

}






/********************************************************************
 *                        INSERTION CODE                            *
 ********************************************************************/



// This insert function allows us to call the recursive function while only knowing
// the key and the data.
template <typename DATA, typename KEY>
void AVLTree<DATA, KEY>::insert(KEY key, DATA data) {
    m_root = recursiveInsert(key, data, m_root);
}



// This is the function that performs the recursive functioning of the insert function.
// This exists so insert can be called while only knowing the key and data to insert.
template <typename DATA, typename KEY>
typename AVLTree<DATA, KEY>::Node* AVLTree<DATA, KEY>::recursiveInsert(KEY key, DATA data, Node*& currNode) {


    if(currNode == NULL) {

        // We've reached the end of the tree, now add the new node.

        currNode = new Node(key, data);

        return currNode;

    } else if(key < currNode->m_key) {

//        if(currNode->m_left == NULL && currNode->m_right == NULL) {
//            currNode->m_height += 1;
//        }

        currNode->m_left = recursiveInsert(key, data, currNode->m_left);

        currNode->m_height = std::max(safeHeight(currNode->m_left), safeHeight(currNode->m_right)) + 1;

        currNode = balance(currNode, key);

    } else if(key > currNode->m_key) {

//        if(currNode->m_left == NULL && currNode->m_right == NULL) {
//            currNode->m_height += 1;
//        }

        currNode->m_right = recursiveInsert(key, data, currNode->m_right);

        currNode->m_height = std::max(safeHeight(currNode->m_left), safeHeight(currNode->m_right)) + 1;

        currNode = balance(currNode, key);

    }

//    currNode->m_height++;

    cout << "Balanced: " << currNode->m_data << " Height: " << currNode->m_height << endl;

    return currNode;

}


template <typename DATA, typename KEY>
typename AVLTree<DATA, KEY>::Node* AVLTree<DATA, KEY>::balance(Node*& node, KEY key) {

    int factor = bfactor(node);

    if (factor > 1) {
        if(key < node->m_left->m_key) {

            return rotateRight(node);

        } else if(key > node->m_left->m_key) {

            node->m_left =  rotateLeft(node->m_left);
            return rotateRight(node);

        }

    } else if(factor < -1) {

        if(key < node->m_right->m_key) {

            node->m_right = rotateRight(node->m_right);
            return rotateLeft(node);

        } else if(key > node->m_right->m_key) {

            return rotateLeft(node);

        }

    }

    cout << "Balanced: " << node->m_data << " Height: " << node->m_height << endl;

    return node;

}



//////////////////////////////////////////////////////////////////
// These are the rotation functions that perform operations     //
// on the tree. Special thanks to Wikipedia:                    //
// https://en.wikipedia.org/wiki/Tree_rotation                  //
//////////////////////////////////////////////////////////////////

// When new node is added in Right of Right subtree
template <typename DATA, typename KEY>
typename AVLTree<DATA, KEY>::Node* AVLTree<DATA, KEY>::rotateRight(Node* parent) {

    Node* temp = parent->m_left;

    parent->m_left = temp->m_right;

    temp->m_right = parent;

//    if(parent != NULL) {
//        parent->m_height--;
//    }
//
//    if(temp != NULL) {
//        temp->m_height++;
//    }


    // update subtree right
    // update root height
    parent->m_height = std::max(safeHeight(parent->m_left), safeHeight(parent->m_right)) + 1;
    temp->m_height = std::max(safeHeight(temp->m_left), safeHeight(temp->m_right)) + 1;

    return temp;

}



// When node is added to left of left subtree
template <typename DATA, typename KEY>
typename AVLTree<DATA, KEY>::Node* AVLTree<DATA, KEY>::rotateLeft(Node* parent) {

    Node* temp = parent->m_right;

    parent->m_right = temp->m_left;

    temp->m_left = parent;

    // Update the heights
    parent->m_height = std::max(safeHeight(parent->m_left), safeHeight(parent->m_right)) + 1;
    temp->m_height = std::max(safeHeight(temp->m_left), safeHeight(temp->m_right)) + 1;

    return temp;

}





/********************************************************************
 *                              PRINTING CODE                       *
 ********************************************************************/

// Prints using the print order saved.
template <typename DATA, typename KEY>
void AVLTree<DATA, KEY>::print(std::ostream& out) {
    print(m_printOrder, out);
}

// Prints the tree according to the provided print order.
template <typename DATA, typename KEY>
void AVLTree<DATA, KEY>::print(PrintOrder order, std::ostream& out) {

    stringstream stream;

    switch(order) {
        case IN:
            recurInOrder(m_root, stream);
            break;
        case PRE:
            recurPreOrder(m_root, stream);
            break;
        case POST:
            recurPostOrder(m_root, stream);
            break;
        case LEVEL:
            break;
    }

    out << stream.str();

    out << endl;
}



//////////////////////////////////////////////////////////////////
// These are the recursive printing functions that print all    //
// the information out in a recursive manner.                   //
//////////////////////////////////////////////////////////////////



// The recursive function used to print the tree in pre order.
template <typename DATA, typename KEY>
void AVLTree<DATA, KEY>::recurPreOrder(Node* currNode, std::ostream& out) {

    if(currNode == NULL) {
        return;
    }

    out << currNode->m_data << " ";

    if(currNode->m_left != NULL) {
        recurPreOrder(currNode->m_left, out);
    }

    if(currNode->m_right != NULL) {
        recurPreOrder(currNode->m_right, out);
    }

}



// The recursive function used to print the tree in order.
template <typename DATA, typename KEY>
void AVLTree<DATA, KEY>::recurInOrder(Node* currNode, std::ostream& out) {

//    cerr << currNode->m_data << endl;

    if(currNode == NULL) {
        return;
    }

    // The left
    if(currNode->m_left != NULL) {
        recurInOrder(currNode->m_left, out);
    }

    // The middle
    out << currNode->m_data << " ";

    // The right
    if(currNode->m_right != NULL) {
        recurInOrder(currNode->m_right, out);
    }

}



template <typename DATA, typename KEY>
void AVLTree<DATA, KEY>::recurPostOrder(Node* currNode, std::ostream& out) {

//    cerr << currNode->m_data << endl;

    if(currNode == NULL) {
        return;
    }

    if(currNode->m_left != NULL) {
        recurPostOrder(currNode->m_left, out);
    }

    if(currNode->m_right != NULL) {
        recurPostOrder(currNode->m_right, out);
    }

    out << currNode->m_data << " ";

}



//////////////////////////////////////////////////////////////////
// These are some utility functions.                            //
//////////////////////////////////////////////////////////////////

template <typename DATA, typename KEY>
int AVLTree<DATA, KEY>::safeHeight(Node* node) {
    return node != NULL ? node->m_height : 0;
}

template <typename DATA, typename KEY>
int AVLTree<DATA, KEY>::bfactor(Node* node) {
    return safeHeight(node->m_left) - safeHeight(node->m_right);
}

#endif
