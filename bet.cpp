/* Remi Trettin COP4530 Project 4 */
#include <iostream>
#include <vector>
#include <stack>
#include <sstream>
#include "bet.h"

using namespace std;

const int PrecPD = 2;
const int PrecAM = 1;

// determine operator precedence
int precedence(string s) {
  if(s == "+" || s == "-") {
    return PrecAM;
  }
  return PrecPD;
}

// return true if s is an operator
bool isOperator(string s) {
  if(s == "+" || s == "-" || s == "*" || s == "/") {
    return true;
  }
  return false;
}

// default constructor - set root to null
BET::BET() : root(nullptr) {
}

// build a BET from a postfix expression
BET::BET(string postfix) : root(nullptr) {
  stack<BinaryNode *> stk;
  BinaryNode *n1, *n2;
  auto temp = explode(postfix, ' ');
  for(auto itr = temp.begin(); itr != temp.end(); ++itr) {
    if(!isOperator(*itr)) {
      root = new BinaryNode(*itr);
      stk.push(root);
    }else{
      root = new BinaryNode(*itr);
      if(stk.empty()) {
        makeEmpty(root);
        root = NULL;
        return;
      }
      n1 = stk.top();
      stk.pop();
      n2 = stk.top();
      stk.pop();
      root->right = n1;
      root->left = n2;
      stk.push(root);
    }
  }
  if(stk.empty()) {
    makeEmpty(root);
    root = NULL;
    return;
  }
  root = stk.top();
  stk.pop();
  if(!stk.empty()) {
    makeEmpty(root);
    root = NULL;
    return;
  }
}

// build a BET from another BET using the private clone() function
BET::BET(const BET& bet) : root(nullptr) {
  BinaryNode * copy = clone(bet.root);
  root = copy;
}

// destructor - delete necessary memory
BET::~BET() {
  makeEmpty(root);
  root = NULL;
}

// rebuild BET from a postfix expression
bool BET::buildFromPostfix(const string postfix) {
  if(!empty()) {
    makeEmpty(root);
    root = NULL;
  }
  stack<BinaryNode *> stk;
  BinaryNode *n1, *n2;
  auto temp = explode(postfix, ' ');
  for(auto itr = temp.begin(); itr != temp.end(); ++itr) {
    if(!isOperator(*itr)) {
      root = new BinaryNode(*itr);
      stk.push(root);
    }else{
      root = new BinaryNode(*itr);
      if(stk.empty()) {
        makeEmpty(root);
        root = NULL;
        return false;
      }
      n1 = stk.top();
      stk.pop();
      n2 = stk.top();
      stk.pop();
      root->right = n1;
      root->left = n2;
      stk.push(root);
    }
  }
  if(stk.empty()) {
    makeEmpty(root);
    root = NULL;
    return false;
  }
  root = stk.top();
  stk.pop();
  if(!stk.empty()) {
    makeEmpty(root);
    root = NULL;
    return false;
  }
  return true;
}

// assignment operator
const BET & BET::operator=(const BET &rhs) {
  if(!empty()) {
    makeEmpty(root);
    root = NULL;
  }
  BinaryNode * copy = clone(rhs.root);
  root = copy;
  return *this;
}

// public interface
void BET::printInfixExpression() {
  printInfixExpression(root);
  cout << endl;
}

// public interface
void BET::printPostfixExpression() {
  printPostfixExpression(root);
  cout << endl;
}

// return true if the BET is empty
bool BET::empty() {
  if(root == nullptr) {
    return true;
  }
  return false;
}

// public interface
size_t BET::size() {
  if(root == NULL)
    return 0;
  else
    return size(root);
}

// public interface
size_t BET::leaf_nodes() {
  if(root == NULL)
    return 0;
  else
    return leaf_nodes(root);
}

// private function to traverse the tree inorder using recursion
void BET::printInfixExpression(BinaryNode *t) {
  if(t) {
    printInfixExpression(t->left);
    cout << t->element << " ";
    printInfixExpression(t->right);
  }
}

// private function to print the postfix expression using recursion
void BET::printPostfixExpression(BinaryNode *t) {
  if(t) {
    printPostfixExpression(t->left);
    printPostfixExpression(t->right);
    cout << t->element << " ";
  }
}

// return the size of the tree using recursion
size_t BET::size(BinaryNode *t) {
  size_t total = 1;
  if(t->left != NULL) total = total + size(t->left);
  if(t->right != NULL) total = total + size(t->right);
  return total;
}

// return the number of leaf nodes using recursion
size_t BET::leaf_nodes(BinaryNode *t) {
  if(t == NULL)
    return 0;
  if(t->left == NULL && t->right == NULL)
    return 1;
  else
    return leaf_nodes(t->left) + leaf_nodes(t->right);
}

// empty the tree using recursion
void BET::makeEmpty(BinaryNode * &t) {
  if(t == NULL)
    return;
  makeEmpty(t->left);
  makeEmpty(t->right);
  delete t;
  t = NULL;
}

// clone the tree denoted by t using recursion
BET::BinaryNode * BET::clone(BinaryNode *t) const {
  if(t == NULL) {
    return t;
  }
  BinaryNode * temp = new BinaryNode(t->element);
  temp->left = clone(t->left);
  temp->right = clone(t->right);
  return temp;
}

// return a vector of strings without the delimiter character
vector<string> BET::explode(string const &s, char delimiter) {
  vector<string> result;
  istringstream iss(s);

  for(string token; getline(iss, token, delimiter);) {
    result.push_back(move(token));
  }

  return result;
}
