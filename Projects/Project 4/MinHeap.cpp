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
    // TODO Auto-generated constructor stub

}

template<class T, int m_size>
MinHeap<T, m_size>::MinHeap(const Heap<T, m_size> heap) {
    Heap(heap);
}

#endif /* MINHEAP_CPP_ */
