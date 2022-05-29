// James Tennant • jtennant • pa8

#include "Dictionary.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int main() {

  cout << "Hello DictionaryTest!\n";

  Dictionary A;

  A.setValue("jorah", 21);
  A.setValue("james", 21);
  A.setValue("james", 3);
  A.setValue("bono", 28);
  A.setValue("arya", 12);

  cout << A;
  cout << A.pre_string();

  // cout << A.to_string();
  // cout << (A.contains("james") ? "true\n" : "false\n");
  // cout << (A.contains("obama") ? "true\n" : "false\n");

  // A.remove("bro");
  // A.remove("bono");
  // A.remove("jorah");
  // A.remove("james");
  // A.remove("arya");

  // cout << A.pre_string();

  // Dictionary B = A;

  // cout << endl << A;
  // cout << A.getValue("james") << endl;

  // cout << (A.hasCurrent() ? "true\n" : "false\n");

  // A.begin();
  // cout << A.currentVal() << A.currentKey() << endl;
  // A.next();
  // cout << A.currentVal() << A.currentKey() << "\n\n";

  // A.end();
  // cout << A.currentVal() << A.currentKey() << endl;
  // A.prev();
  // cout << A.currentVal() << A.currentKey() << "\n\n";

  // cout << (A == B ? "true\n" : "false\n");

  // B = A;

  // A.clear();

  return 0;
}
