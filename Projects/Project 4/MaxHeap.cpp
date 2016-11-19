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
    // TODO Auto-generated constructor stub

}

template<class T, int m_size>
MaxHeap<T, m_size>::MaxHeap(const Heap<T, m_size> heap) {
    Heap(heap);
}
