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
    // I got sick of writing the whole thing out so I created the type
    // Node to represent the AVLNode<DATA, KEY> class.
    typedef AVLNode<DATA, KEY> Node;

    AVLTree();
    ~AVLTree();

    Node* rotateLeft(Node* pivot);
    Node* rotateRight(Node* pivot);
    Node* rotateLeftRight(Node* pivot);
    Node* rotateRightLeft(Node* pivot);


    void insert(KEY key, DATA data);

    // Removes a node from the tree with the given key.
    // Takes: A key to remove.
    // Returns: true if it found and removed the node, false otherwise.
    bool remove(KEY key);
    Node* search(KEY key);

    void print(PrintOrder order);


    Node* getRoot() {
        return m_root;
    };

    void setRoot(Node* root) {
        m_root = root;
    };
protected:
    // Guards against null pointers.
    int safeHeight(Node* node);

    int bfactor(Node* node);
private:

    Node* m_root;

    Node* balance(Node* pivot);

    // This is the recursive method that inserts the data into the tree and
    // performs the neccessary roations for it to be a proper AVL tree.
    // Takes: A key value, data to use and the node currently on.
    // Results: In a tree with the new node added.
    Node* recursiveInsert(KEY key, DATA data, Node* node);

    // This is the recursive method that searches for and returns the Node into the AVL tree
    // Takes: a key to search for and the current node being searched.
    // Returns: the node with a given key or NULL if the node is not found under the node.
    Node* recursiveSearch(KEY key, Node* node);

    void recurPreOrder(Node* currNode, std::ostream& out);
    void recurInOrder(Node* currNode, std::ostream& out);
    void recurPostOrder(Node* currNode, std::ostream& out);
};

#include "AVLTree.cpp"

#endif /* AVLTREE_H_ */
