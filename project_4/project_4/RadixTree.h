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
    
    ~RadixTree() { }
    void insert(std::string key, const ValueType& value);
    ValueType* search(std::string key) const;
    
private:
    struct RadixTreeNode {
        //TODO:
        RadixTreeNode(std::string key, const ValueType& value) : word(key), m_value(value) { }
        
        std::string word;
        vector<RadixTreeNode*> children;
        ValueType m_value;
        bool endOfWord;
    };
    RadixTreeNode* m_rootptr;
    unordered_map<std::string, ValueType*> unorderedMap;
    void insertRecursive(std::string currWord, const ValueType& value, RadixTreeNode* rootnode);
    ValueType* searchRecursive(std::string key, RadixTreeNode* rootnode) const;
};

template <typename ValueType>
void RadixTree<ValueType>::insert(std::string key, const ValueType& value) {
    
    insertRecursive(key, value, m_rootptr);
    
    //NON-RECURSIVE IMPLEMENTATION
    /*
    RadixTreeNode* newNode;
    //if empty
    if (m_rootptr == nullptr) {
        newNode = new RadixTreeNode(key, value);
        m_rootptr = newNode;
        return;
    }
    //check children for prefix of word
    RadixTreeNode* currNode = m_rootptr;
    string currWord = key;
    while (currNode != nullptr) {
        string matchingChildWord = "";
        for (int i = 0; i < currNode->children.size(); i++) {
            //check each child node's word to see if any match our word
            string childWord = currNode->children[i]->word;
            if (key[0] = childWord[0]) {
                //found our word
                matchingChildWord = childWord;
                currNode = currNode->children[i];
                break;
            }
            else {
                //keep looking
                continue;
            }
        }
        //if no prefix, add new child with the full word
        if (matchingChildWord == "") {
            newNode = new RadixTreeNode(currWord, value);
            currNode->children.push_back(newNode);
        }
        //if prefix:
        int i;
        for (i = 0; i < matchingChildWord.size(); i++) {
            if (currWord[i] != matchingChildWord[i]) {
                //TODO: break the word if it shares a prefix with matchingchildword, and add a new node of the shared prefix.
                break;
            }
        }
        //this means that the word contains the entire prefix
        if (i == matchingChildWord.size()) {
            currNode =
        }
                    
    }
     */
    
    //UNORDERED MAP IMPLEMENTATION
//        if (unorderedMap.find(key) == unorderedMap.end()) {
//            ValueType* a = new ValueType(value);
//            unorderedMap.insert(std::make_pair(key, a));
//        }
//        else { //key is found
//            ValueType* a = new ValueType(value);
//            unorderedMap.find(key)->second = a;
//        }
}

template<typename ValueType>
ValueType* RadixTree<ValueType>::search(std::string key) const {
    //if empty tree, return not found
    if (!m_rootptr) {
        ValueType* a = nullptr;
        return a;
    }
    //search recursive assumes a non empty tree
    return searchRecursive(key, m_rootptr);
    
    //UNORDERED MAP IMPLEMENTATION
//        if (unorderedMap.find(key) == unorderedMap.end()) {
//            return nullptr;
//        }
//        else {
//            ValueType* a = (unorderedMap.find(key)->second);
//            return a;
//        }
}

template <typename ValueType>
void RadixTree<ValueType>::insertRecursive(std::string currWord, const ValueType& value, RadixTreeNode* rootnode) {
    //base case
    if (rootnode == nullptr) {
        RadixTreeNode* newNode = new RadixTreeNode(currWord, value);
        rootnode = newNode;
        return;
    }
    //recursion
    else {
        //check the prefix of rootnode's children
        //variables:
        string newWord = "";
        RadixTreeNode* newRootNode = nullptr;
        //if so, insert rootnode, that child
        int i;
        for (i = 0; i < rootnode->children.size(); i++) {
            RadixTreeNode* selectedChild = nullptr;
            if (currWord[0] == rootnode->children[i]->word[0]) {
                //determining the new currword
                selectedChild = rootnode->children[i];
                int j;
                for (j = 0; j < selectedChild->word.size(); j++) {
                    if (currWord[j] != selectedChild->word[j]) {
                        break;
                    }
                }
                
                //in the case the word is already in the tree:
                if (j == currWord.size()-1) {
                    //if it's not there as an end-of-word
                    if (!selectedChild->endOfWord) {
                        selectedChild->endOfWord = true;
                    }
                    //update the value regardless:
                    selectedChild->m_value = value;
                }
                
                //determine the new word
                for (int k = j; k < currWord.size(); k++) {
                    newWord += currWord[k];
                }
                
                //if prefix needs to be split
                if (j != selectedChild->word.size()) {
                    //splitting into the new prefixes:
                    string newSharedPrefix = "";
                    string newNextPrefix = "";
                    for (int k = 0; k < j; k++) {
                        newSharedPrefix += currWord[k];
                    }
                    for (int k = j; k < selectedChild->word.size(); k++) {
                        newNextPrefix += selectedChild->word[k];
                    }
                    //create the new parent node, and fix the children.
                    ValueType a = selectedChild->m_value;
                    RadixTreeNode* newPrefixNode = new RadixTreeNode(newSharedPrefix, a);
                    newPrefixNode->endOfWord = false;
                    rootnode->children[i] = newPrefixNode;
                    newPrefixNode->children.push_back(selectedChild);
                    selectedChild->word = newNextPrefix;
                    newPrefixNode->children.push_back(newRootNode);
                    insertRecursive(currWord, value, newRootNode);
                }
                
                //if prefix doesn't need to be split
                else {
                    newRootNode = rootnode->children[i];
                    insertRecursive(currWord, value, newRootNode); //recurse
                    break;
                }
            }
        }
        //if all children were checked and they don't hold a shared prefix,
        if (i == rootnode->children.size()) {
            rootnode->children.push_back(newRootNode);
            insertRecursive(currWord, value, newRootNode); //recurse
        }
    }
}

template <typename ValueType>
ValueType* RadixTree<ValueType>::searchRecursive(std::string key, RadixTreeNode* rootnode) const {
    //base case
    if (rootnode->word == key) {
        //found it!
        return &rootnode->m_value;
    }
    else {
        //check children of rootnode
        for (int i = 0; i < rootnode->children.size(); i++) {
            //find a prefix if there is one
            if (rootnode->children[i]->word[0] == key[0]) {
                for (int j = 0; j < rootnode->children[i]->word.size(); j++) {
                    if (rootnode->children[i]->word[j] != key[j]) {
                        //prefix not found, so return not found.
                        ValueType* a = nullptr;
                        return a;
                    }
                }
                //this means we found the prefix, so we call search on the new word
                string newWord = "";
                for (int j = rootnode->children[i]->word.size(); j < key.size(); j++) {
                    newWord += key[j];
                }
                cout << newWord;
                searchRecursive(newWord, rootnode->children[i]);
            }
        }
        //prefix not found, so return not found.
        ValueType* a = nullptr;
        return a;
    }
}
#endif /* RadixTree_h */
