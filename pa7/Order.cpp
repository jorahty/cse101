// James Tennant • jtennant • pa7

#include "Dictionary.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
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

  // insert line and line number into dictionary

  Dictionary D;

  string line;
  int line_count = 0;
  while (getline(in, line)) {
    line_count++;

    D.setValue(line, line_count);
  }

  out << D << endl;
  out << D.pre_string() << endl;

  // close files
  in.close();
  out.close();

  return 0;
}
