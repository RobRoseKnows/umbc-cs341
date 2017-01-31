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
    typename Heap<T, m_size>::Heap();
}



// Code taken from class notes
template<class T, int m_size>
void MinHeap<T, m_size>::PercolateUp(int index) {

    // The parent index saved. This means we only have to call another method
    // logn + 1 times vs the 3logn we needed before.
    int parent = this->GetParentIndex(index);
    T temp = this->m_array[index];

    for( ;
            index >= 1 &&                                   // Make sure we aren't above the top yet
            temp.CompareTo(this->m_array[ parent ]) < 0;    // If temp is less than the parent, knock us up
            index = parent ) {                              // Set index to the parent.

        parent = this->GetParentIndex(index);
        this->m_array[ index ] = this->m_array[ parent ];  // swap, from child to parent

    }

    this->m_array[ index ] = temp;


}

// Code taken from the class notes
template<class T, int m_size>
void MinHeap<T, m_size>::PercolateDown(int index) {

    // Saving the child allows us to save function calls by sacrificing a little memory
    int child = this->GetLeftChildIndex(index);
    T tmp = this->m_array[ index ];

    for( ;
            child <= this->m_currentSize;              // Start by checking the left side if
            index = child ) {

        // Left child. This saves us function calls
        child = this->GetLeftChildIndex(index);

        // Check to see if the right child is less than the left child.
        if(
                child != this->m_currentSize &&                                             // Make sure we won't go out of bounds
                this->m_array[ child + 1 ].CompareTo(this->m_array[ child ]) < 0 ) {        // Check if right is less than left

            // If it is, we want to switch the current node with that side so lets add 1.
            child++;

        }

        // If we should continue percolating down.
        if( tmp.CompareTo(this->m_array[ child ]) > 0 ) {

            this->m_array[ index ] = this->m_array[ child ];

        } else {

            break;

        }
    }

    this->m_array[ index ] = tmp;

}


#endif /* MINHEAP_CPP_ */
