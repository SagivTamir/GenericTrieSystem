//
// Created by tamir on 15/03/2022.
//

#ifndef GENERICSYSTEMHANDLER_TRIENODE_H
#define GENERICSYSTEMHANDLER_TRIENODE_H

#include <vector>

template<class Data>
class TrieNode {
    int num_of_leaves;
    int index_in_ABC;
    bool is_end_of_word;
public:
    std::vector<TrieNode*> next_nodes;
    TrieNode(int index_in_ABC,int ABC_size) : num_of_leaves(1),
    next_nodes(std::vector<TrieNode*>(ABC_size,nullptr)),
    index_in_ABC(index_in_ABC),
    is_end_of_word(false){}
    void setEndOfWord();
    void increaseNumOfLeaves();
    bool isNextNodesAreNull() const;
    void setValue(int value_in_ABC){
        index_in_ABC = value_in_ABC;
    }
    int getNumberOfLeaves() const;
    int getValue() const;
    bool isEndOfWord() const;
};

template<class Data>
void TrieNode<Data>::increaseNumOfLeaves() {
    num_of_leaves++;
}

template<class Data>
bool TrieNode<Data>::isNextNodesAreNull() const {
    int vec_size = next_nodes.size();
    for(int i = 0; i < vec_size; i++){
        if (next_nodes[i] != nullptr){
            return false;
        }
    }
    return true;
}

template<class Data>
void TrieNode<Data>::setEndOfWord() {
    is_end_of_word = true;
}

template<class Data>
int TrieNode<Data>::getNumberOfLeaves() const {
    return num_of_leaves;
}

template<class Data>
int TrieNode<Data>::getValue() const {
    return index_in_ABC;
}

template<class Data>
bool TrieNode<Data>::isEndOfWord() const {
    return is_end_of_word;
}


#endif //GENERICSYSTEMHANDLER_TRIENODE_H
