/* Remi Trettin COP4530 Project 3 */
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include "stack.h"

using namespace std;
using namespace cop4530;

// helper functions
bool isOperand(string x);
vector<string> explode(string const &s, char delimiter);
int weight(string x);
bool precedence(string a, string b);
int evalpost(vector<string> p);

int main() {
  Stack<string> operators;
  string answer ("");
  vector<string> operands;
  vector<string> postfix;
  bool eval = true; // whether to evaluate the postfix expression at the end

  // input loop
  while(answer != "exit") {
    cout << "Enter infix expression (\"exit\" to quit): ";
    getline(cin, answer);
    if(answer == "exit" || answer == "") break; // exit loop based on input
    cout << "Postfix expression: ";

    auto infix = explode(answer, ' '); // remove spaces from infix input
    for(auto itt = infix.begin(); itt != infix.end(); ++itt) { // if input contains a letter or _, do not evaluate later
      if((*itt).find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_") != string::npos) {
        eval = false;
      }
    }
    auto itr = infix.begin();
    for(; itr != infix.end(); ++itr) { // do infix to postfix conversion
      if(isOperand(*itr)) {
        cout << *itr << " ";
        operands.push_back(*itr);
        postfix.push_back(*itr);
      }else{
        if(*itr == "(") {
          operators.push(*itr);
        }else if(*itr == "+" || *itr == "-" || *itr == "*" || *itr == "/") {
          while(operators.empty() == false && operators.top() != "(" && precedence(*itr, operators.top()) != true) {
            cout << operators.top() << " ";
            postfix.push_back(operators.top());
            operators.pop();
          }
          operators.push(*itr);
        }else if(*itr == ")" && isOperand(*(itr-1))) {
          while(operators.top() != "(") {
            cout << operators.top() << " ";
            postfix.push_back(operators.top());
            operators.pop();
          }
          operators.pop();
        }else{
          cout << endl << "ERROR" << endl;
          return 0;
        }
      }
    }
    if(isOperand(*(itr-1))) {
      while(operators.empty() == false) {
        cout << operators.top() << " ";
        postfix.push_back(operators.top());
        operators.pop();
      }
    }else{
      cout << endl << "ERROR" << endl;
      return 0;
    }
    cout << endl;

    cout << "Postfix evaluation: ";
    if(eval == true) { // format postfix evaluation output
      for(auto itt = postfix.begin(); itt != postfix.end(); ++itt) {
        cout << *itt << " ";
      }
      cout << " = " << evalpost(postfix);
    }else{
      for(auto itt = postfix.begin(); itt != postfix.end(); ++itt) {
        cout << *itt << " ";
      }
      cout << " = ";
      for(auto itt = postfix.begin(); itt != postfix.end(); ++itt) {
        cout << *itt << " ";
      }
    }
    cout << endl;
    operators.clear(); // clear stacks and vectors for next loop iteration
    operands.clear();
    postfix.clear();
  }

  return 0;
}

// return true if x is an operand, false otherwise
bool isOperand(string x) {
  if(x != "+" && x != "-" && x != "*" && x != "/" && x != "(" && x != ")") {
    return true;
  }else{
    return false;
  }
}

// return a vector of strings without the delimiter character
vector<string> explode(string const &s, char delimiter) {
  vector<string> result;
  istringstream iss(s);

  for(string token; getline(iss, token, delimiter);) {
    result.push_back(move(token));
  }

  return result;
}

// determine the weight of each operator for postfix conversion
int weight(string x) {
  int weight = 0;
  char y;

  if(x == "+")
    y = '+';
  else if(x == "-")
    y = '-';
  else if(x == "*")
    y = '*';
  else
    y = '/';

  switch(y) {
    case '+':
    case '-':
      weight = 1;
      break;
    case '*':
    case '/':
      weight = 2;
      break;
    default:
      weight = 0;
      break;
  }
  return weight;
}

// calculate precedence of each operator
bool precedence(string a, string b) {
  int aw = weight(a);
  int bw = weight(b);
  if(aw > bw) {
    return true;
  }else{
    return false;
  }
}

// evaluate postfix expression
int evalpost(vector<string> p) {
  Stack<double> stk;
  for(auto itt = p.begin(); itt != p.end(); ++itt) {
    if(!isOperand(*itt)) {
      double op2 = stk.top();
      stk.pop();
      double op1 = stk.top();
      stk.pop();
      double result;
      if(*itt == "+") {
        result = op1 + op2;
      }else if(*itt == "-") {
        result = op1 - op2;
      }else if(*itt == "*") {
        result = op1 * op2;
      }else{
        result = op1 / op2;
      }
      stk.push(result);
    }else{
      stk.push(stod(*itt));
    }
  }
  return stk.top();
}
