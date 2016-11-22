/*
 * File:    MaxHeap.cpp
 * Author:  Robert
 * Section: 3
 * Created: Nov 19, 2016
 * E-mail:  robrose2@umbc.edu
 * Description:
 * 
 */

#include "MaxHeap.h"

template<class T, int m_size>
MaxHeap<T, m_size>::MaxHeap() {

    m_array = T[m_size + 1];
    m_currentSize = 0;

}

template<class T, int m_size>
MaxHeap<T, m_size>::MaxHeap(const Heap<T, m_size> heap) {

    Heap(heap);

}



// Code taken from the class notes.
template<class T, int m_size>
void MaxHeap<T, m_size>::PercolateUp(int index) {

    T temp = m_array[index];

    for( ; index >= 1 && temp.CompareTo(m_array[ index / 2 ]) > 0; index /= 2 )
        m_array[ index ] = m_array[ index / 2 ]; // swap, from child to parent
    m_array[ index ] = temp;

}




// Code taken from the class notes
template<class T, int m_size>
void MaxHeap<T, m_size>::PercolateDown(int index) {

    int child;
    T tmp = m_array[ index ];

    for( ; index * 2 <= m_currentSize; index = child )
    {
        // Left child
        child = index * 2;

        // Check to see if the right child is greater than the left child.
        if( child != m_currentSize && m_array[ child + 1 ].CompareTo(m_array[ child ]) > 0 )
            child++;

        // If we should continue percolating down.
        if( m_array[ child ] > tmp ) {

            m_array[ index ] = m_array[ child ];

        } else {

            break;

        }
    }

    m_array[ index ] = tmp;

}
