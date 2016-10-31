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
#include <iostream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

template <class KEY, class DATA>
AVLTree<KEY, DATA>::AVLTree() {



}


template <class KEY, class DATA>
AVLTree<KEY, DATA>::~AVLTree() {

    // The deconstructor in AVLNode should delete the children recursively
    // for us.
    delete m_root;
    m_root = NULL;

}



// This insert function allows us to call the recursive function while only knowing
// the key and the data.
template <class KEY, class DATA>
void AVLTree<KEY, DATA>::insert(KEY key, DATA data) {
    recursiveInsert(key, data, m_root);
}


// This is the function that performs the recursive functioning of the insert function.
// This exists so insert can be called while only knowing the key and data to insert.
template <class KEY, class DATA>
void AVLTree<KEY, DATA>::recursiveInsert(KEY key, DATA data, AVLNode<KEY, DATA>* currNode) {

    if(currNode == NULL) {

        // We finally reached where th enode is supposed to go so we create it and return it.
        currNode = new AVLNode<KEY, DATA>(key, data);
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

    } else if(key > currNode->key) {

        // Recursive call
        currNode->m_right = recursiveInsert(key, data, currNode->right);

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




template <class KEY, class DATA>
bool AVLTree<KEY, DATA>::remove(KEY key) {

}



template <class KEY, class DATA>
AVLNode<KEY, DATA>* AVLTree<KEY, DATA>::search(KEY key) {
    return recursiveSearch(key, m_root);
}

// The function that performs the recursive portion of the search. Used so search()
// can be called when all the user has is a key.
template <class KEY, class DATA>
AVLNode<KEY, DATA>* AVLTree<KEY, DATA>::recursiveSearch(KEY key, AVLNode<KEY, DATA>* currNode) {

    if(currNode->key == key) {

        return currNode;

    } else if(currNode->m_left == NULL && key < currNode->m_key) {

        AVLNode<KEY, DATA>* result = recursiveSearch(key, currNode->m_left);
        if(result != NULL) {
            return result;
        }

    } else if(currNode->m_right == NULL && key > currNode->m_key) {

        // Node is to the right because key is greater than current.
        AVLNode<KEY, DATA>* result = recursiveSearch(key, currNode->m_right);
        if(result != NULL) {
            return result;
        }

    } else {

        return NULL;

    }

}



template <class KEY, class DATA>
void AVLTree<KEY, DATA>::recurPreOrder(AVLNode<KEY, DATA>* currNode, ostream& out) {

    out << currNode->m_data << " ";

    if(currNode->m_left != NULL) {
        recurPreOrder(currNode->m_left, out);
    }

    if(currNode->m_right != NULL) {
        recurPreOrder(currNode->m_right, out);
    }

}


template <class KEY, class DATA>
void AVLTree<KEY, DATA>::recurInOrder(AVLNode<KEY, DATA>* currNode, ostream& out) {

}


template <class KEY, class DATA>
void AVLTree<KEY, DATA>::recurPostOrder(AVLNode<KEY, DATA>* currNode, ostream& out) {

}



template <class KEY, class DATA>
void AVLTree<KEY, DATA>::leftRotate(AVLNode<KEY, DATA>* pivot) {

    // Let temp be pivot's right child
    AVLNode<KEY, DATA>* temp = pivot->m_right;

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



template <class KEY, class DATA>
void AVLTree<KEY, DATA>::rightRotate(AVLNode<KEY, DATA>* pivot) {

    // Let temp be pivot's left child
    AVLNode<KEY, DATA>* temp = pivot->m_left;

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



template <class KEY, class DATA>
void AVLTree<KEY, DATA>::leftRightRotate(AVLNode<KEY, DATA>* pivot) {
    leftRotate(pivot);
    rightRotate(pivot);
}



template <class KEY, class DATA>
void AVLTree<KEY, DATA>::rightleftRotate(AVLNode<KEY, DATA>* pivot) {
    rightRotate(pivot);
    leftRotate(pivot);
}



///////////////////////////////////////////////////////////////
// If you only have a key you can use one of these to rotate //
///////////////////////////////////////////////////////////////



template <class KEY, class DATA>
void AVLTree<KEY, DATA>::leftRotate(KEY pivotKey) {
    leftRotate(search(pivotKey));
}

template <class KEY, class DATA>
void AVLTree<KEY, DATA>::rightRotate(KEY pivotKey) {
    rightRotate(search(pivotKey));
}

template <class KEY, class DATA>
void AVLTree<KEY, DATA>::leftRightRotate(KEY pivotKey) {
    leftRightRotate(search(pivotKey));
}

template <class KEY, class DATA>
void AVLTree<KEY, DATA>::rightLeftRotate(KEY pivotKey) {
    rightLeftRotate(search(pivotKey));
}
