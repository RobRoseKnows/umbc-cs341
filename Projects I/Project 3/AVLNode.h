/*
 * File:    AVLNode.h
 * Author:  Robert
 * Section: 3
 * Created: Oct 31, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * 
 */

#ifndef AVLNODE_H_
#define AVLNODE_H_

using namespace std;

template <typename DATA, typename KEY>
class AVLNode {
public:

    AVLNode(KEY key, DATA data);

    // This is a recursive deconstructor for the node class. This way it
    // deletes the child nodes.
    ~AVLNode();

    // I'm making all these public to make the program simpler.
    KEY m_key;
    DATA m_data;

    int m_height;

    AVLNode* m_left;
    AVLNode* m_right;

    int calcHeight();

    int balance();

//    bool operator<(const AVLNode& lhs, const AVLNode& rhs);
};

#include "AVLNode.cpp"

#endif /* AVLNODE_H_ */
