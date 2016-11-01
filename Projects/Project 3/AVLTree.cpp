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

//    cout << "CurrNode: " << currNode << endl;

    if(currNode == NULL) {
//        cout << "equals NULL" << endl;
        // We finally reached where th enode is supposed to go so we create it and return it.
        currNode = new AVLNode<DATA, KEY>(key, data);

    } else if(key < currNode->m_key) {

        // Go through until we can actually insert something, then return all the way back up.
        currNode->m_left = recursiveInsert(key, data, currNode->m_left);

//        cout << currNode << endl;
//        cout << currNode->m_left << endl;
//        cout << currNode->m_left->m_data << endl;

        if(currNode->m_left != NULL) {
            // Set the parent because insert doesn't do that at all.
            currNode->m_left->m_parent = currNode;
        }

        // Calculate the new heights.
        currNode->calcHeight();

        // Get left height or zero if NULL.
        int leftHeight = 0;
        if(currNode->m_left != NULL) {
            leftHeight = currNode->m_left->m_height;
        }

        // Get right height or zero if NULL.
        int rightHeight = 0;
        if(currNode->m_right != NULL) {
            rightHeight = currNode->m_right->m_height;
        }

        if(std::abs(leftHeight - rightHeight) > 1) {

            if(currNode->m_right != NULL && key < currNode->m_left->m_key) {
                // LL
                return leftRotate(currNode);
            } else {
                // LR
                return leftRightRotate(currNode);
            }

        }

    } else if(key > currNode->m_key) {

        // Recursive call
        currNode->m_right = recursiveInsert(key, data, currNode->m_right);

        // The initializer for AVLNode has no way of finding the parent.
        if(currNode->m_right != NULL) {
            // Set the parent because insert doesn't do that at all.
            currNode->m_right->m_parent = currNode;
        }

        currNode->calcHeight();

        int leftHeight = 0;
        if(currNode->m_left != NULL) {
            leftHeight = currNode->m_left->m_height;
        }

        int rightHeight = 0;
        if(currNode->m_right != NULL) {
            rightHeight = currNode->m_right->m_height;
        }

        if(std::abs(leftHeight - rightHeight) > 1) {

            if(currNode->m_right != NULL && key < currNode->m_right->m_key) {
                // RR
                return rightRotate(currNode);
            } else {
                // RL
                return rightLeftRotate(currNode);
            }

        }

    }

    return currNode;

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

    if(currNode->m_key == key) {

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
void AVLTree<DATA, KEY>::recurPostOrder(AVLNode<DATA, KEY>* currNode, std::ostream& out) {

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


///////////////////////////////////////////////////////////////
// These are the rotation functions that perform operations  //
// on the tree.                                              //
///////////////////////////////////////////////////////////////


template <typename DATA, typename KEY>
AVLNode<DATA, KEY>* AVLTree<DATA, KEY>::leftRotate(AVLNode<DATA, KEY>* pivot) {

    cout << pivot << endl;

    // Let temp be pivot's right child
    AVLNode<DATA, KEY>* temp = pivot->m_right;

    cout << temp << endl;

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
AVLNode<DATA, KEY>* AVLTree<DATA, KEY>::rightRotate(AVLNode<DATA, KEY>* pivot) {

    // Let temp be pivot's left child
    AVLNode<DATA, KEY>* temp = pivot->m_right;

    // Set temp's left child to be pivot's right child
    pivot->m_right = temp->m_left;

    // Set pivot's right-child's parent to Temp
    pivot->m_right->m_parent = temp;

    // Set pivot's right child to be temp
    temp->m_left = pivot;

    // Set temp's parent to be pivot
    temp->m_parent = pivot;

    // Redo the height calculations for the heights
    pivot->calcHeight();
    temp->calcHeight();

    return temp;

}


template <typename DATA, typename KEY>
AVLNode<DATA, KEY>* AVLTree<DATA, KEY>::rightRotate(AVLNode<DATA, KEY>* pivot) {

    // Let temp be pivot's left child
    AVLNode<DATA, KEY>* temp = pivot->m_right;

    // Set temp's left child to be pivot's right child
    pivot->m_right = temp->m_left;

    // Set pivot's right-child's parent to Temp
    pivot->m_right->m_parent = temp;

    // Set pivot's right child to be temp
    temp->m_left = pivot;

    // Set temp's parent to be pivot
    temp->m_parent = pivot;

    // Redo the height calculations for the heights
    pivot->calcHeight();
    temp->calcHeight();

    return temp;

}



// LR
template <typename DATA, typename KEY>
AVLNode<DATA, KEY>* AVLTree<DATA, KEY>::leftRightRotate(AVLNode<DATA, KEY>* pivot) {
    pivot->m_left = rightRotate(pivot->m_left);
    return leftRotate(pivot);
}


// RL
template <typename DATA, typename KEY>
AVLNode<DATA, KEY>* AVLTree<DATA, KEY>::rightLeftRotate(AVLNode<DATA, KEY>* pivot) {
    pivot->m_right = leftRotate(pivot->m_right);
    return rightRotate(pivot);
}

#endif
