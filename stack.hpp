#ifndef COP4530_STACK_HPP
#define COP4530_STACK_HPP

template <typename T>
Stack<T>::Stack() {
}

template <typename T>
Stack<T>::Stack(const Stack<T> &x) {
  for(typename std::vector<T>::const_iterator itr = x.begin(); itr != x.end(); ++itr) {
    mystack.push_back(*itr);
  }
}

template <typename T>
Stack<T>::Stack(Stack<T> && x) {
  for(typename std::vector<T>::iterator itr = x.begin(); itr != x.end(); ++itr) {
    mystack.push_back(*itr);
  }
  x.clear();
}

template <typename T>
Stack<T>::~Stack() {
}

template <typename T>
Stack<T> & Stack<T>::operator=(const Stack<T> & x) {
  Stack<T> copy = x;
  std::swap(*this, copy);
  return *this;
}

template <typename T>
Stack<T> & Stack<T>::operator=(Stack<T> && x) {
  std::swap(mystack, x.mystack);
  return *this;
}

template <typename T>
bool Stack<T>::empty() const {
  return mystack.empty();
}

template <typename T>
void Stack<T>::clear() {
  mystack.clear();
}

template <typename T>
void Stack<T>::push(const T& x) {
  mystack.push_back(x);
}

template <typename T>
void Stack<T>::push(T && x) {
  mystack.push_back(x);
}

template <typename T>
void Stack<T>::pop() {
  mystack.pop_back();
}

template <typename T>
T& Stack<T>::top() {
  return mystack.back();
}

template <typename T>
const T& Stack<T>::top() const {
  return mystack.back();
}

template <typename T>
int Stack<T>::size() const {
  return mystack.size();
}

template <typename T>
void Stack<T>::print(std::ostream& os, char ofc) const {
  auto itr = mystack.begin();
  os << *itr++;
  for(; itr != mystack.end(); ++itr) {
    os << ofc << *itr;
  }
  os << std::endl;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& a) {
  auto itr = a.begin();
  os << *itr++;
  for(; itr != a.end(); ++itr) {
    os << " " << *itr;
  }
  os << std::endl;
}

template <typename T>
typename std::vector<T>::iterator Stack<T>::begin() {
  return mystack.begin();
}

template <typename T>
typename std::vector<T>::const_iterator Stack<T>::begin() const {
  return mystack.begin();
}

template <typename T>
typename std::vector<T>::iterator Stack<T>::end() {
  return mystack.end();
}

template <typename T>
typename std::vector<T>::const_iterator Stack<T>::end() const {
  return mystack.end();
}

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

template <typename T>
bool operator!=(const Stack<T>& a, const Stack<T>& b) {
  return !(a == b);
}

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
