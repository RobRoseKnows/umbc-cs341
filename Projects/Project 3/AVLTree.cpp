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



// This insert function allows us to call the recursive function while only knowing
// the key and the data.
template <typename DATA, typename KEY>
void AVLTree<DATA, KEY>::insert(KEY key, DATA data) {
    if(m_root == NULL) {
        m_root = new Node(key, data);
    } else {
        m_root = recursiveInsert(key, data, m_root);
    }
}


// This is the function that performs the recursive functioning of the insert function.
// This exists so insert can be called while only knowing the key and data to insert.
template <typename DATA, typename KEY>
typename AVLTree<DATA, KEY>::Node* AVLTree<DATA, KEY>::recursiveInsert(KEY key, DATA data, Node* currNode) {

//    if(currNode->m_left != NULL) {
//        currNode->m_left->m_parent = currNode;
//    }
//
//    if(currNode->m_right != NULL) {
//        currNode->m_right->m_parent = currNode;
//    }

    if(currNode == NULL) {

        return new Node(key, data);

    } else if(key < currNode->m_key) {

        currNode->m_left = recursiveInsert(key, data, currNode->m_left);

    } else if(key > currNode->m_key) {

        currNode->m_right = recursiveInsert(key, data, currNode->m_right);
    }

    return balance(currNode);

}


template <typename DATA, typename KEY>
typename AVLTree<DATA, KEY>::Node* AVLTree<DATA, KEY>::balance(Node* pivot) {
    // Use the safeHeight helper functions to get the height.
     pivot->m_height = 1 + std::max(safeHeight(pivot->m_left), safeHeight(pivot->m_right));

     if(bfactor(pivot) == 2) {

         if(bfactor(pivot->m_right) < 0) {
             return rotateRightLeft(pivot);
         } else {
             return rotateLeft(pivot);
         }

     } else if(bfactor(pivot) == -2){

         if(bfactor(pivot->m_left) > 0) {
             return rotateLeftRight(pivot);
         } else {
             return rotateRight(pivot);
         }

     }

     return pivot;
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


// Prints the tree according to the provided print order.
template <typename DATA, typename KEY>
void AVLTree<DATA, KEY>::print(PrintOrder order) {

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

    cout << stream.str();

    cout << endl;
}



//////////////////////////////////////////////////////////////////
// These are the rotation functions that perform operations     //
// on the tree. Special thanks to Wikipedia:                    //
// https://en.wikipedia.org/wiki/Tree_rotation                  //
//////////////////////////////////////////////////////////////////

// When new node is added in Right of Right subtree
template <typename DATA, typename KEY>
typename AVLTree<DATA, KEY>::Node* AVLTree<DATA, KEY>::rotateLeft(Node* pivot) {

    Node* temp = pivot->m_right;

    pivot->m_right = temp->m_left;

    temp->m_right = pivot;

    temp->calcHeight();
    pivot->calcHeight();

    return temp;
}


// When node is added to left of left subtree
template <typename DATA, typename KEY>
typename AVLTree<DATA, KEY>::Node* AVLTree<DATA, KEY>::rotateRight(Node* pivot) {

    Node* temp = pivot->m_left;
    
    pivot->m_left = temp->m_right;
    
    temp->m_right = pivot;
    
    temp->calcHeight();
    pivot->calcHeight();

    return temp;

}



template <typename DATA, typename KEY>
typename AVLTree<DATA, KEY>::Node* AVLTree<DATA, KEY>::rotateLeftRight(Node* pivot) {
    pivot->m_left = rotateLeft(pivot->m_left);

    return rotateRight(pivot);
}



template <typename DATA, typename KEY>
typename AVLTree<DATA, KEY>::Node* AVLTree<DATA, KEY>::rotateRightLeft(Node* pivot) {
    pivot->m_right = rotateRight(pivot->m_right);

    return rotateLeft(pivot);
}



//////////////////////////////////////////////////////////////////
// These are the recursive printing functions that print all    //
// the information out in a recursive manner.                   //
//////////////////////////////////////////////////////////////////


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


template <typename DATA, typename KEY>
void AVLTree<DATA, KEY>::recurInOrder(Node* currNode, std::ostream& out) {

//    cerr << currNode->m_data << endl;

    if(currNode == NULL) {
        return;
    }

    if(currNode->m_left != NULL) {
        recurPreOrder(currNode->m_left, out);
    }

    out << currNode->m_data << " ";

    if(currNode->m_right != NULL) {
        recurPreOrder(currNode->m_right, out);
    }

}


template <typename DATA, typename KEY>
void AVLTree<DATA, KEY>::recurPostOrder(Node* currNode, std::ostream& out) {

//    cerr << currNode->m_data << endl;

    if(currNode == NULL) {
        return;
    }

    if(currNode->m_left != NULL) {
        recurPreOrder(currNode->m_left, out);
    }

    if(currNode->m_right != NULL) {
        recurPreOrder(currNode->m_right, out);
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
    return safeHeight(node->m_right) - safeHeight(node->m_left);
}

#endif
