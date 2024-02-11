# GenericTrySystem
This system is based on "Trie" data structure.
This means it has the ability to search, sort, insert, remove and return the number of prefixes in linear time complexity (by the **length** of the elements) , O(objectMaxLength).
The system is generic,
Therefore the following methods should be override by the entity object class:
- operator[]
- getLength() const
- char convertToElementType(int index) const

There are two examples of using the system in main.cpp.

created by Sagiv Tamir.
25.3.22
