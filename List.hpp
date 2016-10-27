/* Remi Trettin COP4530 Project 2 */
using namespace cop4530;

// const_iterator default constructor
template <typename T>
List<T>::const_iterator::const_iterator() : current{nullptr} {}

// const_iterator * overload
template <typename T>
const T & List<T>::const_iterator::operator*() const {
  return retrieve();
}

// const_iterator ++ overload
template <typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator++() {
  current = current->next;
  return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int) {
  const_iterator old = *this;
  ++(*this);
  return old;
}

// const_iterator -- overload
template <typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator--() {
  current = current->prev;
  return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int) {
  const_iterator old = *this;
  --(*this);
  return old;
}

// const_iterator == overload
template <typename T>
bool List<T>::const_iterator::operator==(const List<T>::const_iterator & rhs) const {
  return current == rhs.current;
}

// const_iterator != overload
template <typename T>
bool List<T>::const_iterator::operator!=(const List<T>::const_iterator & rhs) const {
  return !(*this == rhs);
}

// return value of const_iterator pointer
template <typename T>
T & List<T>::const_iterator::retrieve() const {
  return current->data;
}

// construct const_iterator at specified Node
template <typename T>
List<T>::const_iterator::const_iterator(Node *p) : current{p} {}

// default iterator constructor
template <typename T>
List<T>::iterator::iterator() {}

// iterator * overload
template <typename T>
T & List<T>::iterator::operator*() {
  return const_iterator::retrieve();
}

template <typename T>
const T & List<T>::iterator::operator*() const {
  return const_iterator::operator*();
}

