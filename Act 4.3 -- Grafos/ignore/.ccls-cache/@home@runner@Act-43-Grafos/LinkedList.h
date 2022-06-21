#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

  #include<iostream>
  #include <stdexcept>
  #include "LLNode.h"

  template <class T>
  class LinkedList {
      private:
        LLNode<T>* head;
        LLNode<T>* tail;
        int numElements;

      public:
        LinkedList();
        ~LinkedList();
        int getNumElements();
        void printList();
        void printLastNode();
        void addFirst(T value);
        void addLast(T value);
        T getData(int position);

  };

  template<class T>
  LinkedList<T>::LinkedList() {
      //std::cout << "--->Creando una lista vacia" << std::endl;
      head = nullptr;
      tail = nullptr;
      numElements = 0;
  }

  template<class T>
  LinkedList<T>::~LinkedList() {
      //std::cout << "--->Liberando memoria de la lista ligada" << std::endl;
    LLNode<T> *p, *q;
    p = head;
    while (p != nullptr) {
      q = p->next;
      delete p;
      p = q;
    }
    head = nullptr;
    tail = nullptr;
    numElements = 0;
  }

  template<class T>
  int LinkedList<T>::getNumElements() {
    return numElements;
  }

  template<class T>
  void LinkedList<T>::printList() {
    LLNode<T> *ptr = head;
    while (ptr != nullptr) {
        std::cout << ptr->data << " ";
        ptr = ptr->next;
    }
    std::cout << std::endl;
  }

  template<class T>
  void LinkedList<T>::printLastNode() {
    std::cout << tail->data << std::endl;
  }

  template<class T>
  void LinkedList<T>::addFirst(T value) {
    LLNode<T> *newLLNode = new LLNode<T>(value);
    newLLNode->next = head;
    head = newLLNode;
    if (numElements == 0) 
      tail = newLLNode;
    numElements++;    
  }

  template<class T>
  void LinkedList<T>::addLast(T value) {
    if (head == nullptr) {
      addFirst(value);
    }
    else {
      LLNode<T> *newLLNode = new LLNode<T>(value);
      newLLNode->next = nullptr;
      tail->next = newLLNode;
      tail = newLLNode;
      numElements++;
    }
  }

  template<class T>
  T LinkedList<T>::getData(int position) {
    if (position < 0 || position >= numElements) {
      throw std::out_of_range("Indice fuera de rango");
    }
    else {
      T res = {};
      if (position == 0)
        return head->data;
      LLNode<T> *p = head;
      int index = 0;
      while (p != nullptr) {
        if (index == position)
          return p->data;
        index++;
        p = p->next;
      }
      return res;
    }
  }

#endif // _LINKEDLIST_H_