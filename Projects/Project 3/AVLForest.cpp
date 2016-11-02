#include "AVLForest.h"

AVLForest::AVLForest()
{
}

AVLForest::~AVLForest()
{
}

void AVLForest::insert(std::string line)
{  
    vector<int> lineRecord;

    istringstream lineStream(line);

    while(lineStream) {
        string s;
        if(!getline(lineStream, s, ',')) break;

        int asInt;
        s >> asInt;

        lineRecord.push_back(asInt);
    }

    /*
     *   enum DataType{CHARACTER, STRING};
  enum NumberType{INTEGER, FLOAT};
     *
     */

    if(lineRecord.size() == 4)
    {
        // create a new tree and add it to the vector

        // This stores the index of the new tree mapped to its id value so we
        // can refer to it as an index in the forest vector.
        m_idToIndexMap.map(lineRecord[0], forest.size());

        AVLTreeBase* newBase = new AVLTreeBase;

        int printOrder = lineRecord[1];
        int dataType = lineRecord[2];
        int numberType[3];

        if(dataType == AVLTreeBase::CHARACTER && numberType == AVLTreeBase::INTEGER)
        {
            newBase = static_cast<AVLTree<char, int>*>(printOrder);
        }
        else if(dataType == AVLTreeBase::CHARACTER && numberType == AVLTreeBase::FLOAT)
        {
            newBase = static_cast<AVLTree<char, float>*>(printOrder);
        }
        else if(dataType == AVLTreeBase::STRING && numberType == AVLTreeBase::INTEGER)
        {
            newBase = static_cast<AVLTree<string, int>*>(printOrder);
        }
        else if(dataType == AVLTreeBase::STRING && numberType == AVLTreeBase::FLOAT)
        {
            newBase = static_cast<AVLTree<string, float>*>(printOrder);
        }
        else
        {
            throw runtime_error("Invalid case for AVLTree");
        }
    }
    else
    {
        // tree is in vector
        // we can proceed with insert

        int id = lineRecord[0];
        int dataType = lineRecord[1];
        int numberType = lineRecord[2];

        int index = m_idToIndexMap.find(id);

        AVLTreeBase* base = forest[index];

        if(dataType == AVLTreeBase::CHARACTER && numberType == AVLTreeBase::INTEGER)
        {
            AVLTree<char, int>* tree = static_cast<AVLTree<char, int>*>(base);
        }
        else if(dataType == AVLTreeBase::CHARACTER && numberType == AVLTreeBase::FLOAT)
        {
            base = static_cast<AVLTree<char, float>*>(printOrder);
        }
        else if(dataType == AVLTreeBase::STRING && numberType == AVLTreeBase::INTEGER)
        {
            base = static_cast<AVLTree<string, int>*>(printOrder);
        }
        else if(dataType == AVLTreeBase::STRING && numberType == AVLTreeBase::FLOAT)
        {
            base = static_cast<AVLTree<string, float>*>(printOrder);
        }
        else
        {
            throw runtime_error("Invalid case for AVLTree");
        }
    }
}

std::ostream& operator << (std::ostream& out, AVLForest& avlForest)
{
  // print all trees
  for(/* iterate over vector */)
  {
    if(/* character and integer */)
    {
      /* static_cast to <YourAVLTreeClassName<char, int>*> and print */
    }
    else if(/* character and float */)
    {
      /* static_cast to <YourAVLTreeClassName<char, float>*> and print */
    }
    else if(/* string and integer */)
    {
      /* static_cast to <YourAVLTreeClassName<std::string, int>*> and print */
    }
    else if((/* string and float */))
    {
      /* static_cast to <YourAVLTreeClassName<std::string, float>*> and print */
    }
    else
    {
      // invalid case
    }

    return out;
}
