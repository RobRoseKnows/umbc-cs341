#ifndef LLAMA_CPP_
#define LLAMA_CPP_

#include<assert.h>
#include<string>
#include "Llama.h"

/*
 * File:    Llama<T, LN_SIZE>.cpp
 * Author:  Robert Rose
 * Section: 3
 * Created: 10/1/16
 * E-mail:  robrose2@umbc.edu
 * Description:
 *
 */

using namespace std;

template <class T, int LN_SIZE>
Llama<T, LN_SIZE>::Llama() {
    LlamaNode<T, LN_SIZE>* newNode = new LlamaNode<T, LN_SIZE>;

    m_dataStart = newNode;
    m_firstNode = newNode;

    m_capacity = LN_SIZE;

    m_numNodes = 1;
    m_count = 0;
    m_capacity = LN_SIZE;
}


template <class T, int LN_SIZE>
Llama<T, LN_SIZE>::Llama(const Llama<T, LN_SIZE>& other) {

}

template <class T, int LN_SIZE>
Llama<T, LN_SIZE>::~Llama<T, LN_SIZE>() {
    LlamaNode<T, LN_SIZE>* delNode = m_firstNode;
    LlamaNode<T, LN_SIZE>* nextNode = delNode->m_next;

    while(nextNode != NULL) {
//        for(int i = 0; i < LN_SIZE; i++) {
//            delete delNode->arr[i];
//        }

        delNode->m_next = NULL;
        delete delNode;
        delNode = nextNode;
        nextNode = delNode->m_next;
    }

    m_firstNode = NULL;
    m_dataStart = NULL;
}

template <class T, int LN_SIZE>
int Llama<T, LN_SIZE>::size() {
    return m_count;
}

template <class T, int LN_SIZE>
int Llama<T, LN_SIZE>::capacity() {
    return m_capacity;
}

template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>::dump() {
    cerr << "***** Llama Stack Dump *****" << endl;
    cerr << "LN_SIZE = " << LN_SIZE << endl;
    cerr << "# of items in the stack = " << m_count << endl;
    cerr << "# of nodes created = " << LlamaNode<T, LN_SIZE>::newCount << endl;
    cerr << "# of nodes destroyed = " << LlamaNode<T, LN_SIZE>::deleteCount << endl;

    cerr << endl;

    if(m_dataStart == m_firstNode) {
        cerr << "This stack does not have an extra node." << endl;
    } else {
        cerr << "This stack has an extra node: " << m_firstNode << endl;
    }

    cerr << endl;

    cerr << "Stack contents, top to bottom" << endl;

    LlamaNode<T, LN_SIZE>* itr = m_dataStart;

    do {
        cerr << "----- " << itr << "-----" << endl;

        // This chunk is so we know how many items we need to iterate
        // over in order to print out all the data.
        int numItems = LN_SIZE;
        if(itr == m_firstNode) {
            // If we're at the top of the stack, determine how many items are
            // in this Llama<T, LN_SIZE>Node
            numItems = m_count % LN_SIZE;
        }

        // Print them in reverse order.
        for(int i = numItems; i > 0; i--) {
            cerr << itr->arr[i-1] << endl;
        }

        itr = itr->m_next;
    } while(itr != NULL); // Continue until the end of the nodes.

    cerr << "----- bottom of stack -----" << endl;
    cerr << endl;
    cerr << "*****************************" << endl;
}

template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>::push(const T& data) {
    if(m_count + 1 > m_capacity) {
        // This means we need to create a new Node to hold more data
        // Create new node and set all the relevant pointers
        LlamaNode<T, LN_SIZE>* newNode = new LlamaNode<T, LN_SIZE>;
        newNode->m_next = m_firstNode;
        m_firstNode = newNode;
        m_dataStart = newNode;

        m_dataStart->arr[m_count % LN_SIZE] = data;

        m_capacity += LN_SIZE;
        m_count++;
        m_numNodes++;
    } else if(m_count % LN_SIZE == 0) {
        // This means the current node in m_dataStart has filled up with data and
        // we need to overflow to the first node.
        m_dataStart = m_firstNode;
        m_dataStart->arr[m_count % LN_SIZE] = data;
        m_count++;
    } else {
        // We can just add the data to the node we're currently pointing at
        // to hold data.
        m_dataStart->arr[m_count % LN_SIZE] = data;
        m_count++;
    }
}

