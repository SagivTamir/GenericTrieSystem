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
    TrieNode<Data> *root;
    int num_of_elements;
    int ABC_size;
    bool is_first_insert;

    bool insertDigitByDigit(Data &new_data, int index, TrieNode<Data> *current_node);

    void clearTree(TrieNode<Data> *current_node);

    // the first element is saved only for its convertToElementType method for printSystem use.
    Data *first_element;
public:
    explicit GenericTrie(int ABC_size);

    ~GenericTrie();

    bool insert(Data &new_data);

    void remove(Data &to_remove);

    void removeRec(Data &to_remove, int current_index, TrieNode<Data> *current_node);

    TrieNode<Data> *find(Data &new_data);

    TrieNode<Data> *findRec(Data &new_data, int current_index, TrieNode<Data> *current_node);

    int numOfPrefixes(Data &new_data);

    bool isContain(Data &data);

    std::vector<std::vector<int>> printTreeRec(TrieNode<Data> *current_node, std::vector<std::vector<int>> &print_vec,
                                               int &finished_words_pass) const;

    void printTree() const;

    void decreaseNumOfElements();
};

template<class Data>
GenericTrie<Data>::GenericTrie(int ABC_size) :
        root(new TrieNode<Data>(0, ABC_size)),
        num_of_elements(0),
        ABC_size(ABC_size),
        is_first_insert(true),
        first_element(nullptr) {}


template<class Data>
bool GenericTrie<Data>::insert(Data &new_data) {
    if (isContain(new_data)) {
        // object already contains
        return false;
    }
    if (is_first_insert) {
        root->next_nodes = std::vector<TrieNode<Data> *>(ABC_size, nullptr);
        first_element = new Data(new_data);
        is_first_insert = false;
    }
    insertDigitByDigit(new_data, 0, root);
    num_of_elements++;
    return true;
}

template<class Data>
bool GenericTrie<Data>::insertDigitByDigit(Data &new_data, int index, TrieNode<Data> *current_node) {
    if (index > (new_data.getLength() - 1)) {
        current_node->increaseEndOfWordCounter();
        return true;
    }
    auto itr = std::find(new_data.my_ABC.begin(), new_data.my_ABC.end(), new_data[index]);
    int index_of_curr_dig_in_ABC = std::distance(new_data.my_ABC.begin(), itr);

    if ((current_node->next_nodes[index_of_curr_dig_in_ABC]) == nullptr) {
        (current_node->next_nodes[index_of_curr_dig_in_ABC]) = new TrieNode<Data>(index_of_curr_dig_in_ABC, ABC_size);
        // continue with the next digit
        insertDigitByDigit(new_data, ++index, current_node->next_nodes[index_of_curr_dig_in_ABC]);
    } else {
        current_node->next_nodes[index_of_curr_dig_in_ABC]->increaseNumberOfLeaves();
        insertDigitByDigit(new_data, ++index, current_node->next_nodes[index_of_curr_dig_in_ABC]);
    }
    return false;
}

template<class Data>
GenericTrie<Data>::~GenericTrie() {
    clearTree(root);
    delete first_element;
}

template<class Data>
void GenericTrie<Data>::clearTree(TrieNode<Data> *current_node) {
    for (int i = 0; i < ABC_size; i++) {
        if (current_node->next_nodes[i] != nullptr) {
            clearTree(current_node->next_nodes[i]);
        }
    }
    delete current_node;
}

template<class Data>
std::vector<std::vector<int>>
GenericTrie<Data>::printTreeRec(TrieNode<Data> *current_node, std::vector<std::vector<int>> &print_vec,
                                int &finished_words_pass) const {
    for (int i = 0; i < ABC_size; i++) {
        if (current_node->next_nodes[i] != nullptr) {
            for (int j = 0; j < current_node->next_nodes[i]->getNumberOfLeaves(); j++) {
                print_vec[finished_words_pass + j].push_back(current_node->next_nodes[i]->getValue());
            }
            if (current_node->next_nodes[i]->isEndOfWord()) {
                finished_words_pass++;
            }
            printTreeRec(current_node->next_nodes[i], print_vec, finished_words_pass);
        }
    }
    return print_vec;
}

