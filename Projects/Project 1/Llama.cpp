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
    LlamaNode newNode = new LlamaNode;

    m_dataStart = *newNode;
    m_firstNode = *newNode;

    m_capacity = LN_SIZE;

    m_numNodes = 1;
}

Llama::Llama(const Llama& other) {

}

Llama::~Llama() {
    LlamaNode* delNode = m_firstNode;
    LlamaNode* nextNode = delNode->m_next;

    while(nextNode != NULL) {
        for(int i = 0; i < LN_SIZE; i++) {
            delete delNode->arr[i];
            delNode->arr[i] = NULL;
        }

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

}

void Llama::push(const T& data) {
    if(m_count + 1 > m_capacity) {
        // This means we need to create a new Node to hold more data
        // Create new node and set all the relevant pointers
        LlamaNode newNode = new LlamaNode();
        newNode.m_next = *m_firstNode;
        m_firstNode = *newNode;
        m_dataStart = *newNode;

        newNode.arr[m_count + 1 % LN_SIZE] = data;

        m_capacity += LN_SIZE;
        m_count++;
        m_numNodes++;
    } else if(m_count + 1 % LN_SIZE == 0) {
        // This means the current node in m_dataStart has filled up with data and
        // we need to overflow to the first node.
        m_dataStart = m_firstNode;
        m_dataStart->arr[m_count + 1 % LN_SIZE] = data;
        m_count++;
    } else {
        // We can just add the data to the node we're currently pointing at
        // to hold data.
        m_dataStart->arr[(m_count + 1 % LN_SIZE) - 1] = data;
        m_count++;
    }
}

T Llama::pop() {
    if(m_count == 0) {
        throw LlamaUnderflow("Cannot pop 0 items.");
    }

    T item = m_dataStart[(m_count % LN_SIZE) - 1];
    m_count--;
    return item;
}

void Llama::dup() {
    if(m_count == 0) {
        throw LlamaUnderflow("Cannot dupe 0 items.");
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
    // Which stack we have to check
    int stackOn = offset / LN_SIZE;
    LlamaNode* checkNode = m_dataStart;

    for(int i = 0; i < stackOn; i++) {
        checkNode = checkNode->m_next;
    }

    return checkNode->arr[offset % LN_SIZE];
}

#endif