template <class T, int LN_SIZE>
T Llama<T, LN_SIZE>::pop() {
    if(m_count == 0) {
        throw LlamaUnderflow("Cannot pop 0 items.");
    }

    // This is the capacity of all the nodes after the one we're currently in.
    // if m_count passes below the cut off, it means we need to change where the
    // data starts. This is also used to figure out when to get rid of the top node.
    int cutOff = (m_numNodes - 1) * LN_SIZE;

    T item;

    m_count--;

//    if(m_firstNode == m_dataStart) {
        item = m_dataStart->arr[m_count % LN_SIZE];
//    } else {
//        item = m_dataStart->arr[(LN_SIZE - (m_count % LN_SIZE)) - 1];
//    }


    if((m_capacity - m_count == LN_SIZE + LN_SIZE/2) && m_dataStart != m_firstNode) {
        m_firstNode->m_next = NULL;
        delete m_firstNode;
        m_firstNode = m_dataStart;
        m_numNodes--;
        m_capacity -= LN_SIZE;
    }

    if(m_count == cutOff) {
        m_dataStart = m_dataStart->m_next;
    }

    return item;
}

// I know there aren't the best way of doing it but I'm running out of time.
template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>::dup() {
    if(m_count == 0) {
        throw LlamaUnderflow("Cannot duplicate 0 items.");
    }

    // ABCD -> AABCD
    T toDupe = pop();
    push(toDupe);
    push(toDupe);
}

template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>::swap() {
    if(m_count < 2) {
        throw LlamaUnderflow("Cannot swap < 2 items.");
    }

    // ABCD -> BACD
    T a = pop();
    T b = pop();
    push(a);
    push(b);
}

template <class T, int LN_SIZE>
void Llama<T, LN_SIZE>::rot() {
    if(m_count < 3) {
        throw LlamaUnderflow("Cannot rotate < 3 items.");
    }

    // ABCD -> CABD
    T a = pop();
    T b = pop();
    T c = pop();
    push(b);
    push(a);
    push(c);
}

template <class T, int LN_SIZE>
T Llama<T, LN_SIZE>::peek(int offset) const {
    if(offset >= m_count) {
        throw LlamaUnderflow("Offset too large.");
    }

    LlamaNode<T, LN_SIZE>* itr = m_dataStart;
    int itemsTotal = 0;

    int inFirstNode = 0;

    do {
        int numItemsInThisNode = LN_SIZE;

        if(itr == m_dataStart) {
            // If we're at the top of the stack, determine how many items are
            // in this Llama<T, LN_SIZE>Node and only add them to the total.
            itemsTotal += m_count % LN_SIZE;
            numItemsInThisNode = m_count % LN_SIZE;

            // Store the number of items in the first node so we can offset the
            // index in the array.
            inFirstNode = m_count % LN_SIZE;
        } else {
            itemsTotal += LN_SIZE;
        }

        // If the total number of items encompassed by the nodes traversed passes
        // above the offset, we know the value we want is inside the node.
        if(itemsTotal > offset) {
            // I have a feeling there is some nice, elegant combination that will look a lot prettier than this
            // monstrosity but this was what I came up with and I don't need to spend several more hours looking
            // for the unicorn.
            return itr->arr[numItemsInThisNode - ((offset - (itemsTotal == inFirstNode ? 0 : inFirstNode)) % LN_SIZE) - 1];
        } else {
            itr = itr->m_next;
        }
    } while(itr != NULL);

    // This shouldn't happen because we check for overflow at the beginning. Just in case.
    return NULL;
}

#endif
