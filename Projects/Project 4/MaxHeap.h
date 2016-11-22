/*
 * File:    MaxHeap.h
 * Author:  Robert
 * Section: 3
 * Created: Nov 19, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * 
 */

#ifndef MAXHEAP_H_
#define MAXHEAP_H_

#include "Heap.h"

template<class T, int m_size>
class MaxHeap : Heap<T, m_size> {
public:
    MaxHeap();

    // The copy constructor is required for Hack()
    MaxHeap(const Heap<T, m_size> heap);


    void PercolateUp(int index);
    void PercolateDown(int index);

};

#endif /* MAXHEAP_H_ */
