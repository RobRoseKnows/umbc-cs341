#ifndef AVLTREE_H_
#define AVLTREE_H_

/*
 * File:    AVLTree.h
 * Author:  Robert
 * Section: 3
 * Created: Oct 29, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * 
 */

#include "AVLTreeBase.h"
#include "AVLNode.h"
#include <iostream>

using namespace std;

template <typename DATA, typename KEY>
class AVLTree : public AVLTreeBase {
public:
    AVLTree();
    ~AVLTree();

    // Special thanks to Wikipedia to help me understand all these rotations
    // https://en.wikipedia.org/wiki/Tree_rotation

    void leftRotate(AVLNode<DATA, KEY>* pivot);
    void rightRotate(AVLNode<DATA, KEY>* pivot);
    void leftRightRotate(AVLNode<DATA, KEY>* pivot);
    void rightleftRotate(AVLNode<DATA, KEY>* pivot);

    void leftRotate(KEY2 pivotKey);
    void rightRotate(KEY pivotKey);
    void leftRightRotate(KEY pivotKey);
    void rightLeftRotate(KEY pivotKey);


    void insert(KEY key, DATA data);

    // Removes a node from the tree with the given key.
    // Takes: A key to remove.
    // Returns: true if it found and removed the node, false otherwise.
    bool remove(KEY key);
    AVLNode<DATA, KEY>* search(KEY key);

    void print(PrintOrder order, ostream& out);

    AVLNode<DATA, KEY>* getRoot() {
        return m_root;
    };

    void setRoot(AVLNode<DATA, KEY>* root) {
        m_root = root;
    };

private:
    AVLNode<DATA, KEY>* m_root;

    // This is the recursive method that inserts the data into the tree and
    // performs the neccessary roations for it to be a proper AVL tree.
    // Takes: A key value, data to use and the node currently on.
    // Results: In a tree with the new node added.
    AVLNode<DATA, KEY>* recursiveInsert(KEY key, DATA data, AVLNode<DATA, KEY>* node);

    // This is the recursive method that searches for and returns the Node into the AVL tree
    // Takes: a key to search for and the current node being searched.
    // Returns: the node with a given key or NULL if the node is not found under the node.
    AVLNode<DATA, KEY>* recursiveSearch(KEY key, AVLNode<DATA, KEY>* node);


    void recurPreOrder(AVLNode<DATA, KEY>* currNode, ostream& out);
    void recurInOrder(AVLNode<DATA, KEY>* currNode, ostream& out);
    void recurPostOrder(AVLNode<DATA, KEY>* currNode, ostream& out);
};

#include "AVLTree.cpp"

#endif /* AVLTREE_H_ */
