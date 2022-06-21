#ifndef __MAXHEAP_H_
#define __MAXHEAP_H_

  #include <vector>
  #include <iostream>
  #include <stdexcept>

  template<class T>
  class MaxHeap {
    private:
      // contiene los elementos del heap
      std::vector<T> data; 
      // capacidad maxima del heap
      int maxSize;
      // tamaño actual del heap   
      int size;   
      int parent(int i);
      int left(int i);
      int right(int i);
      void heapifyDown(int i);
      
    public:
      MaxHeap();
      MaxHeap(int capacity);
      ~MaxHeap();
      bool isEmpty();
      int getCapacity();
      void printMaxHeap();
      void push(T key);
      T top();
      void pop();
      int getSize();
      void setCapacity(int capacity);

  };

  template <class T> 
  MaxHeap<T>::MaxHeap() {
      size = 0;
      maxSize = 0;
  }

  template <class T> 
  MaxHeap<T>::MaxHeap(int capacity) {
      //std::cout << "--->Creando un MaxHeap: " <<  this << std::endl;
      size = 0;
      maxSize = capacity;
      data.resize(maxSize);
  }

  template <class T> 
  MaxHeap<T>::~MaxHeap() {
      //std::cout << "--->Liberando memoria del MaxHeap: " <<  this << std::endl;
      data.clear();
  }
  
  template <class T> 
  bool MaxHeap<T>::isEmpty() {
    return (size <= 0);
  }

  template <class T> 
  int MaxHeap<T>::getCapacity() {
    return maxSize;
  }

  template <class T> 
  void MaxHeap<T>::setCapacity(int capacity) {
    size = 0;
    maxSize = capacity;
    data.resize(maxSize);
  }

  template <class T> 
  void MaxHeap<T>::printMaxHeap() {
    for (int i=0; i < size; i++)
      std::cout << data[i] << " ";
    std::cout << std::endl;
  }

  template <class T> 
  int MaxHeap<T>::parent(int i) {
    return (i-1)/2; 
  }
  
  template <class T> 
  int MaxHeap<T>::left(int i) {
    return (2*i + 1); 
  }

  template <class T> 
  int MaxHeap<T>::right(int i) {
    return (2*i + 2);
  }

  template <class T> 
  void MaxHeap<T>::push(T key) {
    if (size == maxSize) {
      throw std::out_of_range("Overflow: no se puede insertar la llave");
    }
    // Insertamos la nueva llave al final del vector
    int i = size;
    data[i] = key;
    size++;
    // Reparar las propiedades del max heap si son violadas
    while (i != 0 && data[parent(i)] < data[i]) {
       std::swap(data[i], data[parent(i)]);
       i = parent(i);
    }
  }

  template <class T> 
  T MaxHeap<T>::top() {
    if (isEmpty()) {
      throw std::out_of_range("El heap no contine datos");
    }
    else {
      return data[0];   
    }
  }

  // Recursive heapify-down algorithm.
  // The node at index `i` and its two direct children
  // violates the heap property
  template <class T> 
  void MaxHeap<T>::heapifyDown(int i) {
      // get left and right child of node at index `i`
      int _left = left(i);
      int _right = right(i);
      int largest = i;
      // compare `A[i]` with its left and right child
      // and find the largest value
      if (_left < getSize() && data[_left] > data[i]) {
          largest = _left;
      }
      if (_right < getSize() && data[_right] > data[largest]) {
          largest = _right;
      }
      // swap with a child having greater value and
      // call heapify-down on the child
      if (largest != i) {
          std::swap(data[i], data[largest]);
          heapifyDown(largest);
      }
  }

  template <class T> 
  void MaxHeap<T>::pop() {
    if (isEmpty()) {
      throw std::out_of_range("El heap no contiene datos");
    }
    else {
      // replace the root of the heap with the last element
      // of the vector
      data[0] = data.back();  // escribe el último elemento en la primer casilla
      data.pop_back();   // borra la ultima casilla
      // call heapify-down on the root node
      heapifyDown(0);
    }
  }

  template <class T> 
  int MaxHeap<T>::getSize() {
      return size;
  }

#endif // __MAXHEAP_H_