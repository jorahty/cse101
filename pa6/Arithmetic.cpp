// James Tennant • jtennant • pa6

#include "BigInteger.h"
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

    // read lines
    string line1;
    string line2;
    string line3;
    getline(in, line1);
    getline(in, line2);
    getline(in, line3);

    // init BigIntegers
    BigInteger A = BigInteger(line1);
    BigInteger B = BigInteger(line3);

    BigInteger three = BigInteger("3");
    BigInteger two = BigInteger("2");
    BigInteger nine = BigInteger("9");
    BigInteger sixteen = BigInteger("16");

    // print operations
    out << A << "\n\n";
    out << B << "\n\n";
    out << A + B << "\n\n";
    out << A - B << "\n\n";
    out << A - A << "\n\n";
    out << three * A - two * B << "\n\n";
    out << A * B << "\n\n";
    out << A * A << "\n\n";
    out << B * B << "\n\n";
    out << nine * A * A * A * A + sixteen * B * B * B * B * B << "\n\n";

    // close files
    in.close();
    out.close();

    return 0;
}
