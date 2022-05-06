// James Tennant • jtennant • pa5

#include "List.h"
#include <iomanip>
#include <iostream>

using namespace std;

void shuffle(List& D);

int main(int argc, char* argv[]) {

    // Check for correct number of arguments
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <max deck size>\n";
        return 1;
    }

    int n = atoi(argv[1]); // Get max deck size

    // Print header
    cout << "deck size       shuffle count\n------------------------------\n";

    // For deck size in [1, n]
    List A;
    for (int size = 1; size <= n; size++) {

        int count = 0;

        A.insertBefore(size - 1);
        List B = A;

        do {
            shuffle(B);
            count++;
        } while (!(B == A));

        cout << " " << left << setw(16) << size << count << endl;
    }

    return 0;
}

void shuffle(List& D) {
    int n = D.length();

    List A, B;

    for (D.moveFront(); D.position() < n; D.moveNext()) {
        int x = D.peekNext();
        if (D.position() < n / 2) {
            A.insertBefore(x);
        } else {
            B.insertBefore(x);
        }
    }

    D.clear();
    A.moveFront();
    B.moveFront();

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            int x = B.peekNext();
            B.moveNext();
            D.insertBefore(x);
            continue;
        }
        int x = A.peekNext();
        A.moveNext();
        D.insertBefore(x);
    }
}
