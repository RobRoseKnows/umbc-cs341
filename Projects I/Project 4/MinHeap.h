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
class MinHeap : public Heap<T, m_size> {
public:
    MinHeap();

    // The copy constructor required for Hack()
    MinHeap(const Heap<T, m_size>& heap) : Heap<T, m_size>::Heap(heap) {};

    // This is used in adding a new item to the heap. It goes up through the heap
    // to make sure the maximum is at the top.
    //
    // Takes:       The index of the newly added item.
    // Returns:     Nothing but the m_array is a fully valid heap.
    void PercolateUp(int index);

    // This is used in deleting the root node. It goes down through the heap bringing
    // the last node to the point where the heap is valid.
    //
    // Takes: the new spot of the last node.
    // Returns:     Nothing but the heap is fully valid.
    void PercolateDown(int index);
};


#include "MinHeap.cpp"

#endif /* MINHEAP_H_ */
