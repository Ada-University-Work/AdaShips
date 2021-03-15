#include "headers/helpers.h"

using namespace std;

string lowercase_word(string word){
  string lowercase_word;
  for (int i=0; i<word.length(); i++) {
    lowercase_word += tolower(word[i]);
  }
  return lowercase_word;
};