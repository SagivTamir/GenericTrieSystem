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
class System {
    GenericTrie<Data> *trie;
public:
    /**
     * start the System
     * @param ABC_size - for example: phoneNumbers: 0-9 (ABC_SIZE = 10)
     */
    explicit System(int ABC_size) : trie(new GenericTrie<Data>(ABC_size)) {}

    ~System();

    /**
     * insert a new element to the system.
     * the element must have the following methods:
     *  - operator[]
     *  - getLength() const
     *  - char convertToElementType(int index) const
     *  when the last one input is index in it's ABC. the function returns char that represents the ABC letter/digit.
     * @param new_data - the new element.
     * @return true if succeeded, otherwise false
     */
    bool insert(Data &new_data);

    /**
     * removes element from the system
     * if the system does not contain the required element - nothing happened.
     * @param to_remove - the element that required to remove from the system.
     */
    void remove(Data &to_remove);

    /**
     * counts the number of elements in the system which the element is prefix of them.
     * @param element - the prefix element
     * @return number of different elements which the element is prefix of them.
     */
    int numOfPrefixes(Data &element);

    /**
     * prints the current elements in the system.
     */
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
    std::cout << std::endl;
}


template<class Data>
int System<Data>::numOfPrefixes(Data &element) {
    return trie->numOfPrefixes(element);
}


template<class Data>
void System<Data>::remove(Data &to_remove) {
    trie->remove(to_remove);
}

#endif //GENERICSYSTEMHANDLER_SYSTEM_H
