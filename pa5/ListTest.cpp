// James Tennant • jtennant • pa5

#include "List.h"
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

void provided();

void printInfo(const List& L);

int main() {

    cout << "\033[35m"; // Change color

    cout << "Hello ListTest!\n";

    List L;
    printInfo(L);

    L.insertAfter(1);
    printInfo(L);

    L.insertAfter(2);
    L.insertAfter(3);
    L.insertAfter(4);
    printInfo(L);

    L.moveBack();
    L.eraseBefore();
    printInfo(L);

    L.moveFront();
    printInfo(L);

    L.moveNext();
    printInfo(L);

    L.movePrev();
    printInfo(L);

    L.clear();
    printInfo(L);

    L.insertBefore(7);
    L.insertBefore(9);
    L.insertBefore(13);
    printInfo(L);

    L.moveFront();
    L.eraseAfter();
    printInfo(L);

    L.moveNext();
    L.setBefore(4);
    L.setAfter(2);
    printInfo(L);

    L.moveNext();
    L.insertAfter(-4);
    L.insertAfter(-2);
    L.insertAfter(0);
    printInfo(L);

    List R;
    R.insertBefore(4);
    R.insertBefore(2);
    R.insertBefore(0);
    R.insertBefore(-2);
    R.insertBefore(-4);
    printInfo(R);

    cout << (L.equals(R) ? "true" : "false") << endl;
    cout << (R.equals(L) ? "true" : "false") << endl;
    cout << (L == R ? "true" : "false") << endl;
    R.setBefore(21);
    cout << (L.equals(R) ? "true" : "false") << endl;
    cout << (R.equals(L) ? "true" : "false") << endl;
    cout << (L == R ? "true" : "false") << endl;

    cout << L.findNext(0) << endl;
    cout << L.findNext(5) << endl;
    cout << L.findPrev(2) << endl;

    cout << L << endl;
    cout << R << endl;
    L = L.concat(R);
    L.movePrev();
    printInfo(L);

    cout << "\033[0m"; // Reset color

    provided(); // Run test provided in ListClient.cpp

    return 0;
}

void printInfo(const List& L) {
    cout << endl;
    cout << "length front back position peekPrev peekNext\n";
    cout << L.length();
    if (L.length() > 0) {
        cout << setw(9) << L.front();
        cout << setw(6) << L.back();
    } else {
        cout << setw(9) << "NA";
        cout << setw(6) << "NA";
    }
    cout << setw(5) << L.position();
    if (L.position() > 0) {
        cout << setw(9) << L.peekPrev();
    } else {
        cout << setw(9) << "NA";
    }
    if (L.position() < L.length()) {
        cout << setw(9) << L.peekNext();
    } else {
        cout << setw(9) << "NA";
    }
    cout << endl;
    cout << L << endl;
}

