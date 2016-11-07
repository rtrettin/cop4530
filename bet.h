#ifndef BET_H
#define BET_H

#include <string>
using std::string;

class BET{
  public:
    BET();
    BET(const string postfix);
    BET(const BET&);
    ~BET();
    bool buildFromPostfix(const string postfix);
    const BET & operator=(const BET&);
    void printInfixExpression();
    void printPostfixExpression();
    size_t size();
    size_t leaf_nodes();
    bool empty();
  private:
    struct BinaryNode {
      string element;
      BinaryNode *left;
      BinaryNode *right;
      BinaryNode(const string &e, BinaryNode *l = NULL, BinaryNode *r = NULL) : element(e), left(l), right(r) {}
    };
    BinaryNode *root;
    void printInfixExpression(BinaryNode *n);
    void printPostfixExpression(BinaryNode *n);
    void makeEmpty(BinaryNode* &t);
    BinaryNode * clone(BinaryNode *t) const;
    size_t size(BinaryNode *t);
    size_t leaf_nodes(BinaryNode *t);
};

#endif