// iterator ++ overload
template <typename T>
typename List<T>::iterator & List<T>::iterator::operator++() {
  this->current = this->current->next;
  return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator++(int) {
  iterator old = *this;
  ++(*this);
  return old;
}

// iterator -- overload
template <typename T>
typename List<T>::iterator & List<T>::iterator::operator--() {
  this->current = this->current->prev;
  return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator--(int) {
  iterator old = *this;
  --(*this);
  return old;
}

// construct iterator at specified Node
template <typename T>
List<T>::iterator::iterator(Node *p) : const_iterator{p} {}

// default List constructor
template <typename T>
List<T>::List() {
  init();
}

// List destructor
template <typename T>
List<T>::~List() {
  clear();
  delete head;
  delete tail;
}

// List copy constructor
template <typename T>
List<T>::List(const List<T> & rhs) {
  init();
  for(auto & x : rhs) {
    push_back(x);
  }
}

// List = overload
template <typename T>
const List<T> & List<T>::operator=(const List<T> & rhs) {
  List<T> copy = rhs;
  std::swap(*this, copy);
  return *this;
}

// List move constructor
template <typename T>
List<T>::List(List<T> && rhs) : theSize(rhs.theSize), head(rhs.head), tail(rhs.tail) {
  rhs.theSize = 0;
  rhs.head = nullptr;
  rhs.tail = nullptr;
}

// construct List with num items, all set to val
template <typename T>
List<T>::List(int num, const T& val) {
  init();
  for(int i = 0; i < num; i++) {
    push_back(val);
  }
}

// construct List from another List's range
template <typename T>
List<T>::List(const_iterator start, const_iterator end) {
  init();
  for(; start != end; ++start) {
    push_back(*start);
  }
}

// construct List using initializer_list {}
template <typename T>
List<T>::List(std::initializer_list<T> iList) {
  init();
  typename std::initializer_list<T>::iterator it;
  for(it = iList.begin(); it != iList.end(); ++it) {
    push_back(*it);
  }
}

template <typename T>
List<T> & List<T>::operator=(List<T> && rhs) {
  std::swap(theSize, rhs.theSize);
  std::swap(head, rhs.head);
  std::swap(tail, rhs.tail);
  return *this;
}

template <typename T>
List<T>& List<T>::operator=(std::initializer_list<T> iList) {
  clear();
  typename std::initializer_list<T>::iterator it;
  for(it = iList.begin(); it != iList.end(); ++it) {
    push_back(*it);
  }
}

// initialize List with size 0 and head/tail sentinel nodes
template <typename T>
void List<T>::init() {
  theSize = 0;
  head = new Node;
  tail = new Node;
  head->next = tail;
  tail->prev = head;
}

// insert new Node in List at position itr with value val
template <typename T>
typename List<T>::iterator List<T>::insert(List<T>::iterator itr, const T & val) {
  Node *p = itr.current;
  theSize++;
  return { p->prev = p->prev->next = new Node{val, p->prev, p} };
}

template <typename T>
typename List<T>::iterator List<T>::insert(List<T>::iterator itr, T && val) {
  Node *p = itr.current;
  theSize++;
  return { p->prev = p->prev->next = new Node{std::move(val), p->prev, p} };
}

// erase Node in List at position itr
template <typename T>
typename List<T>::iterator List<T>::erase(List<T>::iterator itr) {
  Node *p = itr.current;
  iterator retVal{p->next};
  p->prev->next = p->next;
  p->next->prev = p->prev;
  delete p;
  theSize--;
  return retVal;
}

// erase all Nodes in List between start,end
template <typename T>
typename List<T>::iterator List<T>::erase(List<T>::iterator start, List<T>::iterator end) {
  for(iterator itr = start; itr != end;) {
    itr = erase(itr);
  }
  return end;
}

// return iterator at beginning of List
template <typename T>
typename List<T>::const_iterator List<T>::begin() const {
  return { head->next };
}

template <typename T>
typename List<T>::iterator List<T>::begin() {
  return { head->next };
}

// return iterator at end of List
template <typename T>
typename List<T>::const_iterator List<T>::end() const {
  return { tail };
}

template <typename T>
typename List<T>::iterator List<T>::end() {
  return { tail };
}

// return size of List
template <typename T>
int List<T>::size() const {
  return theSize;
}

// return true if List is empty
template <typename T>
bool List<T>::empty() const {
  return size() == 0;
}

// remove all Nodes in List
template <typename T>
void List<T>::clear() {
  while(!empty()) {
    pop_front();
  }
}

// return first item in List
template <typename T>
T& List<T>::front() {
  return *begin();
}

template <typename T>
const T& List<T>::front() const {
  return *begin();
}

// return last item in List
template <typename T>
T& List<T>::back() {
  return *--end();
}

template <typename T>
const T& List<T>::back() const {
  return *--end();
}

// insert front
template <typename T>
void List<T>::push_front(const T & val) {
  insert(begin(), val);
}

template <typename T>
void List<T>::push_front(T && val) {
  insert(begin(), std::move(val));
}

// insert back
template <typename T>
void List<T>::push_back(const T & val) {
  insert(end(), val);
}

template <typename T>
void List<T>::push_back(T && val) {
  insert(end(), std::move(val));
}

// remove front
template <typename T>
void List<T>::pop_front() {
  erase(begin());
}

// remove back
template <typename T>
void List<T>::pop_back() {
  erase(--end());
}

// remove from List where item = val
template <typename T>
void List<T>::remove(const T &val) {
  auto itr = begin();
  for(; itr != end(); ++itr) {
    if(*itr == val) {
      erase(itr);
    }
  }
}

// List << overload
template <typename T>
std::ostream & operator<<(std::ostream &os, const List<T> &l) {
  auto itr = l.begin();
  os << *itr++;
  for(; itr != l.end(); ++itr) {
    os << " " << *itr;
  }
  os << std::endl;
}

// output List contents with ofc delimiter
template <typename T>
void List<T>::print(std::ostream& os, char ofc) const {
  auto itr = begin();
  os << *itr++;
  for(; itr != end(); ++itr) {
    os << ofc << *itr;
  }
  os << std::endl;
}

// List == overload
template <typename T>
bool operator==(const List<T> & lhs, const List<T> &rhs) {
  if(lhs.size() == rhs.size()) {
    auto itr_l = lhs.begin();
    auto itr_r = rhs.begin();
    for(; itr_l != lhs.end(); ++itr_l) {
      for(; itr_r != rhs.end(); ++itr_r) {
        if(*itr_l != *itr_r) {
          return false;
        }
      }
    }
    return true;
  }else{
    return false;
  }
}

// List != overload
template <typename T>
bool operator!=(const List<T> & lhs, const List<T> &rhs) {
  return !(lhs == rhs);
}

// reverse order of List
template <typename T>
void List<T>::reverse() {
  int count = 0;
  int total = theSize / 2;
  auto itr = --end();
  auto itr_s = begin();
  T temp;
  while(count < total) {
    temp = *itr;
    *itr = *itr_s;
    *itr_s = temp;
    itr--;
    itr_s++;
    count++;
  }
}

// remove from List if specified condition is true
template <typename T>
template <typename PREDICATE>
void List<T>::remove_if(PREDICATE pred) {
  auto itr = begin();
  for(; itr != end(); ++itr) {
    if(pred(*itr)) {
      erase(itr);
    }
  }
}
