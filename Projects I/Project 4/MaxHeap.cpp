#ifndef MAXHEAP_CPP_
#define MAXHEAP_CPP_

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

    typename Heap<T, m_size>::Heap();

}



// Code taken from the class notes.
template<class T, int m_size>
void MaxHeap<T, m_size>::PercolateUp(int index) {

    T temp = this->m_array[index];

    for( ;
            index >= 1 &&                                                       // Make sure we aren't above the top yet
            temp.CompareTo(this->m_array[ this->GetParentIndex(index) ]) > 0;         // If temp is greater than the parent, knock us up
            index = this->GetParentIndex(index) ) {                             // Set index to the parent.

        this->m_array[ index ] = this->m_array[ this->GetParentIndex(index) ]; // swap, from child to parent

    }

    this->m_array[ index ] = temp;

}




// Code taken from the class notes
template<class T, int m_size>
void MaxHeap<T, m_size>::PercolateDown(int index) {

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
                this->m_array[ child + 1 ].CompareTo(this->m_array[ child ]) > 0 ) {        // Check if right is greater than left

            // If it is, we want to switch the current node with that side so lets add 1.
            child++;

        }

        // If we should continue percolating down.
        if( tmp.CompareTo(this->m_array[ child ]) < 0 ) {

            this->m_array[ index ] = this->m_array[ child ];

        } else {

            break;

        }
    }

    this->m_array[ index ] = tmp;

}


#endif /* MAXHEAP_CPP_ */
