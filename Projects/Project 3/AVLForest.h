#ifndef _AVLFOREST_H_
#define _AVLFOREST_H_

/* include your tree implementation  */
#include <vector>
#include <string>
#include <map>

#include "AVLTreeBase.h"

using namespace std;

class AVLForest
{
  // vector of trees
  // we use a non-templated base class so we can hold all template instantiations
  std::vector<AVLTreeBase*> forest;
  std::map<int, int> m_idToIndexMap;

  // other data memebers
  
public:
  AVLForest();
  ~AVLForest();

  void insert(std::string);
  void print_range(std::ostream&, std::string);
  friend std::ostream& operator << (std::ostream&, AVLForest&);

  // other member functions
};

#endif /* _AVLFOREST_H_ */
