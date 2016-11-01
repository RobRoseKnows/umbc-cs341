#include "AVLForest.h"
#include "AVLTree.h"
#include "AVLTreeBase.h"
#include <fstream>
#include<iostream>

// we know data is either char or string
// we know numbers are either int or float

int main(int argc, char** argv) {

//    cerr << "Did run" << endl;

    AVLTree<string, int> tree = AVLTree<string, int>();

    cout << "Inserting 9" << endl;
    tree.insert(9, "9");
    cout << "Expected: 9" << endl;
    tree.print(AVLTreeBase::IN);
    cout << "Expected: 9" << endl;
    tree.print(AVLTreeBase::PRE);

    cout << "Inserting 2" << endl;
    tree.insert(2, "2");
    cout << "Expected 2 9" << endl;
    tree.print(AVLTreeBase::IN);
    cout << "Expected 9 2" << endl;
    tree.print(AVLTreeBase::PRE);

    cout << "Inserting 4" << endl;
    tree.insert(4, "4");
    cout << "Expected 2 4 9" << endl;
    tree.print(AVLTreeBase::IN);
    cout << "Expected 4 2 9" << endl;
    tree.print(AVLTreeBase::PRE);

    cout << "Inserting 10" << endl;
    tree.insert(10, "10");
    cout << "Expected 2 4 9 10" << endl;
    tree.print(AVLTreeBase::IN);
    cout << "Expected 4 2 9 10" << endl;
    tree.print(AVLTreeBase::PRE);

    cout << "Inserting 8" << endl;
    tree.insert(8, "8");
    cout << "Expected 2 4 8 9 10" << endl;
    tree.print(AVLTreeBase::IN);
    cout << "Expected 4 2 9 8 10" << endl;
    tree.print(AVLTreeBase::PRE);


    return 0;
}

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
//  inputFile.open(argv[1], std::ios::in);
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
//  rangeFile.open(argv[2], std::ios::in);
//
//  while(std::getline(rangeFile, line))
//  {
//    avlForest.print_range(std::cout, line);
//  }
//
//
//
//}
