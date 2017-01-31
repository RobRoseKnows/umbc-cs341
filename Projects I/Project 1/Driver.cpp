/*
 * File:    Llama.cpp
 * Author:  Robert Rose
 * Section: 3
 * Created: 10/1/16
 * E-mail:  robrose2@umbc.edu
 * Description:
 *
 */

#include <iostream>
#include <string>
using namespace std ;

#include "Llama.h"

int main() {

   Llama<string, 4> S;

   // Push a bunch of strings

   S.push("cdef") ;
   S.push("yzab") ;
   S.push("vwx") ;
   S.push("stu") ;

   S.push("pqr") ;
   S.push("mno") ;
   S.push("jkl") ;
   S.push("ghi") ;

   S.push("def") ;
   S.push("abc") ;
   S.dump() ;


   cerr << "\n***** Dump using peek *****" ;
   int size = S.size() ;
   cerr << "\nsize = " << size << endl ;

   for (int i=0 ; i < S.size() ; i++) {
      cerr << i << ": " << S.peek(i) << endl ;
   }

   cerr << endl;

   // Pop some strings off
   string s1 ;

   cerr << "\n***** Pop Test *****\n" ;
   s1 = S.pop() ;
   cerr << "popped " << s1 << endl ;
   s1 = S.pop() ;
   cerr << "popped " << s1 << endl ;
   s1 = S.pop() ;
   cerr << "popped " << s1 << endl ;

   cerr << endl;

   S.dump() ;  // should have "extra" node

   cerr << "\n***** Push Test *****\n" ;
   S.push("x789") ;
   S.push("x456") ;
   S.push("x123") ;

   cerr << endl;

   S.dump() ;  // should use extra node


   cerr << "\n***** Pop Test *****\n" ;
   s1 = S.pop() ;
   cerr << "popped " << s1 << endl ;
   s1 = S.pop() ;
   cerr << "popped " << s1 << endl ;

   cerr << endl;

   S.dump() ;  // should have extra node again


   cerr << "\n***** Pop Test *****\n" ;
   s1 = S.pop() ;
   cerr << "popped " << s1 << endl ;
   s1 = S.pop() ;
   cerr << "popped " << s1 << endl ;

   cerr << endl;

   S.dump() ;  // extra node should be gone

   return 0 ;
}
