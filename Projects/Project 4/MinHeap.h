/*
 * File:    MinHeap.h
 * Author:  Robert
 * Section: 3
 * Created: Nov 19, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * 
 */

#ifndef MINHEAP_H_
#define MINHEAP_H_

#include "Heap.h"

template<class T, int m_size>
class MinHeap : Heap<T, m_size> {
public:
    MinHeap();

    // The copy constructor required for Hack()
    MinHeap(const Heap<T, m_size> heap) { Heap(heap); };

    void PercolateUp(int index);
    void PercolateDown(int index);
};


#include "MinHeap.cpp"

#endif /* MINHEAP_H_ */
