#ifndef LLAMA_CPP_
#define LLAMA_CPP_

#include<assert.h>
#include<string>
#include "Llama.h"

/*
 * File:    Llama.cpp
 * Author:  Robert Rose
 * Section: 3
 * Created: 10/1/16
 * E-mail:  robrose2@umbc.edu
 * Description:
 *
 */

using namespace std;

Llama::Llama() {
    LlamaNode* newNode = new LlamaNode;

    m_dataStart = newNode;
    m_firstNode = newNode;

    m_capacity = LN_SIZE;

    m_numNodes = 1;
    m_count = 0;
    m_capacity = LN_SIZE;
}

Llama::Llama(const Llama& other) {

}

Llama::~Llama() {
    LlamaNode* delNode = m_firstNode;
    LlamaNode* nextNode = delNode->m_next;

    while(nextNode != NULL) {
//        for(int i = 0; i < LN_SIZE; i++) {
//            delete delNode->arr[i];
//            delNode->arr[i] = NULL;
//        }

        delNode->m_next = NULL;
        delete delNode;
        delNode = nextNode;
        nextNode = delNode->m_next;
    }

    m_firstNode = NULL;
    m_dataStart = NULL;
}

int Llama::size() {
    return m_count;
}

void Llama::dump() {
    cerr << "***** Llama Stack Dump *****" << endl;
    cerr << "LN_SIZE = " << LN_SIZE << endl;
    cerr << "# of items in the stack = " << m_count << endl;
    cerr << "# of nodes created = " << LlamaNode::newCount << endl;
    cerr << "# of nodes destroyed = " << LlamaNode::deleteCount << endl;

    cerr << endl;

    if(m_dataStart == m_firstNode) {
        cerr << "This stack does not have an extra node." << endl;
    } else {
        cerr << "This stack has an extra node: " << m_firstNode << endl;
    }

    cerr << endl;

    cerr << "Stack contents, top to bottom" << endl;

    LlamaNode* itr = m_dataStart;

    do {
        cerr << "----- " << itr << "-----" << endl;

        // This chunk is so we know how many items we need to iterate
        // over in order to print out all the data.
        int numItems = LN_SIZE;
        if(itr == m_firstNode) {
            // If we're at the top of the stack, determine how many items are
            // in this LlamaNode
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

void Llama::push(const T& data) {
    if(m_count + 1 > m_capacity) {
        // This means we need to create a new Node to hold more data
        // Create new node and set all the relevant pointers
        LlamaNode* newNode = new LlamaNode;
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

T Llama::pop() {
    if(m_count == 0) {
        throw LlamaUnderflow("Cannot pop 0 items.");
    }

    // This is the capacity of all the nodes after the one we're currently in.
    // if m_count passes below the cut off, it means we need to change where the
    // data starts. This is also used to figure out when to get rid of the top node.
    int cutOff = (m_numNodes - 1) * LN_SIZE;

    T item;

    if(m_firstNode == m_dataStart) {
        item = m_dataStart->arr[(m_count % LN_SIZE) - 1];
    } else {
        item = m_dataStart->arr[(LN_SIZE - (m_count % LN_SIZE)) - 1];
    }

    m_count--;


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

void Llama::dup() {
    if(m_count == 0) {
        throw LlamaUnderflow("Cannot duplicate 0 items.");
    }

    // ABCD -> AABCD
    T toDupe = pop();
    push(toDupe);
    push(toDupe);
}

void Llama::swap() {
    if(m_count < 2) {
        throw LlamaUnderflow("Cannot swap < 2 items.");
    }

    // ABCD -> BACD
    T a = pop();
    T b = pop();
    push(a);
    push(b);
}

void Llama::rot() {
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

T Llama::peek(int offset) const {
    if(offset >= m_count) {
        throw LlamaUnderflow("Offset too large.");
    }

    LlamaNode* itr = m_dataStart;
    int itemsTotal = 0;

    int inFirstNode = 0;

    do {
        int numItemsInThisNode = LN_SIZE;

        if(itr == m_dataStart) {
            // If we're at the top of the stack, determine how many items are
            // in this LlamaNode and only add them to the total.
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
