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
        m_root = new AVLNode<DATA, KEY>(key, data);
    } else {
        recursiveInsert(key, data, m_root);
    }
}


// This is the function that performs the recursive functioning of the insert function.
// This exists so insert can be called while only knowing the key and data to insert.
template <typename DATA, typename KEY>
AVLNode<DATA, KEY>* AVLTree<DATA, KEY>::recursiveInsert(KEY key, DATA data, AVLNode<DATA, KEY>* currNode) {

    if(currNode == NULL) {

        // We finally reached where th enode is supposed to go so we create it and return it.
        currNode = new AVLNode<DATA, KEY>(key, data);
        return currNode;

    } else if(key < currNode->m_key) {

        // Go through until we can actually insert something, then return all the way back up.
        currNode->m_left = recursiveInsert(key, data, currNode->m_left);

        // Set the parent because insert doesn't do that at all.
        currNode->m_left->m_parent = currNode;

        // Calculate the new heights.
        currNode->calcHeight();

        if(std::abs(currNode->m_left->m_height - currNode->m_right->m_height) > 1) {

            if(key < currNode->m_left->m_key) {
                // LL
                leftRotate(currNode);
            } else {
                // LR
                leftRightRotate(currNode);
            }

        }

    } else if(key > currNode->m_key) {

        // Recursive call
        currNode->m_right = recursiveInsert(key, data, currNode->m_right);

        // The initializer for AVLNode has no way of finding the parent.
        currNode->m_right->m_parent = currNode;

        currNode->calcHeight();

        if(std::abs(currNode->m_left->m_height - currNode->m_right->m_height) > 1) {

            if(key < currNode->m_right->m_key) {
                // RR
                rightRotate(currNode);
            } else {
                // RL
                leftRightRotate(currNode);
            }

        }

    } else {

        // Need  to return something if it's equal to despite that never happening
        // based from project specs.
        return currNode;

    }

}




template <typename DATA, typename KEY>
bool AVLTree<DATA, KEY>::remove(KEY key) {

}



template <typename DATA, typename KEY>
AVLNode<DATA, KEY>* AVLTree<DATA, KEY>::search(KEY key) {
    return recursiveSearch(key, m_root);
}

// The function that performs the recursive portion of the search. Used so search()
// can be called when all the user has is a key.
template <typename DATA, typename KEY>
AVLNode<DATA, KEY>* AVLTree<DATA, KEY>::recursiveSearch(KEY key, AVLNode<DATA, KEY>* currNode) {

    if(currNode->key == key) {

        return currNode;

    } else if(currNode->m_left == NULL && key < currNode->m_key) {

        AVLNode<DATA, KEY>* result = recursiveSearch(key, currNode->m_left);
        if(result != NULL) {
            return result;
        }

    } else if(currNode->m_right == NULL && key > currNode->m_key) {

        // Node is to the right because key is greater than current.
        AVLNode<DATA, KEY>* result = recursiveSearch(key, currNode->m_right);
        if(result != NULL) {
            return result;
        }

    } else {

        return NULL;

    }

}


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



///////////////////////////////////////////////////////////////
// These are the recursive printing functions that print all //
// the information out in a recursive manner.                //
///////////////////////////////////////////////////////////////


template <typename DATA, typename KEY>
void AVLTree<DATA, KEY>::recurPreOrder(AVLNode<DATA, KEY>* currNode, std::ostream& out) {

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
void AVLTree<DATA, KEY>::recurInOrder(AVLNode<DATA, KEY>* currNode, std::ostream& out) {

    cerr << currNode->m_data << endl;

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
void AVLTree<DATA, KEY>::recurPostOrder(AVLNode<DATA, KEY>* currNode, std::ostream& out) {

    cerr << currNode->m_data << endl;

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


///////////////////////////////////////////////////////////////
// These are the rotation functions that perform operations  //
// on the tree.                                              //
///////////////////////////////////////////////////////////////


template <typename DATA, typename KEY>
void AVLTree<DATA, KEY>::leftRotate(AVLNode<DATA, KEY>* pivot) {

    // Let temp be pivot's right child
    AVLNode<DATA, KEY>* temp = pivot->m_right;

    // Set pivot's right child to be temp's left child
    pivot->m_right = temp->m_left;

    // Set temp's left-child's parent to pivot
    temp->m_left->m_parent = pivot;

    // Set temp's left child to be pivot
    temp->m_left = pivot;

    // Set pivot's parent to be temp
    pivot->m_parent = temp;

    // Redo the height calculations for the heights
    pivot->calcHeight();
    temp->calcHeight();

}



template <typename DATA, typename KEY>
void AVLTree<DATA, KEY>::rightRotate(AVLNode<DATA, KEY>* pivot) {

    // Let temp be pivot's left child
    AVLNode<DATA, KEY>* temp = pivot->m_left;

    // Set temp's left child to be pivot's right child
    temp->m_left = pivot->m_right;

    // Set pivot's right-child's parent to Temp
    pivot->m_right->m_parent = temp;

    // Set pivot's right child to be temp
    pivot->m_left = temp;

    // Set temp's parent to be pivot
    temp->m_parent = pivot;

    // Redo the height calculations for the heights
    pivot->calcHeight();
    temp->calcHeight();

}



template <typename DATA, typename KEY>
void AVLTree<DATA, KEY>::leftRightRotate(AVLNode<DATA, KEY>* pivot) {
    leftRotate(pivot);
    rightRotate(pivot);
}



template <typename DATA, typename KEY>
void AVLTree<DATA, KEY>::rightleftRotate(AVLNode<DATA, KEY>* pivot) {
    rightRotate(pivot);
    leftRotate(pivot);
}


///////////////////////////////////////////////////////////////
// If you only have a key you can use one of these to rotate //
///////////////////////////////////////////////////////////////



template <typename DATA, typename KEY>
void AVLTree<DATA, KEY>::leftRotate(KEY pivotKey) {
    leftRotate(search(pivotKey));
}

template <typename DATA, typename KEY>
void AVLTree<DATA, KEY>::rightRotate(KEY pivotKey) {
    rightRotate(search(pivotKey));
}

template <typename DATA, typename KEY>
void AVLTree<DATA, KEY>::leftRightRotate(KEY pivotKey) {
    leftRightRotate(search(pivotKey));
}

template <typename DATA, typename KEY>
void AVLTree<DATA, KEY>::rightLeftRotate(KEY pivotKey) {
    rightLeftRotate(search(pivotKey));
}

#endif
