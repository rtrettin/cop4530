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
  string temp;
  for(int i = 0; i < postfix.length(); i++) {
    temp = postfix[i];
    if(temp == " ") continue;
    if(!isOperator(temp)) {
      root = new BinaryNode(temp);
      stk.push(root);
    }else{
      root = new BinaryNode(temp);
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
  //
}

BET::~BET() {
  //
}

bool BET::buildFromPostfix(const string postfix) {
  if(!empty()) {
    //makeEmpty(this);
  }
  stack<BinaryNode *> stk;
  BinaryNode *n1, *n2;
  string temp;
  for(int i = 0; i < postfix.length(); i++) {
    temp = postfix[i];
    if(temp == " ") continue;
    if(!isOperator(temp)) {
      root = new BinaryNode(temp);
      stk.push(root);
    }else{
      root = new BinaryNode(temp);
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
  //
}

void BET::printInfixExpression() {
  printInfixExpression(root);
  cout << endl;
}

void BET::printPostfixExpression() {
  printPostfixExpression(root);
}

bool BET::empty() {
  if(root == nullptr) {
    return true;
  }
  return false;
}

size_t BET::size() {
  return size(root);
}

size_t BET::leaf_nodes() {
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
  //
}

size_t BET::size(BinaryNode *t) {
  //
}

size_t BET::leaf_nodes(BinaryNode *t) {
  //
}

void BET::makeEmpty(BinaryNode * &t) {
  //
}

BET::BinaryNode * BET::clone(BinaryNode *t) const {
  //
}
