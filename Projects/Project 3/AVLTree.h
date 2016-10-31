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

using namespace std;

template <class KEY, class DATA>
class AVLTree : public AVLTreeBase {
public:
    AVLTree();
    ~AVLTree();

    // Special thanks to Wikipedia to help understand all these rotations
    // https://en.wikipedia.org/wiki/Tree_rotation

    void leftRotate(AVLNode<KEY, DATA>* pivot);
    void rightRotate(AVLNode<KEY, DATA>* pivot);
    void leftRightRotate(AVLNode<KEY, DATA>* pivot);
    void rightleftRotate(AVLNode<KEY, DATA>* pivot);

    void leftRotate(KEY pivotKey);
    void rightRotate(KEY pivotKey);
    void leftRightRotate(KEY pivotKey);
    void rightLeftRotate(KEY pivotKey);


    void insert(KEY key, DATA data);

    // Removes a node from the tree with the given key.
    // Takes: A key to remove.
    // Returns: true if it found and removed the node, false otherwise.
    bool remove(KEY key);
    AVLNode<KEY, DATA>* search(KEY key);

    void print();
    void recurPreOrder(AVLNode<KEY, DATA>* currNode, ostream& out);
    void recurInOrder(AVLNode<KEY, DATA>* currNode, ostream& out);
    void recurPostOrder(AVLNode<KEY, DATA>* currNode, ostream& out);

    AVLNode<KEY, DATA>* getRoot() {
        return m_root;
    };

    void setRoot(AVLNode<KEY, DATA>* root) {
        m_root = root;
    };

private:
    AVLNode<KEY, DATA>* m_root;

    // This is the recursive method that inserts the data into the tree and
    // performs the neccessary roations for it to be a proper AVL tree.
    // Takes: A key value, data to use and the node currently on.
    // Results: In a tree with the new node added.
    void recursiveInsert(KEY key, DATA data, AVLNode<KEY, DATA>* node);

    // This is the recursive method that searches for and returns the Node into the AVL tree
    // Takes: a key to search for and the current node being searched.
    // Returns: the node with a given key or NULL if the node is not found under the node.
    AVLNode<KEY, DATA>* recursiveSearch(KEY key, AVLNode<KEY, DATA>* node);
};

#endif /* AVLTREE_H_ */