void provided() {
    cout << "\nProvided test from ListClient.cpp:\n";

    int i, n = 10;
    List A, B, C, D;

    for (i = 1; i <= n; i++) {
        A.insertAfter(i);
        B.insertAfter(11 - i);
        C.insertBefore(i);
        D.insertBefore(11 - i);
    }

    cout << endl;
    cout << "A = " << A << endl;
    cout << "A.position() = " << A.position() << endl;
    cout << "B = " << B << endl;
    cout << "B.position() = " << B.position() << endl;
    cout << "C = " << C << endl;
    cout << "C.position() = " << C.position() << endl;
    cout << "D = " << D << endl;
    cout << "D.position() = " << D.position() << endl;
    cout << endl;

    A.moveBack();
    B.moveBack();
    C.moveFront();
    D.moveFront();

    cout << "A = " << A << endl;
    cout << "A.position() = " << A.position() << endl;
    cout << "B = " << B << endl;
    cout << "B.position() = " << B.position() << endl;
    cout << "C = " << C << endl;
    cout << "C.position() = " << C.position() << endl;
    cout << "D = " << D << endl;
    cout << "D.position() = " << D.position() << endl;

    cout << endl
         << "B: ";
    for (i = 1; i <= 7; i++) {
        cout << B.movePrev() << " ";
    }
    cout << endl
         << "B.position() = " << B.position() << endl;

    cout << endl
         << "C: ";
    for (i = 1; i <= 7; i++) {
        cout << C.moveNext() << " ";
    }
    cout << endl
         << "C.position() = " << C.position() << endl;

    cout << endl;
    cout << "A==B is " << (A == B ? "true" : "false") << endl;
    cout << "B==C is " << (B == C ? "true" : "false") << endl;
    cout << "C==D is " << (C == D ? "true" : "false") << endl;
    cout << "D==A is " << (D == A ? "true" : "false") << endl;
    cout << endl;

    cout << B.findNext(5) << endl;
    cout << B << endl;
    B.eraseBefore();
    B.eraseAfter();
    cout << B << endl;
    cout << B.position() << endl;
    cout << B.findPrev(2) << endl;
    B.eraseBefore();
    B.eraseAfter();
    cout << B << endl;
    cout << B.position() << endl;
    cout << B.findNext(20) << endl;
    cout << B.position() << endl;
    cout << B.findPrev(20) << endl;
    cout << B.position() << endl;
    cout << endl;

    for (i = 10; i >= 1; i--) {
        A.insertAfter(i);
        A.movePrev();
    }
    cout << "A = " << A << endl;
    for (i = 1; i <= 15; i++) {
        A.moveNext();
    }
    cout << A.position() << endl;
    // A.cleanup();
    // cout << "A = " << A << endl;
    // cout << A.position() << endl;
    // cout << endl;

    // List E = A;
    // cout << "E==A is " << (E == A ? "true" : "false") << endl;

    // cout << endl;

    // List F = A.concat(B);
    // cout << "F = " << F << endl;
    // cout << "length: " << F.length() << endl;
    // cout << "front: " << F.front() << endl;
    // cout << "back: " << F.back() << endl;
    // cout << "position: " << F.position() << endl;
    // for (i = 1; i <= 7; i++) {
    //     cout << "peekNext: " << F.peekNext() << endl;
    //     F.insertBefore(-i);
    //     cout << F.moveNext() << endl;
    // }
    // cout << "F = " << F << endl;

    // cout << endl;

    // cout << "test exceptions: " << endl;
    // cout << "A = " << A << endl;
    // A.moveFront();
    // try {
    //     A.peekPrev();
    // } catch (std::range_error& e) {
    //     cout << e.what() << endl;
    //     cout << "   continuing without interruption" << endl;
    // }
    // try {
    //     A.movePrev();
    // } catch (std::range_error& e) {
    //     cout << e.what() << endl;
    //     cout << "   continuing without interruption" << endl;
    // }
    // try {
    //     A.setBefore(5);
    // } catch (std::range_error& e) {
    //     cout << e.what() << endl;
    //     cout << "   continuing without interruption" << endl;
    // }
    // try {
    //     A.eraseBefore();
    // } catch (std::range_error& e) {
    //     cout << e.what() << endl;
    //     cout << "   continuing without interruption" << endl;
    // }
    // A.moveBack();
    // try {
    //     A.peekNext();
    // } catch (std::range_error& e) {
    //     cout << e.what() << endl;
    //     cout << "   continuing without interruption" << endl;
    // }
    // try {
    //     A.moveNext();
    // } catch (std::range_error& e) {
    //     cout << e.what() << endl;
    //     cout << "   continuing without interruption" << endl;
    // }
    // try {
    //     A.setAfter(5);
    // } catch (std::range_error& e) {
    //     cout << e.what() << endl;
    //     cout << "   continuing without interruption" << endl;
    // }
    // try {
    //     A.eraseAfter();
    // } catch (std::range_error& e) {
    //     cout << e.what() << endl;
    //     cout << "   continuing without interruption" << endl;
    // }
    // A.clear();
    // try {
    //     A.front();
    // } catch (std::length_error& e) {
    //     cout << e.what() << endl;
    //     cout << "   continuing without interruption" << endl;
    // }
    // try {
    //     A.back();
    // } catch (std::length_error& e) {
    //     cout << e.what() << endl;
    //     cout << "   continuing without interruption" << endl;
    // }

    // cout << endl;
}
