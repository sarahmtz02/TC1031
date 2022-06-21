#ifndef __HASH_TABLE_H_
#define __HASH_TABLE_H_

#include <iostream>
#include <vector>
#include <stdexcept>
#include "HashNode.h"

template<class K, class T>
class HashTable {
  private:
    std::vector<HashNode<K,T>> table;
    int size;
    int maxSize; // preferible un numero primo
    int collisions;

  public:
    HashTable();
    HashTable(int selectedMaxSize);
    ~HashTable();
    int getHashIndex(K keyVal);
    int getSize();
    int getMaxSize();
    int getCollisions();
    void print();
    void add(K keyVal, T value);
    T find(K keyVal);
    T getDataAt(int index);
    void remove(K keyVal);
    void setCapacity(int selectedMaxSize);


};

template<class K, class T>
HashTable<K, T>::HashTable() {
  maxSize = 0;
  size = 0;
  collisions = 0;
  table = std::vector<HashNode<K,T>>(maxSize);
}

template<class K, class T>
HashTable<K, T>::HashTable(int selectedMaxSize) {
  maxSize = selectedMaxSize;
  size = 0;
  collisions = 0;
  table = std::vector<HashNode<K,T>>(maxSize);
}

template<class K, class T>
HashTable<K, T>::~HashTable() {
  maxSize = 0;
  size = 0;
  collisions = 0;
  table.clear();
}

template<class K, class T>
void HashTable<K, T>::setCapacity(int selectedMaxSize) {
  maxSize = selectedMaxSize;
  size = 0;
  collisions = 0;
  table = std::vector<HashNode<K,T>>(maxSize);
}

template<class K, class T>
int HashTable<K, T>::getHashIndex(K keyVal) {
  return keyVal % maxSize;
}

template<class K, class T>
int HashTable<K, T>::getSize() {
  return size;
}

template<class K, class T>
int HashTable<K, T>::getMaxSize() {
  return maxSize;
}

template<class K, class T>
int HashTable<K, T>::getCollisions() {
  return collisions;
}

template<class K, class T>
void HashTable<K,T>::print() {
  std::cout << "Content of the hash table: " << std::endl;
  for (int i = 0; i < maxSize; i++) {
    // status:  0 empty, 1 used, 2 deleted
    if (table[i].getStatus() == 1) // Cell is used
      std::cout << "Cell: " << i << " Key: " << table[i].getKey() << ", Value: " << table[i].getData() << ", Overflow.size: " << table[i].getOverflowSize() << std::endl;
  }
}

template<class K, class T>
void HashTable<K,T>::add(K keyVal, T value) {
  if (size == maxSize) {
    throw std::out_of_range("Hash Table is full");
  }
  // Compute the index of the table hash using a key and a hash function
  int hashVal = getHashIndex(keyVal); 
  HashNode<K, T> node = table[hashVal];
  // status:  0 empty, 1 used, 2 deleted
  if (node.getStatus() != 1) { // Cell is free
    node.setKey(keyVal);
    node.setData(value);
    table[hashVal] = node;
  }
  else { // Cell is already taken
    // Find next free space using quadratic probing
    // https://www.geeksforgeeks.org/quadratic-probing-in-hashing/
    int i = 1;
    int currentHashVal = getHashIndex(hashVal + i * i);
    HashNode<K, T> currentNode = table[currentHashVal];
    while (currentNode.getStatus() == 1) { // Cell is used
      i++;
      currentHashVal = getHashIndex(hashVal + i * i);
      currentNode = table[currentHashVal];
      collisions++;
    }
    // A free cell was found
    currentNode.setKey(keyVal);
    currentNode.setData(value);
    node.addToOverflow(currentHashVal);
    table[currentHashVal] = currentNode;
    table[hashVal] = node;
  }
  size++;
}  

template<class K, class T>
T HashTable<K,T>::find(K keyVal) {
  int hashVal = getHashIndex(keyVal); 
  HashNode<K, T> node = table[hashVal];
  T resNotFound = {};
  // status:  0 empty, 1 used, 2 deleted
  if (node.getStatus() == 1) { // Cell is used
    if (node.getKey() == keyVal) {
      //return hashVal;
      return node.getData();
    }
    for (int i = 0; i < node.getOverflowSize(); i++) {
      int overflowIndex = node.getOverflowAt(i);
      if (table[overflowIndex].getKey() == keyVal) {
        //return overflowIndex;
        return table[overflowIndex].getData();
      }
    }
    return resNotFound;
  }
  return resNotFound;
}

template<class K, class T>
T HashTable<K,T>::getDataAt(int index) {
  return table[index].getData();
}

template<class K, class T>
void HashTable<K,T>::remove(K keyVal) {
  int pos, hashVal;
  pos = find(keyVal);
  if (pos == -1) {
    throw std::invalid_argument("Element does not exist in hash table");
  }
  hashVal = getHashIndex(keyVal);
  if (pos != hashVal) {
    HashNode<K, T> node = table[hashVal];
    node.removeFromOverflow(pos);
    table[hashVal] = node;
  }
  table[pos].clearData(); 
}


#endif // __HASH_TABLE_H_

