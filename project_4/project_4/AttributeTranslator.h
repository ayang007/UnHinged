//
//  AttributeTranslator.h
//  project_4
//
//  Created by Angela Yang on 3/6/22.
//

#ifndef AttributeTranslator_h
#define AttributeTranslator_h
#include "provided.h"
#include "RadixTree.h"

class AttributeTranslator {
public:
    AttributeTranslator();
    
    ~AttributeTranslator();
    
    bool Load(std::string filename);
    
    std::vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;
private:
    RadixTree<vector<AttValPair>> m_compatibleRadixTree;
};

#endif /* AttributeTranslator_h */
