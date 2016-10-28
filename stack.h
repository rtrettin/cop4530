#ifndef COP4530_STACK_H
#define COP4530_STACK_H

#include <iostream>
#include <vector>

namespace cop4530 {
  template <typename T>
  class Stack;

  template <typename T>
  class Stack {
    public:
      Stack();
      Stack(const Stack<T> &);
      Stack(Stack<T> &&);
      ~Stack();
      Stack<T> & operator=(const Stack<T> &);
      Stack<T> & operator=(Stack<T> &&);
      bool empty() const;
      void clear();
      void push(const T& x);
      void push(T && x);
      void pop();
      T& top();
      const T& top() const;
      int size() const;
      void print(std::ostream& os, char ofc = ' ') const;
      typename std::vector<T>::iterator begin();
      typename std::vector<T>::const_iterator begin() const;
      typename std::vector<T>::iterator end();
      typename std::vector<T>::const_iterator end() const;
    protected:
      std::vector<T> mystack;
  };
  template <typename T>
  std::ostream& operator<<(std::ostream& os, const Stack<T>& a);
  template <typename T>
  bool operator==(const Stack<T>&, const Stack <T>&);
  template <typename T>
  bool operator!=(const Stack<T>&, const Stack <T>&);
  template <typename T>
  bool operator<=(const Stack<T>& a, const Stack <T>& b);
  #include "stack.hpp"
}
#endif
