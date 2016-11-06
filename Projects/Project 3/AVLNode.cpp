#ifndef AVLNODE_CPP_
#define AVLNODE_CPP_

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



template <typename DATA, typename KEY>
AVLNode<DATA, KEY>::AVLNode(KEY key, DATA data) {
    m_key = key;
    m_data = data;

    m_height = 1;

    m_left = NULL;
    m_right = NULL;
}


template <typename DATA, typename KEY>
AVLNode<DATA, KEY>::~AVLNode() {
    if(m_left != NULL) {
        delete m_left;
        m_left = NULL;
    }

    if(m_right != NULL) {
        delete m_right;
        m_right = NULL;
    }

}



template <typename DATA, typename KEY>
int AVLNode<DATA, KEY>::calcHeight() {
    int hL = 0;
    int hR = 0;

    if(m_left != NULL) {
        hL = m_left->m_height;
    }

    if(m_right != NULL) {
        hR = m_right->m_height;
    }

    m_height = std::max(hL, hR) + 1;
    return m_height;
}


//template <typename KEY, typename DATA>
//bool AVLNode<KEY, DATA>::operator<(const AVLNode& lhs, const AVLNode& rhs)
//{
//    return lhs->m_key < rhs->m_key;
//}


#endif
