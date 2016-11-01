#include "AVLForest.h"
#include "AVLTree.h"
#include "AVLTreeBase.h"

#include <fstream>
#include <iostream>
#include <string>


int main(int arc, char** argv) {
    std::ostream out;

    AVLTree<string, int> tree = AVLTree<string, int>();
    tree.insert(9, "9");
    tree.print(AVLTreeBase::IN, out);
    tree.print(AVLTreeBase::PRE, out);

    tree.insert(10,"10");
    tree.print(AVLTreeBase::IN, out);
    tree.print(AVLTreeBase::PRE, out);

    tree.insert(3, "3");
    tree.print(AVLTreeBase::IN, out);
    tree.print(AVLTreeBase::PRE, out);

    tree.insert(3, "2");
    tree.print(AVLTreeBase::IN, out);
    tree.print(AVLTreeBase::PRE, out);

    tree.insert(3, "1");
    tree.print(AVLTreeBase::IN, out);
    tree.print(AVLTreeBase::PRE, out);

    tree.insert(11, "11");
    tree.print(AVLTreeBase::IN, out);
    tree.print(AVLTreeBase::PRE, out);

    tree.insert(8, "8");
    tree.print(AVLTreeBase::IN, out);
    tree.print(AVLTreeBase::PRE, out);

    tree.insert(12, "12");
    tree.print(AVLTreeBase::IN, out);
    tree.print(AVLTreeBase::PRE, out);


}


// we know data is either char or string
// we know numbers are either int or float

//int main(int argc, char** argv)
//{
//  // avl forest to be populated
//  AVLForest avlForest;
//
//  // read input from file
//  std::ifstream inputFile;
//  std::ifstream rangeFile;
//  std::string line;
//
//  // open file for reading
//  inputFile.open(argv[1], std::ios::IN);
//
//  // read all lines
//  while(std::getline(inputFile, line))
//  {
//    // process each line
//    avlForest.insert(line);
//  }
//
//  // print all trees
//  std::cout<<"\n==============\n";
//  std::cout<<"PRINTING TREES";
//  std::cout<<"\n==============\n";
//  std::cout<<avlForest;
//
//  // print ranges
//  std::cout<<"\n===============\n";
//  std::cout<<"PRINTING RANGES";
//  std::cout<<"\n===============\n";
//  rangeFile.open(argv[2], std::ios::IN);
//
//  while(std::getline(rangeFile, line))
//  {
//    avlForest.print_range(std::cout, line);
//  }
//}
