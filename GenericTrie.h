//
// Created by tamir on 15/03/2022.
//

#ifndef GENERICSYSTEMHANDLER_GENERICTRIE_H
#define GENERICSYSTEMHANDLER_GENERICTRIE_H

#include "TrieNode.h"
#include <vector>
#include <algorithm>
#include <iostream>

template<class Data>
class GenericTrie {
    TrieNode<Data>* root;
    int num_of_elements;
    int ABC_size;
    bool is_first_insert;
    bool insertDigitByDigit(Data& new_data, int index,TrieNode<Data>* current_node);
    void clearTree(TrieNode<Data>* current_node);
    // the first element is saved only for his methods.
    Data* first_element;
public:
    explicit GenericTrie(int ABC_size);
    ~GenericTrie();
    bool insert(Data& new_data);
    std::vector<std::vector<int>> printTreeRec(TrieNode<Data>* current_node,std::vector<std::vector<int>>& print_vec, int& finished_words_pass) const;
    void printTree() const;
};

template<class Data>
GenericTrie<Data>::GenericTrie(int ABC_size) :
    root(new TrieNode<Data>(0,ABC_size)),
    num_of_elements(0),
    ABC_size(ABC_size),
    is_first_insert(true),
    first_element(nullptr) {}


template<class Data>
bool GenericTrie<Data>::insert(Data &new_data) {
    if (is_first_insert){
        root->next_nodes = std::vector<TrieNode<Data>*>(ABC_size, nullptr);
        first_element = &new_data;
        is_first_insert = false;
    }
    insertDigitByDigit(new_data,0,root);
    num_of_elements++;

    return true;
}

template<class Data>
bool GenericTrie<Data>::insertDigitByDigit(Data& new_data, int index, TrieNode<Data>* current_node) {
    if (index > (new_data.getLength() - 1)){
        current_node->setEndOfWord();
        return true;
    }
    auto itr = std::find(new_data.my_ABC.begin(), new_data.my_ABC.end(), new_data[index]);
    int index_of_curr_dig_in_ABC = std::distance(new_data.my_ABC.begin(), itr);

    if ((current_node->next_nodes[index_of_curr_dig_in_ABC]) == nullptr){
        (current_node->next_nodes[index_of_curr_dig_in_ABC]) = new TrieNode<Data>(index_of_curr_dig_in_ABC,ABC_size);
        current_node->next_nodes[index_of_curr_dig_in_ABC]->setValue(index_of_curr_dig_in_ABC);
        // continue with the next digit
        insertDigitByDigit(new_data,++index,current_node->next_nodes[index_of_curr_dig_in_ABC]);
    }
    else {
        current_node->next_nodes[index_of_curr_dig_in_ABC]->increaseNumOfLeaves();
        insertDigitByDigit(new_data,++index,current_node->next_nodes[index_of_curr_dig_in_ABC]);
    }
    return false;
}

template<class Data>
GenericTrie<Data>::~GenericTrie() {
    clearTree(root);
}

template<class Data>
void GenericTrie<Data>::clearTree(TrieNode<Data>* current_node) {
    for (int i = 0; i < ABC_size; i++){
        if (current_node->next_nodes[i] != nullptr){
            clearTree(current_node->next_nodes[i]);
        }
    }
    delete current_node;
}

template<class Data>
std::vector<std::vector<int>> GenericTrie<Data>::printTreeRec(TrieNode<Data>* current_node,std::vector<std::vector<int>>& print_vec, int& finished_words_pass) const {
    for (int i = 0; i < ABC_size; i++) {
        if (current_node->next_nodes[i] != nullptr) {
            for (int j = 0; j < current_node->next_nodes[i]->getNumberOfLeaves(); j++) {
                print_vec[finished_words_pass + j].push_back(current_node->next_nodes[i]->getValue());
            }
            if (current_node->next_nodes[i]->isEndOfWord()){
                finished_words_pass++;
            }
            printTreeRec(current_node->next_nodes[i],print_vec,finished_words_pass);
        }
    }
    return print_vec;
}

template<class Data>
void GenericTrie<Data>::printTree() const {
    std::vector<std::vector<int>> print_vec(num_of_elements, std::vector<int>());
    int finished_word_pass = 0;
    printTreeRec(root,print_vec,finished_word_pass);
    for (auto & i : print_vec){
        for (int j : i){
            std::cout << first_element->convertToElementType(j);
        }
        std::cout << std::endl;
    }
}


#endif //GENERICSYSTEMHANDLER_GENERICTRIE_H