template<class Data>
void GenericTrie<Data>::printTree() const {
    std::vector<std::vector<int>> print_vec(num_of_elements, std::vector<int>());
    int finished_word_pass = 0;
    printTreeRec(root, print_vec, finished_word_pass);
    for (auto &i : print_vec) {
        for (int j : i) {
            std::cout << first_element->convertToElementType(j);
        }
        std::cout << std::endl;
    }
}

template<class Data>
TrieNode<Data> *GenericTrie<Data>::find(Data &new_data) {
    return findRec(new_data, 0, root);
}

template<class Data>
TrieNode<Data> *GenericTrie<Data>::findRec(Data &new_data, int current_index, TrieNode<Data> *current_node) {
    if (current_index > (new_data.getLength() - 1)) {
        return current_node;
    }

    auto itr = std::find(new_data.my_ABC.begin(), new_data.my_ABC.end(), new_data[current_index]);
    int index_of_curr_dig_in_ABC = std::distance(new_data.my_ABC.begin(), itr);

    if ((current_node->next_nodes[index_of_curr_dig_in_ABC]) == nullptr) {
        return nullptr;
    } else {
        return findRec(new_data, ++current_index, current_node->next_nodes[index_of_curr_dig_in_ABC]);
    }
}

template<class Data>
int GenericTrie<Data>::numOfPrefixes(Data &new_data) {
    TrieNode<Data> *const res = find(new_data);
    if (res == nullptr) {
        // the word not found
        return 0;
    } else {
        return res->getNumberOfLeaves();
    }
}

template<class Data>
bool GenericTrie<Data>::isContain(Data &data) {
    TrieNode<Data> *res = find(data);
    if (res == nullptr || !res->isEndOfWord()) {
        return false;
    } else {
        return true;
    }
}

template<class Data>
void GenericTrie<Data>::remove(Data &to_remove) {
    if (!isContain(to_remove)) {
        return;
    }
    int length = to_remove.getLength();
    TrieNode<Data> *arr_path[length];
    TrieNode<Data> *current_node = root;
    for (int i = 0; i < length; i++) {
        auto itr = std::find(to_remove.my_ABC.begin(), to_remove.my_ABC.end(), to_remove[i]);
        int index_of_curr_dig_in_ABC = std::distance(to_remove.my_ABC.begin(), itr);
        arr_path[i] = current_node->next_nodes[index_of_curr_dig_in_ABC];
        current_node = current_node->next_nodes[index_of_curr_dig_in_ABC];
    }
    arr_path[length - 1]->decreaseEndOfWordCounter();
    for (int i = length - 1; i >= 0; i--) {
        if ((arr_path[i])->getNumberOfLeaves() == 1) {
            auto itr = std::find(to_remove.my_ABC.begin(), to_remove.my_ABC.end(), to_remove[i]);
            int index_of_curr_dig_in_ABC = std::distance(to_remove.my_ABC.begin(), itr);
            delete arr_path[i];
            if (arr_path[i] == root->next_nodes[index_of_curr_dig_in_ABC]) {
                root->next_nodes[index_of_curr_dig_in_ABC] = nullptr;
            } else {
                arr_path[i - 1]->next_nodes[index_of_curr_dig_in_ABC] = nullptr;
            }

        } else {
            (arr_path[i])->decreaseNumberOfLeaves();
        }
    }
    this->decreaseNumOfElements();
}

template<class Data>
void GenericTrie<Data>::removeRec(Data &to_remove, int current_index, TrieNode<Data> *current_node) {
    if (current_index > (to_remove.getLength() - 1)) {
        return;
    }
    auto itr = std::find(to_remove.my_ABC.begin(), to_remove.my_ABC.end(), to_remove[current_index]);
    int index_of_curr_dig_in_ABC = std::distance(to_remove.my_ABC.begin(), itr);
    removeRec(to_remove, ++current_index, current_node->next_nodes[index_of_curr_dig_in_ABC]);

    if (current_node->getNumberOfLeaves() == 1) {
        delete current_node;
    }
}

template<class Data>
void GenericTrie<Data>::decreaseNumOfElements() {
    num_of_elements--;
}


#endif //GENERICSYSTEMHANDLER_GENERICTRIE_H
