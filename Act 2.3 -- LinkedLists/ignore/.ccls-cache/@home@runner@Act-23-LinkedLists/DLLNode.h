#ifndef _DLLNODE_H_
#define _DLLNODE_H_

  template <class T>
  class DLLNode { 
  public: 
      T data; 
      DLLNode<T>* next;
      DLLNode<T>* prev;
      DLLNode();
      DLLNode(T val);        
  }; 

  template<class T>
  DLLNode<T>::DLLNode() : data{}, next{nullptr}, prev{nullptr} {}
  
  template<class T>
  DLLNode<T>::DLLNode(T val){
      data = val;
      next = nullptr;
      prev = nullptr;
  }

#endif // _DLLNODE_H_