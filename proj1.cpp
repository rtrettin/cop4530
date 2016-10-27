/* Remi Trettin COP4530 Project 1 */
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <stdio.h>
#include <map>
#include <algorithm>
using namespace std;

// function to swap the order of a pair
template<typename A, typename B>
pair<B,A> swapPair(const pair<A,B> &p) {
    return pair<B,A>(p.second, p.first);
}

// function that swaps pairs in a map and places them in a multimap for sorting
template<typename A, typename B>
multimap<B,A> swapMap(const map<A,B> &src) {
    multimap<B,A> dst;
    transform(src.begin(), src.end(), inserter(dst, dst.begin()), swapPair<A,B>);
    return dst;
}

int main() {
  // variables needed to read file
  vector<char> file;
  vector<char>::iterator it;
  char input;

  // variables for characters
  map<char,int> characters;
  map<char,int>::iterator charit;

  // variables for words
  map<string,int> words;
  map<string,int>::iterator wordit;

  // variables for numbers
  map<string,int> numbers;
  map<string,int>::iterator numit;

  // read file into vector
  while(true) {
    if(cin.peek() == EOF) {
      break;
    }
    it = file.begin();
    cin.get(input);
    file.insert(it, input);
  }

  // loop through vector and insert character counts into map
  for(int i = file.size()-1; i >= 0; i--) {
    charit = characters.find(file[i]);
    if(charit == characters.end()) {
      characters.insert(pair<char,int>(file[i], 1));
    }else{
      characters[file[i]] = characters[file[i]] + 1;
    }
  }

  // sort characters map by value -> store in multimap
  multimap<int,char> sortedCharacters = swapMap(characters);

  // loop through vector and insert number counts into map
  for(int i = file.size()-1; i >= 0; i--) {
    if(isdigit(file[i]) == 1) {
      string digit (1, file[i]);
      while(isdigit(file[i-1]) == 1) {
        digit += file[i-1];
        i--;
      }
      numit = numbers.find(digit);
      if(numit == numbers.end()) {
        numbers.insert(pair<string,int>(digit, 1));
      }else{
        numbers[digit] = numbers[digit] + 1;
      }
    }
  }

  // sort numbers map by value -> store in multimap
  multimap<int,string> sortedNumbers = swapMap(numbers);

  // make vector lowercase for word stats
  for(int i = file.size()-1; i >= 0; i--) {
    file[i] = tolower(file[i]);
  }

  // loop through vector and insert word counts into map
  for(int i = file.size()-1; i >= 0; i--) {
    if(isalpha(file[i])) {
      string w (1, file[i]);
      while(isalpha(file[i-1])) {
        w += file[i-1];
        i--;
      }
      wordit = words.find(w);
      if(wordit == words.end()) {
        words.insert(pair<string,int>(w, 1));
      }else{
        words[w] = words[w] + 1;
      }
    }
  }

  // sort words map by value -> store in multimap
  multimap<int,string> sortedWords = swapMap(words);

  // output character stats
  cout << "Total " << characters.size() << " different characters, ";
  if(characters.size() < 10) {
    cout << characters.size() << " most used characters:" << endl;
    int i = 0;
    for(multimap<int,char>::iterator itc = sortedCharacters.end(); itc != sortedCharacters.begin(); --itc) {
      if(i == 0) itc--;
      if((*itc).second == '\n') {
        cout << "No. " << i << ": ";
        printf("\\n");
        cout << "\t\t" << (*itc).first << endl;
      }else if((*itc).second == '\t') {
        cout << "No. " << i << ": ";
        printf("\\t");
        cout << "\t\t" << (*itc).first << endl;
      }else if((*itc).second == '\r') {
        cout << "No. " << i << ": ";
        printf("\\r");
        cout << "\t\t" << (*itc).first << endl;
      }else{
        cout << "No. " << i << ": " << (*itc).second << "\t\t" << (*itc).first << endl;
      }
      i++;
    }
    multimap<int,char>::iterator itc = sortedCharacters.begin();
    cout << "No. " << i << ": " << (*itc).second << "\t\t" << (*itc).first << endl;
  }else{
    cout << "10 most used characters:" << endl;
    int i = 0;
    for(multimap<int,char>::iterator itc = sortedCharacters.end(); itc != sortedCharacters.begin(); --itc) {
      if(i == 0) itc--;
      if(i < 10) {
        if((*itc).second == '\n') {
          cout << "No. " << i << ": ";
          printf("\\n");
          cout << "\t\t" << (*itc).first << endl;
        }else if((*itc).second == '\t') {
          cout << "No. " << i << ": ";
          printf("\\t");
          cout << "\t\t" << (*itc).first << endl;
        }else if((*itc).second == '\r') {
          cout << "No. " << i << ": ";
          printf("\\r");
          cout << "\t\t" << (*itc).first << endl;
        }else{
          cout << "No. " << i << ": " << (*itc).second << "\t\t" << (*itc).first << endl;
        }
        i++;
      }else{
        break;
      }
    }
  }
  cout << endl;

  // output word stats
  cout << "Total " << words.size() << " different words, ";
  if(words.size() < 10) {
    cout << words.size() << " most used words:" << endl;
    int i = 0;
    for(multimap<int,string>::reverse_iterator itw = sortedWords.rbegin(); itw != sortedWords.rend(); ++itw) {
      cout << "No. " << i << ": " << (*itw).second << "\t\t" << (*itw).first << endl;
      i++;
    }
  }else{
    cout << "10 most used words:" << endl;
    int i = 0;
    for(multimap<int,string>::reverse_iterator itw = sortedWords.rbegin(); itw != sortedWords.rend(); ++itw) {
      if(i < 10) {
        cout << "No. " << i << ": " << (*itw).second << "\t\t" << (*itw).first << endl;
        i++;
      }else{
        break;
      }
    }
  }
  cout << endl;

  // output number stats
  cout << "Total " << numbers.size() << " different numbers, ";
  if(numbers.size() < 10) {
    cout << numbers.size() << " most used numbers:" << endl;
    int i = 0;
    for(multimap<int,string>::reverse_iterator itn = sortedNumbers.rbegin(); itn != sortedNumbers.rend(); ++itn) {
      cout << "No. " << i << ": " << (*itn).second << "\t\t" << (*itn).first << endl;
      i++;
    }
  }else{
    cout << "10 most used numbers:" << endl;
    int i = 0;
    for(multimap<int,string>::reverse_iterator itn = sortedNumbers.rbegin(); itn != sortedNumbers.rend(); ++itn) {
      if(i < 10) {
        cout << "No. " << i << ": " << (*itn).second << "\t\t" << (*itn).first << endl;
        i++;
      }else{
        break;
      }
    }
  }

  return 0;
}
