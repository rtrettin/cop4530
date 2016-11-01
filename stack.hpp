/* Remi Trettin COP4530 Project 3 */
#ifndef COP4530_STACK_HPP
#define COP4530_STACK_HPP

// constructor
template <typename T>
Stack<T>::Stack() {
}

// copy constructor
template <typename T>
Stack<T>::Stack(const Stack<T> &x) {
  for(typename std::vector<T>::const_iterator itr = x.begin(); itr != x.end(); ++itr) {
    mystack.push_back(*itr);
  }
}

// move constructor
template <typename T>
Stack<T>::Stack(Stack<T> && x) {
  for(typename std::vector<T>::iterator itr = x.begin(); itr != x.end(); ++itr) {
    mystack.push_back(*itr);
  }
  x.clear();
}

// destructor
template <typename T>
Stack<T>::~Stack() {
}

// copy assignment operator
template <typename T>
Stack<T> & Stack<T>::operator=(const Stack<T> & x) {
  Stack<T> copy = x;
  std::swap(*this, copy);
  return *this;
}

// move assignment operator
template <typename T>
Stack<T> & Stack<T>::operator=(Stack<T> && x) {
  std::swap(mystack, x.mystack);
  return *this;
}

// use vector empty() to determine if the stack is empty
template <typename T>
bool Stack<T>::empty() const {
  return mystack.empty();
}

// use vector clear() to clear the stack
template <typename T>
void Stack<T>::clear() {
  mystack.clear();
}

// use vector push_back() to insert into stack
template <typename T>
void Stack<T>::push(const T& x) {
  mystack.push_back(x);
}

// use vector push_back() to insert into stack
template <typename T>
void Stack<T>::push(T && x) {
  mystack.push_back(x);
}

// use vector pop_back() to remove from stack
template <typename T>
void Stack<T>::pop() {
  mystack.pop_back();
}

// use vector back() to return the top of the stack
template <typename T>
T& Stack<T>::top() {
  return mystack.back();
}

// use vector back() to return the top of the stack
template <typename T>
const T& Stack<T>::top() const {
  return mystack.back();
}

// use vector size() to return the size of the stack
template <typename T>
int Stack<T>::size() const {
  return mystack.size();
}

// use vector iterator to loop through the stack and print it out
template <typename T>
void Stack<T>::print(std::ostream& os, char ofc) const {
  auto itr = mystack.begin();
  os << *itr++;
  for(; itr != mystack.end(); ++itr) {
    os << ofc << *itr;
  }
  os << std::endl;
}

// use vector iterator to loop through the stack and print it out
template <typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& a) {
  auto itr = a.begin();
  os << *itr++;
  for(; itr != a.end(); ++itr) {
    os << " " << *itr;
  }
  os << std::endl;
}

// override of vector begin()
template <typename T>
typename std::vector<T>::iterator Stack<T>::begin() {
  return mystack.begin();
}

// override of vector const begin()
template <typename T>
typename std::vector<T>::const_iterator Stack<T>::begin() const {
  return mystack.begin();
}

// override of vector end()
template <typename T>
typename std::vector<T>::iterator Stack<T>::end() {
  return mystack.end();
}

// override of vector const end()
template <typename T>
typename std::vector<T>::const_iterator Stack<T>::end() const {
  return mystack.end();
}

// return true if a and b are the same size and contain the same elements
template <typename T>
bool operator==(const Stack<T>& a, const Stack<T>& b) {
  if(a.size() != b.size()) {
    return false;
  }else{
    auto it1 = a.begin();
    auto it2 = b.begin();
    while(it1 != a.end() && it2 != b.end()) {
      if(*it1 != *it2) {
        return false;
      }
      ++it1;
      ++it2;
    }
    return true;
  }
}

// return opposite of operator==
template <typename T>
bool operator!=(const Stack<T>& a, const Stack<T>& b) {
  return !(a == b);
}

// return true if every element of a is <= b
template <typename T>
bool operator<=(const Stack<T>& a, const Stack<T>& b) {
  auto it1 = a.begin();
  auto it2 = b.begin();
  while(it1 != a.end() && it2 != b.end()) {
    if(*it1 > *it2) {
      return false;
    }
    ++it1;
    ++it2;
  }
  return true;
}

#endif
