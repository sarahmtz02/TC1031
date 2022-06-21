#ifndef _LLNODE_H_
#define _LLNODE_H_

  template <class T>
  class LLNode { 
  public: 
      T data; 
      LLNode<T> *next;
      LLNode();
      LLNode(T val);        
  }; 

  template<class T>
  LLNode<T>::LLNode() : data{}, next{nullptr} {}
  
  template<class T>
  LLNode<T>::LLNode(T val){
      data = val;
      next = nullptr;
  }

#endif // _NODE_H_