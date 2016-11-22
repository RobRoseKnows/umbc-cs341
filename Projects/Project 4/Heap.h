#ifndef HEAP_H_
#define HEAP_H_

#include<stdexcept>
#include<string>

class HeapUnderflow : public std::underflow_error {

   public:

   HeapUnderflow(const std::string& what) : std::underflow_error(what) { }

} ;

template<class T, int m_size> class Heap{

	public:

		// required functions by UML
		Heap();
		Heap(const Heap<T, m_size>& origHeap);
		bool Contains(const T& needle) const;	
		const T* Find(const T& needle) const;
		T& Remove();	
		void Insert(T& insertable);		
		void PercolateUp(int index);
		void PercolateDown(int index);

	protected:

		// UML-required member variables
		// Doc says we can promote from private to protected if we override
		T* m_array;
		int m_currentSize;

		static const int ROOT_INDEX = 1;

        T* GetRoot();

        T* GetLeftChild(int pin);
        T* GetRightChild(int pin);
        T* GetParent(int pin);

        int GetLeftChildIndex(int index) const;
        int GetRightChildIndex(int index) const;
        int GetParentIndex(int index) const;


        int FindIndex(int pin);

        bool isEmpty();

};

#include "Heap.cpp"
#endif /* HEAP_H_ */
