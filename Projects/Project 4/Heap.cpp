#ifndef HEAP_CPP_
#define HEAP_CPP_

#include "Heap.h"

template<class T, int m_size>
Heap<T, m_size>::Heap() {
    this->m_currentSize = 0;
}




template<class T, int m_size>
Heap<T, m_size>::Heap(const Heap<T, m_size>& originHeap) {

    this->m_currentSize = originHeap.m_currentSize;

    for(int i = 0; i <= originHeap.m_currentSize; i++) {
        this->m_array[i] = originHeap.m_array[i];
    }
}



template<class T, int m_size>
bool Heap<T, m_size>::Contains(const T& needle) const {

    for(int i = ROOT_INDEX; i < this->m_currentSize + 1; i++) {

        if(this->m_array[i] == needle) {
            return true;
        }

    }

    return false;

}



template<class T, int m_size>
const T* Heap<T, m_size>::Find(const T& needle) const {

    for(int i = ROOT_INDEX; i < this->m_currentSize + 1; i++) {

        if(this->m_array[i] == needle) {
            return this->m_array[i];
        }

    }

}



template<class T, int m_size>
T& Heap<T, m_size>::Remove() {

    if(isEmpty()) {
        throw HeapUnderflow("No nodes to remove");
    }

    T* toReturn = m_array[ROOT_INDEX];

    // Move the node at the rear to the front and sets the rear node to NULL.
    this->m_array[ROOT_INDEX] = this->m_array[m_currentSize];
    this->m_array[m_currentSize] = NULL;

    this->m_currentSize--;

    PercolateDown(ROOT_INDEX);

    return *toReturn;

}



template<class T, int m_size>
void Heap<T, m_size>::Insert(T& insertable) {

    if(m_currentSize + 1 > m_size) {
        throw HeapOverflow("The heap is at max capacity.");
    }

    this->m_currentSize++;

    this->m_array[m_currentSize] = &insertable;

    PercolateUp(m_currentSize);

}





/************************************************************************************
 * PERCOLATE FUNCTIONS                                                              *
 ************************************************************************************/

// Code taken from class notes
template<class T, int m_size>
void Heap<T, m_size>::PercolateUp(int index) {

    // The parent index saved. This means we only have to call another method
    // logn + 1 times vs the 3logn we needed before.
    int parent = this->GetParentIndex(index);
    T* temp = this->m_array[index];

    for( ;
            index >= 1 &&                                   // Make sure we aren't above the top yet
            temp->CompareTo(*(this->m_array[ parent ])) < 0;    // If temp is less than the parent, knock us up
            index = parent ) {                              // Set index to the parent.

        parent = this->GetParentIndex(index);
        this->m_array[ index ] = this->m_array[ parent ];  // swap, from child to parent

    }

    this->m_array[ index ] = temp;


}



// Code taken from the class notes
template<class T, int m_size>
void Heap<T, m_size>::PercolateDown(int index) {

    // Saving the child allows us to save function calls by sacrificing a little memory
    int child = this->GetLeftChildIndex(index);
    T* tmp = this->m_array[ index ];

    for( ;
            child <= this->m_currentSize;              // Start by checking the left side if
            index = child ) {

        // Left child. This saves us function calls
        child = this->GetLeftChildIndex(index);

        // Check to see if the right child is less than the left child.
        if(
                child != this->m_currentSize &&                                             // Make sure we won't go out of bounds
                this->m_array[ child + 1 ]->CompareTo(*(this->m_array[ child ])) < 0 ) {        // Check if right is less than left

            // If it is, we want to switch the current node with that side so lets add 1.
            child++;

        }

        // If we should continue percolating down.
        if( tmp->CompareTo(*(this->m_array[ child ])) > 0 ) {

            this->m_array[ index ] = this->m_array[ child ];

        } else {

            break;

        }
    }

    this->m_array[ index ] = tmp;

}





/************************************************************************************
 * ALL THE GETTER FUNCTIONS THAT RETURN T POINTERS                                  *
 ************************************************************************************/


template<class T, int m_size>
T* Heap<T,m_size>::GetRoot() {
    return m_array[ROOT_INDEX];
}

template<class T, int m_size>
T* Heap<T,m_size>::GetLeftChild(int pin) {

    int indexCurr = FindIndex(pin);
    int indexChild = GetLeftChildIndex(indexCurr);

    if(indexChild > m_currentSize) {
        return NULL;
    }

    return m_array[indexChild];

}


template<class T, int m_size>
T* Heap<T,m_size>::GetRightChild(int pin) {

    int indexCurr = FindIndex(pin);
    int indexChild = GetRightChildIndex(indexCurr);

    if(indexChild > m_currentSize) {
        return NULL;
    }

    return m_array[indexChild];

}


template<class T, int m_size>
T* Heap<T,m_size>::GetParent(int pin) {

    int indexCurr = FindIndex(pin);
    int indexParent = GetParentIndex(indexCurr);

    return m_array[indexParent];

}




/************************************************************************************
 * ALL THE GETTER FUNCTIONS THAT RETURN INDEXES                                     *
 ************************************************************************************/

template<class T, int m_size>
int Heap<T,m_size>::GetLeftChildIndex(int index) const {

    return index * 2;

}

template<class T, int m_size>
int Heap<T,m_size>::GetRightChildIndex(int index) const {

    return index * 2 + 1;

}

template<class T, int m_size>
int Heap<T,m_size>::GetParentIndex(int index) const {

    return index / 2;

}


/************************************************************************************
 * UTILITY FUNCTIONS                                                                *
 ************************************************************************************/


template<class T, int m_size>
int Heap<T,m_size>::FindIndex(int pin) {

    for(int i = ROOT_INDEX; i < m_currentSize + 1; i++) {

        if(m_array[i]->GetKey() == pin) {
            return i;
        }

    }

}


// Checks to see if the heap is empty.
template<class T, int m_size>
bool Heap<T, m_size>::isEmpty() {
    return m_currentSize <= 0;
}


#endif /* HEAP_CPP_ */
