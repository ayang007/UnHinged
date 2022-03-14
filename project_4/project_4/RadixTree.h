//
//  RadixTree.h
//  project_4
//
//  Created by Angela Yang on 3/6/22.
//

#ifndef RadixTree_h
#define RadixTree_h
#include <unordered_map>
#include <string>
#include <iostream>
using namespace std;

template <typename ValueType>
class RadixTree {
public:
    RadixTree() {
        m_rootptr = nullptr;
    }
    
    ~RadixTree() {
        
    }
    
    inline
    void insert(std::string key, const ValueType& value) {
        
        
        if (unorderedMap.find(key) == unorderedMap.end()) {
            ValueType* a = new ValueType(value);
            unorderedMap.insert(std::make_pair(key, a));
        }
        else { //key is found
            ValueType* a = new ValueType(value);
            unorderedMap.find(key)->second = a;
        }
    }
    
    inline
    ValueType* search(std::string key) const {
        
        if (unorderedMap.find(key) == unorderedMap.end()) {
            return nullptr;
        }
        else {
            ValueType* a = (unorderedMap.find(key)->second);
            return a;
        }
    }
private:
    struct RadixTreeNode {
        //TODO:
        RadixTreeNode(std::string key, ValueType& value) : word(key), m_value(value) { }
        
        std::string word;
        ValueType m_value;
        bool endOfWord;
        
        RadixTreeNode* edges[26];
    };
    RadixTreeNode* m_rootptr;
    unordered_map<std::string, ValueType*> unorderedMap;
};
#endif /* RadixTree_h */
