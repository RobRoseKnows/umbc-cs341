#include "AVLForest.h"
#include "AVLTree.h"

using namespace std;

AVLForest::AVLForest()
{
}

AVLForest::~AVLForest()
{
}

void AVLForest::insert(std::string line)
{  
    vector<string> lineRecord;

    istringstream lineStream(line);

    // This takes the line and splits it into a vector so that we can get the
    // individual values.
    while(lineStream) {
        string s;
        if(!getline(lineStream, s, ',')) break;

        lineRecord.push_back(s);
    }

    // Check to see if this is creating a new tree.
    if(lineRecord.size() == 4)
    {
        // create a new tree and add it to the vector

        AVLTreeBase* newBase = new AVLTreeBase;

        int index = ::atoi(lineRecord[0].c_str());
        int printOrder = ::atoi(lineRecord[1].c_str());
        int dataType = ::atoi(lineRecord[2].c_str());
        int numberType = ::atoi(lineRecord[3].c_str());


        int metaData = {
                forest.size(),
                dataType,
                numberType
        };
//        int metaData[3];
//        metaData[0] = forest.size();
//        metaData[1] = dataType;
//        metaData[2] = numberType;

        // This stores the index of the new tree mapped to its id value so we
        // can refer to it as an index in the forest vector.
        m_idToMetaDataMap.map(index, metaData);

        if(switchDataType(dataType) == AVLTreeBase::CHARACTER && switchNumType(numberType) == AVLTreeBase::INTEGER)
        {

            AVLTree<char, int>* tree = static_cast<AVLTree<char, int>*>(newBase);

            tree->m_printOrder = switchPrintOrder(printOrder);

            forest.push_back(tree);

        }
        else if(switchDataType(dataType) == AVLTreeBase::CHARACTER && switchNumType(numberType) == AVLTreeBase::FLOAT)
        {

            AVLTree<char, float>* tree = static_cast<AVLTree<char, float>*>(newBase);

            tree->m_printOrder = switchPrintOrder(printOrder);

            forest.push_back(tree);

        }
        else if(switchDataType(dataType) == AVLTreeBase::STRING && switchNumType(numberType) == AVLTreeBase::INTEGER)
        {

            AVLTree<string, int>* tree = static_cast<AVLTree<string, int>*>(newBase);

            tree->m_printOrder = switchPrintOrder(printOrder);

            forest.push_back(tree);

        }
        else if(switchDataType(dataType) == AVLTreeBase::STRING && switchNumType(numberType) == AVLTreeBase::FLOAT)
        {

            AVLTree<string, float>* tree = static_cast<AVLTree<string, float>*>(newBase);

            tree->m_printOrder = switchPrintOrder(printOrder);

            forest.push_back(tree);

        }
        else
        {

            cerr << "Invalid tree types" << endl;

        }
    }
    else
    {
        // tree is in vector
        // we can proceed with insert

        int id = ::atoi(lineRecord[0].c_str());
        string data = lineRecord[1];
        string key = lineRecord[2];

        int metaData[] = m_idToMetaDataMap.find(id);

        AVLTreeBase* base = forest[metaData[0]];
        AVLTreeBase::DataType dataType = switchDataType(metaData[1]);
        AVLTreeBase::NumberType keyType = switchNumType(metaData[2]);


        if(dataType == AVLTreeBase::CHARACTER && keyType == AVLTreeBase::INTEGER)
        {

            AVLTree<char, int>* tree = static_cast<AVLTree<char, int>*>(base);

            int thisKey = ::atoi(key.c_str());

            char thisData = data.c_str()[0];

            tree->insert(thisKey, thisData);

        }
        else if(dataType == AVLTreeBase::CHARACTER && keyType == AVLTreeBase::FLOAT)
        {

            AVLTree<char, float>* tree = static_cast<AVLTree<char, float>*>(base);

            float thisKey = ::atof(key.c_str());

            char thisData = data.c_str()[0];

            tree->insert(thisKey, thisData);

        }
        else if(dataType == AVLTreeBase::STRING && keyType == AVLTreeBase::INTEGER)
        {

            AVLTree<string, int>* tree = static_cast<AVLTree<string, int>*>(base);

            int thisKey = ::atoi(key.c_str());

            tree->insert(thisKey, data);

        }
        else if(dataType == AVLTreeBase::STRING && keyType == AVLTreeBase::FLOAT)
        {

            AVLTree<string, float>* tree = static_cast<AVLTree<string, float>*>(base);

            float thisKey = ::atof(key.c_str());

            tree->insert(thisKey, data);

        }
        else
        {

            cerr << "Invalid tree type." << endl;

        }
    }
}

AVLTreeBase::PrintOrder AVLForest::switchPrintOrder(int po) {
    switch(po) {
        case 0:
            return AVLTreeBase::IN;
        case 1:
            return AVLTreeBase::PRE;
        case 2:
            return AVLTreeBase::POST;
        case 3:
            return AVLTreeBase::LEVEL;
    }
}

AVLTreeBase::DataType AVLForest::switchDataType(int dt) {
    switch(dt) {
        case 0:
            return AVLTreeBase::CHARACTER;
        case 1:
            return AVLTreeBase::STRING;
    }
}

AVLTreeBase::NumberType AVLForest::switchNumType(int nt) {
    switch(nt) {
        case 0:
            return AVLTreeBase::INTEGER;
        case 1:
            return AVLTreeBase::FLOAT;
    }
}

std::ostream& operator << (std::ostream& out, AVLForest& avlForest)
{
    // print all trees
    for(int id = 0; id < avlForest.forest.size(); id++)
    {

        int metaData = avlForest.m_idToMetaDataMap.find(id);

        AVLTreeBase* base = avlForest.forest[metaData[0]];
        int dataType = metaData[1];
        int keyType = metaData[2];


        // Check to see what kind of tree we're printing
        if(dataType == AVLTreeBase::CHARACTER && keyType == AVLTreeBase::INTEGER)
        {

            AVLTree<char, int>* tree = static_cast<AVLTree<char, int>*>(base);

            tree->print(out);

        }
        else if(dataType == AVLTreeBase::CHARACTER && keyType == AVLTreeBase::FLOAT)
        {

            AVLTree<char, float>* tree = static_cast<AVLTree<char, float>*>(base);

            tree->print(out);

        }
        else if(dataType == AVLTreeBase::STRING && keyType == AVLTreeBase::INTEGER)
        {

            AVLTree<string, int>* tree = static_cast<AVLTree<string, int>*>(base);

            tree->print(out);

        }
        else if(dataType == AVLTreeBase::STRING && keyType == AVLTreeBase::FLOAT)
        {

            AVLTree<string, float>* tree = static_cast<AVLTree<string, float>*>(base);

            tree->print(out);

        }
        else
        {

            cerr << "Error while printing." << endl;

        }

        return out;
    }
}
