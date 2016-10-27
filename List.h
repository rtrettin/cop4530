#ifndef DL_LIST_H
#define DL_LIST_H
#include <iostream>
#include <initializer_list>

namespace cop4530 {
  template <typename T>
  class List {
    private:
      struct Node {
        T data;
        Node *prev;
        Node *next;
        Node(const T & d = T{}, Node *p = nullptr, Node *n = nullptr) : data{d}, prev{p}, next{n} {}
        Node(T && d, Node *p = nullptr, Node *n = nullptr) : data{std::move(d)}, prev{p}, next{n} {}
      };

    public:
      class const_iterator {
        public:
          const_iterator();
          const T & operator*() const;
          const_iterator & operator++();
          const_iterator operator++(int);
          const_iterator & operator--();
          const_iterator operator--(int);
          bool operator==(const const_iterator &rhs) const;
          bool operator!=(const const_iterator &rhs) const;

        protected:
          Node *current;
          T & retrieve() const;
          const_iterator(Node *p);
          friend class List<T>;
      };

      class iterator : public const_iterator {
        public:
          iterator();
          T & operator*();
          const T & operator*() const;
          iterator & operator++();
          iterator operator++(int);
          iterator & operator--();
          iterator operator--(int);

        protected:
          iterator(Node *p);
          friend class List<T>;
      };

    public:
      List();
      List(const List &rhs);
      List(List && rhs);
      explicit List(int num, const T& val = T{});
      List(const_iterator start, const_iterator end);
      List(std::initializer_list<T> iList);
      ~List();
      const List& operator=(const List &rhs);
      List & operator=(List && rhs);
      List& operator=(std::initializer_list<T> iList);

      int size() const;
      bool empty() const;
      void clear();
      void reverse();
      T& front();
      const T& front() const;
      T& back();
      const T& back() const;
      void push_front(const T & val);
      void push_front(T && val);
      void push_back(const T & val);
      void push_back(T && val);
      void pop_front();
      void pop_back();
      void remove(const T &val);

      template <typename PREDICATE>
      void remove_if(PREDICATE pred);

      void print(std::ostream& os, char ofc = ' ') const;
      iterator begin();
      const_iterator begin() const;
      iterator end();
      const_iterator end() const;
      iterator insert(iterator itr, const T& val);
      iterator insert(iterator itr, T && val);
      iterator erase(iterator itr);
      iterator erase(iterator start, iterator end);

    private:
      int theSize;
      Node *head;
      Node *tail;
      void init();
  };

  template <typename T>
  bool operator==(const List<T> & lhs, const List<T> &rhs);
  template <typename T>
  bool operator!=(const List<T> & lhs, const List<T> &rhs);
  template <typename T>
  std::ostream & operator<<(std::ostream &os, const List<T> &l);

  #include "List.hpp"

}
#endif
