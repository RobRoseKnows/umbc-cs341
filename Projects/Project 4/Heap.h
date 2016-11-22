#ifndef HEAP_H_
#define HEAP_H_

#include<stdexcept>
#include<string>



// An exception that is thrown when you try to do something with too few items
// in the heap.
class HeapUnderflow : public std::underflow_error {

public:

    HeapUnderflow(const std::string& what) : std::underflow_error(what) { }

} ;


// An exception that is thrown when you try to do something with too many items
// in the heap.
class HeapOverflow : public std::overflow_error {

public:

    HeapOverflow(const std::string& what) : std::overflow_error(what) { }

} ;





template<class T, int m_size> class Heap{

public:

    // required functions by UML
    Heap();
    Heap(const Heap<T, m_size>& origHeap);


    // The contains method returns true if the needle is found in the Heap.
    //
    // Takes:       an object to find in the heap.
    // Returns:     true if the object is found, false otherwise.
    bool Contains(const T& needle) const;


    // The contains method returns an object pointer of type T if the needle is
    // in the Heap. This function may take up to O(n).
    //
    // Takes:       an object to find in the heap.
    // Returns:     a pointer to the object found in the heap.
    const T* Find(const T& needle) const;

    // Removes and returns a min/max value T (by reference) from the heap. In the
    // process of removal, the heap is updated to maintain heap order.
    //
    // Takes:       m_array must not be empty (if it is, a HeapUnderflow error is
    //              thrown.
    // Returns:     An object of type T that is removed from the heap.
    T& Remove();

    // Given a T, insert will insert the new object into the heap. If needed, the
    // object will percolate up.
    //
    // Takes:       a Node to insert into the heap
    // Returns:     nothing. But m_array should be a fully valid heap.
    void Insert(T& insertable);

    // This is used in adding a new item to the heap. This is overriden by
    // MinHeap and MaxHeap to implement their own changes. For the implementation
    // in Heap, it goes through the heap from the point where a new item was
    // added to make sure the minimum is at the top.
    //
    // Takes:       The index of the newly added item.
    // Returns:     Nothing but the m_array is a fully valid heap.
    void PercolateUp(int index);

    // This is used in adding a new item to the heap. This is overriden by
    // MinHeap and MaxHeap to implement their own changes. For the implementation
    // in Heap, it goes down through the heap from the point where an item was
    // deleted to make sure all levels of the heap are valid.
    //
    // Takes: the new spot of the last node.
    // Returns:     Nothing but the heap is fully valid.
    void PercolateDown(int index);

protected:

    // UML-required member variables
    // Doc says we can promote from private to protected if we override
    T* m_array[m_size + 1];
    int m_currentSize;

    T* GetRoot();

    // These get the pointers to a nodes children and parents based on the pin
    // number.
    //
    // Take:        The pin number of a node.
    // Returns:     A pointer to that node's child or parent. NULL if it has none.
    T* GetLeftChild(int pin);
    T* GetRightChild(int pin);
    T* GetParent(int pin);

    int GetLeftChildIndex(int index) const;
    int GetRightChildIndex(int index) const;
    int GetParentIndex(int index) const;


    int FindIndex(int pin);

    bool isEmpty();
private:

    // This is to prevent magic numbers.
    static const int ROOT_INDEX = 1;
};

#include "Heap.cpp"
#endif /* HEAP_H_ */
