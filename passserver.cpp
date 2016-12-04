/* Remi Trettin COP4530 Assignment 5 */
#include "passserver.h"

// inits the hash table
PassServer::PassServer(size_t size) : passwords(size) {
}

// no clean up needed
PassServer::~PassServer() {
}

// adds a user to the hash table
bool PassServer::addUser(const pair<string, string> &key_value) {
  pair<string, string> temp = key_value;
  temp.second = encrypt(temp.second);
  return passwords.insert(temp);
}

// move version of add user
bool PassServer::addUser(pair<string, string> &&key_value) {
  return addUser(key_value);
}

// removes a user from the table
bool PassServer::removeUser(const string &k) {
  return passwords.remove(k);
}

// changes a user's password based on a few verification checks
bool PassServer::changePassword(const pair<string, string> &p, const string &newpasswd) {
  if(passwords.contains(p.first)) {
    string pw1 = encrypt(p.second);
    string pw2 = encrypt(newpasswd);
    pair<string, string> temp = make_pair(p.first, pw1);
    pair<string, string> temp2 = make_pair(p.first, pw2);
    if(passwords.match(temp)) {
      if(pw1 != pw2) {
        passwords.remove(p.first);
        return passwords.insert(temp2);
      }else{
        return false;
      }
    }else{
      return false;
    }
  }else{
    return false;
  }
}

// returns true if the username is in the table
bool PassServer::find(const string &k) const {
  return passwords.contains(k);
}

// loads a hash table from a file
bool PassServer::load(const char *filename) {
  return passwords.load(filename);
}

// writes the hash table to a file
bool PassServer::write_to_file(char *filename) {
  return passwords.write_to_file(filename);
}

// outputs the hash table
void PassServer::dump() const {
  passwords.dump();
}

// returns the current table size
size_t PassServer::size() const {
  return passwords.size();
}

// uses crypt() to encrypt the inputted plaintext password
string PassServer::encrypt(const string &str) {
  char salt[] = "$1$########";
  char * password = new char[250];
  strcpy(password, crypt(str.c_str(), salt));
  string encrypted = password;
  delete [] password;
  return encrypted.substr(12);
}
