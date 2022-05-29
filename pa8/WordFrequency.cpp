// James Tennant • jtennant • pa8

#include "Dictionary.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {

  // check for correct number of arguments
  if (argc != 3) {
    cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
    return 1;
  }

  // open input file for reading
  ifstream in;
  in.open(argv[1]);
  if (!in.is_open()) {
    cerr << "Unable to open file " << argv[1] << " for reading" << endl;
    return 1;
  }

  // open output file for writing
  ofstream out;
  out.open(argv[2]);
  if (!out.is_open()) {
    cerr << "Unable to open file " << argv[2] << " for writing" << endl;
    return 1;
  }

  Dictionary D;

  string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";

  string line;
  while (getline(in, line)) {
    size_t len = line.length();

    // get first token
    size_t begin = min(line.find_first_not_of(delim, 0), len);
    size_t end = min(line.find_first_of(delim, begin), len);
    string token = line.substr(begin, end - begin);

    while (token != "") { // we have a token

      // convert to lower case
      for (size_t i = 0; i < token.length(); i++) {
        token[i] = tolower(token[i]);
      }

      if (D.contains(token)) {
        D.getValue(token) += 1; // already exists
      } else {
        D.setValue(token, 1); // new word
      }

      // get next token
      begin = min(line.find_first_not_of(delim, end + 1), len);
      end = min(line.find_first_of(delim, begin), len);
      token = line.substr(begin, end - begin);
    }
  }

  out << D << endl;

  // close files
  in.close();
  out.close();

  return 0;
}
