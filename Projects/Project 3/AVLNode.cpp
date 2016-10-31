/*
 * File:    AVLNode.cpp
 * Author:  Robert
 * Section: 3
 * Created: Oct 29, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * 
 */

#include "AVLNode.h"
#include <stdlib.h>
#include <algorithm>

using namespace std;


template <class KEY, class DATA>
void AVLNode<KEY, DATA>::AVLNode<KEY, DATA>::AVLNode(KEY key, DATA data) {
    m_key = key;
    m_data = data;

    m_height = 1;

    m_left = NULL;
    m_right = NULL;
    m_parent = NULL;
}


template <class KEY, class DATA>
AVLNode<KEY, DATA>::~AVLNode() {
    if(m_left != NULL) {
        delete m_left;
        m_left = NULL;
    }

    if(m_right != NULL) {
        delete m_right;
        m_right = NULL;
    }

    m_parent = NULL;
}



template <class KEY, class DATA>
void AVLNode<KEY, DATA>::calcHeight() {
    int hL = 0;
    int hR = 0;

    if(m_left != NULL) {
        hL = m_left->calcHeight();
    }

    if(m_right != NULL) {
        hR = m_right->calcHeight();
    }

    m_height = std::max(hL, hR) + 1;
}

//template <class KEY, class DATA>
//bool AVLNode<KEY, DATA>::operator<(const AVLNode& lhs, const AVLNode& rhs)
//{
//    return lhs->m_key < rhs->m_key;
//}
