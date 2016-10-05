#ifndef _LLAMANODE_H_
#define _LLAMANODE_H_

#define T string
#define LN_SIZE 4


/* File: LlamaNode.h

   UMBC CMSC 341 Fall 2016 Project 1

   This file has the class declaration for the LlamaNode class
   for Project 1. See project description for details.

   This file should not be modified in ANY way.

   When your program is graded, it will be compiled with the original 
   version of this file. Your program must work with the original. 

*/


#include <iostream>
using namespace std ;


//template <class T, int LN_SIZE>   // forward class declaration
class Llama ;


//template <class T, int LN_SIZE>
class LlamaNode {

   friend class Llama ;

   public:

   LlamaNode()  ;
   ~LlamaNode() ;

   static void report() ; 


   private:   

   static int newCount ;      // # of times constructor was called
   static int deleteCount ;   // # of times desctructor was called

   T arr[LN_SIZE] ;
   LlamaNode *m_next ;   

} ;

// TODO: Re-add templated code
//#include "LlamaNode.cpp"

#endif
