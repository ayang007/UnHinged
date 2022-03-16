//
//  AttributeTranslator.cpp
//  project_4
//
//  Created by Angela Yang on 3/6/22.
//

#include <stdio.h>
#include "AttributeTranslator.h"
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

AttributeTranslator::AttributeTranslator() { }

AttributeTranslator::~AttributeTranslator() { }

bool AttributeTranslator::Load(std::string filename) {
    ifstream infile(filename);
    std::string item;
    std::string att;
    std::string val;
    AttValPair* compatibleItem;
    int commaCount;

    // If the file cannot be found, returns false
    if (!infile)
        return false;
    
    // Loads in all lines of the document,
    std::string instring;
    while (getline(infile, instring))
    {
        commaCount = 0;
        item = "";
        att = "";
        val = "";
        for (int i = 0; i < instring.size(); i++) {
            if (instring[i] == ',') {
                commaCount++;
                continue;
            }
            else if (commaCount < 2) {
                item += instring[i];
            }
            else if (commaCount == 2) {
                att += instring[i];
            }
            else if (commaCount == 3) {
                val += instring[i];
            }
        }
        
        compatibleItem = new AttValPair(att, val);
        
        
        vector<AttValPair>* compatibleItems;
        if (m_compatibleRadixTree.search(item) == nullptr) {
            compatibleItems = new vector<AttValPair>;
            compatibleItems->push_back(*compatibleItem);
        }
        else {
            compatibleItems = m_compatibleRadixTree.search(item);
            compatibleItems->push_back(*compatibleItem);
        }
        m_compatibleRadixTree.insert(item, *compatibleItems);
    }

    // File loaded, return true
    return true;
}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const {
    std::string key = source.attribute + source.value;
    std::vector<AttValPair>* a;
    std::vector<AttValPair> empty;
    a = &empty;
    if (m_compatibleRadixTree.search(key) != nullptr) {
        a = m_compatibleRadixTree.search(key);
    }
    return *a;
}
