/* Remi Trettin COP4530 Assignment 5 */
#include <iostream>
#include <string>
#include <utility>
#include <cstdlib>
#include <cctype>
#include "passserver.h"

using namespace std;
using namespace cop4530;

void Menu();

int main() {
  char input = 'z'; // menu choice
  char passwordFileName[250];
  string newUsername, newPassword, delUsername, changeUsername, changePassword;
  int tableCap = -1; // hash table size

  while(tableCap < 1) { //prompt for a correct hash table size
    cout << "Enter preferred hash table capacity: ";
    cin >> tableCap;
    if(tableCap < 1) {
      cout << "NO: Hash table capacity must be 1 or more." << endl;
    }
  }

  PassServer server(tableCap); //create table

  do {
    Menu();
    cin >> input;
    input = tolower(input);
    switch(input) {
      case 'l':
        cout << "Enter password file name to load from: ";
        cin >> passwordFileName;
        if(!server.load(passwordFileName)) {
          cout << "NO: Cannot open file " << passwordFileName << "." << endl;
        }
        break;
      case 'a':
        cout << "Enter username: ";
        cin >> newUsername;
        cout << "Enter password: ";
        cin >> newPassword;
        if(server.addUser(make_pair(newUsername, newPassword))) {
          cout << "User " << newUsername << " added." << endl;
        }else{
          cout << "User " << newUsername << " NOT added." << endl;
        }
        break;
      case 'r':
        cout << "Enter username: ";
        cin >> delUsername;
        if(server.removeUser(delUsername)) {
          cout << "User " << delUsername << " removed." << endl;
        }else{
          cout << "User " << delUsername << " NOT removed." << endl;
        }
        break;
      case 'c':
        cout << "Enter username: ";
        cin >> changeUsername;
        cout << "Enter current password: ";
        cin >> changePassword;
        cout << "Enter new password: ";
        cin >> newPassword;
        if(server.changePassword(make_pair(changeUsername, changePassword), newPassword)) {
          cout << "Password changed for user " << changeUsername << endl;
        }else{
          cout << "Password NOT changed for user " << changeUsername << endl;
        }
        break;
      case 'f':
        cout << "Enter username: ";
        cin >> newUsername;
        if(server.find(newUsername)) {
          cout << "User '" << newUsername << "' found." << endl;
        }else{
          cout << "User '" << newUsername << "' NOT found." << endl;
        }
        break;
      case 'd':
        server.dump();
        break;
      case 's':
        cout << "Size of hashtable: " << server.size() << endl;
        break;
      case 'w':
        cout << "Enter password file name to write to: ";
        cin >> passwordFileName;
        if(!server.write_to_file(passwordFileName)) {
          cout << "NO: File not written." << endl;
        }
        break;
      case 'x':
        break;
      default:
        cout << "NO: Invalid menu option." << endl;
        break;
    }
  }while(input != 'x');

  return 0;
}

void Menu() {
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}
