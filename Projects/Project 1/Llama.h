#ifndef _LLAMA_H_
#define _LLAMA_H_

/* File: Llama.h

   UMBC CMSC 341 Fall 2016 Project 1

   This file has the class declaration for the LlamaNode class
   for Project 1. See project description for details.

   You may add public and private data members to the Llama class.

   You may add public and private member functions to the Llama class.

*/


#include <stdexcept>
#include <string>
#include "LlamaNode.h"

using namespace std ;


class LlamaUnderflow : public std::out_of_range {

   public:

   LlamaUnderflow(const string& what) : std::out_of_range(what) { }

} ;

template <class T, int LN_SIZE>
class Llama {

   public:

   Llama() ;
   Llama(const Llama& other) ;   // copy constructor
   ~Llama() ;


   int size() ; 
   void dump() ;
   void push(const T& data) ;
   T pop() ;


   void dup() ;    //  (top) A B C D -> A A B C D
   void swap() ;   //  (top) A B C D -> B A C D 
   void rot() ;    //  (top) A B C D -> C A B D


   T peek(int offset) const ;


   // overloaded assignment operator
   //
   const Llama& operator=(const Llama& rhs) ;


   //
   // Add your public member functions & public data mebers here:
   //

   int capacity();

   private:

   // This uses an inverted stack. The "dataStart" pointer refers to
   // the first node with data in the series
   LlamaNode<T,LN_SIZE> * m_dataStart;
   // The "firstNode" pointer refers to the first node used in the
   // program, even if it's empty.
   LlamaNode<T,LN_SIZE> * m_firstNode;

   // The number of items in the node.
   int m_count ;
   int m_capacity ;
   int m_numNodes ;

   //
   // Add your private member functions & private data mebers here:
   //


} ;


#include "Llama.cpp"


#endif
