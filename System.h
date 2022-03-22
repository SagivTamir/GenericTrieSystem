//
// Created by tamir on 15/03/2022.
//

#ifndef GENERICSYSTEMHANDLER_SYSTEM_H
#define GENERICSYSTEMHANDLER_SYSTEM_H

#include <map>
#include <vector>
#include "GenericTrie.h"
#include "TrieNode.h"

template<class Data>
class System{
    GenericTrie<Data>* trie;
public:
    explicit System(int ABC_size) : trie(new GenericTrie<Data>(ABC_size)) {}
    bool insert(Data& new_data);
    ~System();
    void printSystem() const;

};

template<class Data>
bool System<Data>::insert(Data &new_data) {
    return trie->insert(new_data);
}

template<class Data>
System<Data>::~System() {
        delete trie;
}

template<class Data>
void System<Data>::printSystem() const {
    trie->printTree();
}

#endif //GENERICSYSTEMHANDLER_SYSTEM_H
