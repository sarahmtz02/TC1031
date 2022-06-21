#ifndef _DLINKEDLIST_H_
#define _DLINKEDLIST_H_

#include "DLLNode.h"
#include <iostream>
#include <stdexcept>

template <class T> class DLinkedList {
private:
  DLLNode<T> *head;
  DLLNode<T> *tail;
  int numElements;

  DLLNode<T> *partition(DLLNode<T> *low, DLLNode<T> *high);
  void quickSort(DLLNode<T>* low, DLLNode<T> *high);
  DLLNode<T>* middle(DLLNode<T>* start, DLLNode<T>* last);

public:
  DLinkedList();
  ~DLinkedList();
  int getNumElements();
  void printList();
  void printLastNode();
  void addFirst(T value);
  void addLast(T value);
  bool deleteData(T value);
  bool deleteAt(int position);
  T getData(int position);
  DLLNode<T> *getHead();  
  void callQuickSort();
  DLLNode<T> *binarySearch(T value);
};

template <class T> DLinkedList<T>::DLinkedList() {
  std::cout << "--->Creando una lista vacia" << std::endl;
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}

template <class T> DLinkedList<T>::~DLinkedList() {
  std::cout << "--->Liberando memoria de la lista ligada" << std::endl;
  DLLNode<T> *p, *q;
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

template <class T> int DLinkedList<T>::getNumElements() { return numElements; }

template <class T> void DLinkedList<T>::printList() {
  DLLNode<T> *ptr = head;
  while (ptr != nullptr) {
    std::cout << ptr->data << " ";
    ptr = ptr->next;
  }
  std::cout << std::endl;
}

template <class T> void DLinkedList<T>::printLastNode() {
  std::cout << tail->data << std::endl;
}

template <class T> void DLinkedList<T>::addFirst(T value) {
  DLLNode<T> *newDLLNode = new DLLNode<T>(value);
  // Si la lista está vacia
  if (head == nullptr && tail == nullptr) {
    head = newDLLNode;
    tail = newDLLNode;
  } else {
    newDLLNode->next = head;
    head->prev = newDLLNode;
    head = newDLLNode;
  }
  numElements++;
}

template <class T> void DLinkedList<T>::addLast(T value) {
  if (head == nullptr && tail == nullptr) {
    addFirst(value);
  } else {
    DLLNode<T> *newDLLNode = new DLLNode<T>(value);
    tail->next = newDLLNode;
    newDLLNode->prev = tail;
    tail = newDLLNode;
    numElements++;
  }
}

template <class T> bool DLinkedList<T>::deleteData(T value) {
  // Si la lista esta vacia
  if (head == nullptr && tail == nullptr) {
    return false;
  } else {
    DLLNode<T> *p, *q;
    p = head;
    q = nullptr;
    // buscar value en la lista
    while (p != nullptr && p->data != value) {
      q = p;
      p = p->next;
    }
    // Si no existe value en la lista
    if (p == nullptr)
      return false;
    // Si debe borrarse el primer elemento
    if (p->prev == nullptr) {
      head = p->next;
      if (head != nullptr)
        head->prev = nullptr;
    } else if (p->next == nullptr) {
      // Si debe borrarse el último elemento
      q->next = nullptr;
      tail = q;
    } else {
      // Cualquier otro elemento entre la lista
      q->next = p->next;
      p->next->prev = q;
    }
    delete p;
    numElements--;
    return true;
  }
}

template <class T> bool DLinkedList<T>::deleteAt(int position) {
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  } else if (position == 0) { // Si debe borrarse el primer elemento
    DLLNode<T> *p = head;
    // Si la lista contiene solo un nodo
    if (head != nullptr && head->next == nullptr) {
      head = tail = nullptr;
    } else {
      head = p->next;
      head->prev = nullptr;
    }
    delete p;
    numElements--;
    return true;
  } else { // Si la lista contiene mas de un nodo
    DLLNode<T> *p = head, *q = nullptr;
    int index = 0;
    // Se busca el indice del elemento a borrar
    while (index != position) {
      q = p;
      p = p->next;
      index++;
    }
    // Si debe borrarse el último elemento
    if (p->next == nullptr) {
      q->next = nullptr;
      tail = q;
    } else { // Cualquier otro elemento en medio de la lista
      q->next = p->next;
      p->next->prev = q;
    }
    delete p;
    numElements--;
    return true;
  }
}

template <class T> T DLinkedList<T>::getData(int position) {
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  } else {
    if (position == 0)
      return head->data;
    DLLNode<T> *p = head;
    int index = 0;
    while (p != nullptr) {
      if (index == position)
        return p->data;
      index++;
      p = p->next;
    }
    return -1;
  }
}

template <class T> DLLNode<T> * DLinkedList<T>::getHead(){
  return head;
}

template <class T> DLLNode<T> * DLinkedList<T>::partition(DLLNode<T> *low, DLLNode<T> *high) {
    // set pivot as h element
    T x = high->data;
 
    // similar to i = l-1 for array implementation
    DLLNode<T> *i = low->prev;
 
    // Similar to "for (int j = l; j <= h- 1; j++)"
    for (DLLNode<T> *j = low; j != high; j = j->next) {
        if (j->data <= x) {
            // Similar to i++ for array
            i = (i == nullptr)? low : i->next; 
            std::swap(i->data, j->data);
        }
    }
    i = (i == nullptr)? low : i->next; // Similar to i++
    std::swap(i->data, high->data);
    return i;
}

template <class T> void DLinkedList<T>::quickSort(DLLNode<T>* low, DLLNode<T> *high) {
    if (high != nullptr && low != high && low != high->next) {
        DLLNode<T> *p = partition(low, high);
        quickSort(low, p->prev);
        quickSort(p->next, high);
    }
}

template <class T> void DLinkedList<T>::callQuickSort() {
  quickSort(head, tail);
}

template <class T> DLLNode<T>* DLinkedList<T>::middle(DLLNode<T>* start, DLLNode<T>* last) {
    if (start == nullptr)
        return nullptr;
    DLLNode<T>* slow = start;
    DLLNode<T>* fast = start->next;
    while (fast != last) {
        fast = fast->next;
        if (fast != last) {
            slow = slow -> next;
            fast = fast -> next;
        }
    }
    return slow;
}

template <class T> DLLNode<T>* DLinkedList<T>::binarySearch(T value) {
    DLLNode<T>* start = head;
    DLLNode<T>* last = nullptr;
 
    do {
        // Find middle
        DLLNode<T>* mid = middle(start, last);
        // If middle is empty
        if (mid == nullptr)
            return nullptr;
 
        // If value is present at middle
        if (mid->data == value)
            return mid;
        // If value is more than mid
        else if (mid->data < value)
            start = mid->next;
        // If the value is less than mid.
        else
            last = mid;
    } while (last == nullptr || last != start);
 
    // value not present
    return nullptr;
}

#endif // _DLINKEDLIST_H_