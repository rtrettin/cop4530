#include <iostream>
#include <vector>
#include <stack>
#include <sstream>
#include "bet.h"

using namespace std;

const int PrecPD = 2;
const int PrecAM = 1;

int precedence(string s) {
  if(s == "+" || s == "-") {
    return PrecAM;
  }
  return PrecPD;
}

bool isOperator(string s) {
  if(s == "+" || s == "-" || s == "*" || s == "/") {
    return true;
  }
  return false;
}

BET::BET() : root(nullptr) {
}

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
      n1 = stk.top();
      stk.pop();
      n2 = stk.top();
      stk.pop();
      root->right = n1;
      root->left = n2;
      stk.push(root);
    }
  }
  root = stk.top();
  stk.pop();
}

BET::BET(const BET& bet) : root(nullptr) {
  BinaryNode * copy = clone(bet.root);
  root = copy;
}

BET::~BET() {
  makeEmpty(root);
  root = NULL;
}

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
      n1 = stk.top();
      stk.pop();
      n2 = stk.top();
      stk.pop();
      root->right = n1;
      root->left = n2;
      stk.push(root);
    }
  }
  root = stk.top();
  stk.pop();
  if(!empty()) {
    return true;
  }
  return false;
}

const BET & BET::operator=(const BET &rhs) {
  if(!empty()) {
    makeEmpty(root);
    root = NULL;
  }
  BinaryNode * copy = clone(rhs.root);
  root = copy;
  return *this;
}

void BET::printInfixExpression() {
  printInfixExpression(root);
  cout << endl;
}

void BET::printPostfixExpression() {
  printPostfixExpression(root);
  cout << endl;
}

bool BET::empty() {
  if(root == nullptr) {
    return true;
  }
  return false;
}

size_t BET::size() {
  if(root == NULL)
    return 0;
  else
    return size(root);
}

size_t BET::leaf_nodes() {
  if(root == NULL)
    return 0;
  else
    return leaf_nodes(root);
}

void BET::printInfixExpression(BinaryNode *t) {
  if(t) {
    printInfixExpression(t->left);
    cout << t->element << " ";
    printInfixExpression(t->right);
  }
}

void BET::printPostfixExpression(BinaryNode *t) {
  if(t) {
    printPostfixExpression(t->left);
    printPostfixExpression(t->right);
    cout << t->element << " ";
  }
}

size_t BET::size(BinaryNode *t) {
  size_t total = 1;
  if(t->left != NULL) total = total + size(t->left);
  if(t->right != NULL) total = total + size(t->right);
  return total;
}

size_t BET::leaf_nodes(BinaryNode *t) {
  if(t == NULL)
    return 0;
  if(t->left == NULL && t->right == NULL)
    return 1;
  else
    return leaf_nodes(t->left) + leaf_nodes(t->right);
}

void BET::makeEmpty(BinaryNode * &t) {
  if(t == NULL)
    return;
  makeEmpty(t->left);
  makeEmpty(t->right);
  delete t;
  t = NULL;
}

BET::BinaryNode * BET::clone(BinaryNode *t) const {
  if(t == NULL) {
    return t;
  }
  BinaryNode * temp = new BinaryNode(t->element);
  temp->left = clone(t->left);
  temp->right = clone(t->right);
  return temp;
}

vector<string> BET::explode(string const &s, char delimiter) {
  vector<string> result;
  istringstream iss(s);

  for(string token; getline(iss, token, delimiter);) {
    result.push_back(move(token));
  }

  return result;
}
