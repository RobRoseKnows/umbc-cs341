#ifndef HEAP_CPP_
#define HEAP_CPP_

#include "Heap.h"

template<class T, int m_size>
Heap<T, m_size>::Heap() {
    m_array = T[m_size + 1];
    m_currentSize = 0;
}

template<class T, int m_size>
Heap<T, m_size>::Heap(const Heap<T, m_size>& origHeap) {
    m_array = origHeap.m_array;
    m_currentSize = origHeap.m_currentSize;
}

template<class T, int m_size>
bool Heap<T, m_size>::Contains(const T& needle) const {

    for(int i = ROOT_INDEX; i < m_currentSize + 1; i++) {

        if(m_array[i] == needle) {
            return true;
        }

    }

    return false;

}


template<class T, int m_size>
const T* Heap<T, m_size>::Find(const T& needle) const {

    for(int i = ROOT_INDEX; i < m_currentSize + 1; i++) {

        if(m_array[i] == needle) {
            return m_array[i];
        }

    }

}

template<class T, int m_size>
T& Heap<T, m_size>::Remove() {

    if(isEmpty()) {
        throw HeapUnderflow("No nodes to remove");
    }

    T& toReturn = m_array[ROOT_INDEX];

    m_array[ROOT_INDEX] = m_array[m_currentSize];
    m_array[m_currentSize] = NULL;

    m_currentSize--;

    PercolateDown(ROOT_INDEX);

}

template<class T, int m_size>
void Heap<T, m_size>::Insert(T& insertable) {

    m_currentSize++;

    m_array[m_currentSize] = insertable;

    PercolateUp(m_currentSize);

}




template<class T, int m_size>
T* Heap<T,m_size>::GetRoot() {
    return m_array[ROOT_INDEX];
}

template<class T, int m_size>
T* Heap<T,m_size>::GetLeftChild(int pin) {

    int indexCurr = FindIndex(pin);
    int indexChild = indexCurr * 2;

    return m_array[indexChild];

}


template<class T, int m_size>
T* Heap<T,m_size>::GetRightChild(int pin) {

    int indexCurr = FindIndex(pin);
    int indexChild = indexCurr * 2 + 1;

    return m_array[indexChild];

}


template<class T, int m_size>
T* Heap<T,m_size>::GetParent(int pin) {

    int indexCurr = FindIndex(pin);
    int indexChild = indexCurr / 2;

    return m_array[indexChild];

}


template<class T, int m_size>
int Heap<T,m_size>::GetLeftChildIndex(int index) {

    return index * 2;

}

template<class T, int m_size>
int Heap<T,m_size>::GetRightChildIndex(int index) {

    return index * 2 + 1;

}

template<class T, int m_size>
int Heap<T,m_size>::GetParentIndex(int index) {

    return index / 2;

}




template<class T, int m_size>
int Heap<T,m_size>::FindIndex(int pin) {

    for(int i = ROOT_INDEX; i < m_currentSize + 1; i++) {

        if(m_array[i]->GetKey() == pin) {
            return i;
        }

    }

}



template<class T, int m_size>
bool Heap<T, m_size>::isEmpty() {
    return m_currentSize <= 0;
}


#endif /* HEAP_CPP_ */
