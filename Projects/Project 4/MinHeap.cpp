#ifndef MINHEAP_CPP_
#define MINHEAP_CPP_

/*
 * File:    MinHeap.cpp
 * Author:  Robert
 * Section: 3
 * Created: Nov 19, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * 
 */

#include "MinHeap.h"

template<class T, int m_size>
MinHeap<T, m_size>::MinHeap() {

    Heap();

}

template<class T, int m_size>
MinHeap<T, m_size>::MinHeap(const Heap<T, m_size> heap) {
    Heap(heap);
}




template<class T, int m_size>
void Heap<T, m_size>::PercolateUp(int index) {

    if(index == 0) {
        return;
    } else {

        int parent = GetParentIndex(index);

        if(m_array[index].CompareTo(m_array[parent]) > 0) {

            T* temp = m_array[parent];
            m_array[parent] = m_array[index];
            m_array[index] = temp;
            PercolateUp(parent);

        } else {

            return;

        }

    }

}

// Code taken from the class notes
template<class T, int m_size>
void Heap<T, m_size>::PercolateDown(int index) {

    int child;
    T tmp = m_array[ index ];

    for( ; index * 2 <= m_currentSize; index = child )
    {
        // Left child
        child = index * 2;

        // Check to see if the right child is less than the left child.
        if( child != m_currentSize && m_array[ child + 1 ] < m_array[ child ] )
            child++;

        // If we should continue percolating down.
        if( m_array[ child ] < tmp ) {

            m_array[ index ] = m_array[ child ];

        } else {

            break;

        }
    }
    m_array[ index ] = tmp;

}


#endif /* MINHEAP_CPP_ */
