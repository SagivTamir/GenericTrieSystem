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
    int counter_end_of_word;
public:
    std::vector<TrieNode *> next_nodes;

    TrieNode(int index_in_ABC, int ABC_size) : num_of_leaves(1),
                                               next_nodes(std::vector<TrieNode *>(ABC_size, nullptr)),
                                               index_in_ABC(index_in_ABC),
                                               counter_end_of_word(0) {}

    void increaseEndOfWordCounter();

    void decreaseEndOfWordCounter();

    void increaseNumberOfLeaves();

    void decreaseNumberOfLeaves();

    int getNumberOfLeaves() const;

    int getValue() const;

    bool isEndOfWord() const;
};

template<class Data>
void TrieNode<Data>::increaseNumberOfLeaves() {
    num_of_leaves++;
}


template<class Data>
void TrieNode<Data>::increaseEndOfWordCounter() {
    counter_end_of_word++;
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
    return counter_end_of_word >= 1;
}


template<class Data>
void TrieNode<Data>::decreaseEndOfWordCounter() {
    counter_end_of_word--;
}

template<class Data>
void TrieNode<Data>::decreaseNumberOfLeaves() {
    num_of_leaves--;
}


#endif //GENERICSYSTEMHANDLER_TRIENODE_H
