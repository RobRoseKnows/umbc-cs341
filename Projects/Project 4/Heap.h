#ifndef HEAP_H_
#define HEAP_H_

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

		// student-made functions below

	protected:

		// UML-required member variables
		// Doc says we can promote from private to protected if we override
		T* m_array;

		// student-made member variables

};

#include "Heap.cpp"
#endif /* HEAP_H_ */
