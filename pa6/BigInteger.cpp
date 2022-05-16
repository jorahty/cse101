// James Tennant • jtennant • pa6

#include "BigInteger.h"
#include "List.h"
#include <iostream>
#include <string>

// Define global constants base & power
const int power = 2;
const long base = 100;

// ██ Constructors & Destructors ██

// BigInteger()
// Constructor that creates a new BigInteger in the zero state:
// signum=0, digits=().
BigInteger::BigInteger() {
    signum = 0;
    digits = List();
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s) {
    if (s.size() == 0) {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }

    // Handle sign prefix
    if (s[0] == '+' || s[0] == '-') {
        signum = (s[0] == '+') ? 1 : -1;
        s = s.substr(1, s.size() - 1);
    } else {
        signum = 1;
    }

    if (s.size() == 0) {
        throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
    }

    // Check for non-numeric character
    if (s.find_first_not_of("0123456789") != std::string::npos)
        throw std::invalid_argument("BigInteger: Constructor: non-numeric string");

    digits = List();

    // Handle zero
    if (s == "0") {
        signum = 0;
        return;
    }

    // Chop s into power-wide chunks
    while (s.size() > 0) {

        // Calculate chunkSize
        int remainder = s.size() % power;
        int chunkSize = (remainder != 0) ? remainder : power;

        std::string chunk = s.substr(0, chunkSize); // Get chunk

        long digit = stol(chunk, nullptr, 10); // Convert chunk to digit

        digits.insertBefore(digit); // Insert digit

        s = s.substr(chunkSize, s.size() - chunkSize); // Trim s
    }
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N) {
    signum = N.signum;
    digits = N.digits;
}

// ██ Access functions ██

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive,
// negative or 0, respectively.
int BigInteger::sign() const {
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const {
    if (signum > N.signum) return 1;
    if (signum < N.signum) return -1;
    // same sign

    if (signum == 0) return 0;
    // same sign and nonzero

    if (digits.length() > N.digits.length()) return signum;
    if (digits.length() < N.digits.length()) return -1 * signum;
    // same sign, same length, and nonzero

    // scan from most-significant to least-significant (left to right)
    // for unequal digits
    List this_digits = this->digits;
    List N_digits = N.digits;
    this_digits.moveFront();
    N_digits.moveFront();
    while (this_digits.position() != this_digits.length()) {
        if (this_digits.peekNext() > N_digits.peekNext()) return signum;
        if (this_digits.peekNext() < N_digits.peekNext()) return -1 * signum;

        this_digits.moveNext();
        N_digits.moveNext();
    }

    return 0; // all digits equal
}

// ██ Manipulation procedures ██

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
    signum = 0;
    digits = List();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of
// this BigInteger positive <--> negative.
void BigInteger::negate() {
    signum *= -1;
}

// ██ BigInteger Arithmetic operations ██

// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L);

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn);

// normalizeList()
// Performs carries from right to left (least to most significant 
// digits), then returns the sign of the resulting integer. Used 
// by add(), sub() and mult().
int normalizeList(List& L);

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p);

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m);

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
    std::cout << *this << " + " << N << std::endl;
    return N;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
// BigInteger sub(const BigInteger& N) const;

// mult()
// Returns a BigInteger representing the product of this and N.
// BigInteger mult(const BigInteger& N) const;

// ██ Other Functions ██

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string() {
    if (digits.length() == 0) return "0";

    std::string s = (signum == -1) ? "-" : ""; // add sign prefix

    digits.moveFront();
    s += std::to_string(digits.peekNext()); // add leftmost digit
    digits.moveNext();

    // add remaining digits
    while (digits.position() != digits.length()) { // for each remaining digit
        std::string digit = std::to_string(digits.peekNext());

        // calculate number of leading zeros needed
        int needed_zeros = power - digit.size();

        for (int i = 0; i < needed_zeros; i++)
            s += "0"; // add leading zeros

        s += digit; // add digit

        digits.moveNext();
    }

    return s;
}

// ██ Overriden Operators ██

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<(std::ostream& stream, BigInteger N) {
    return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B.
bool operator==(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) == 0;
}

// operator<()
// Returns true if and only if A is less than B.
bool operator<(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) == -1;
}

// operator<=()
// Returns true if and only if A is less than or equal to B.
bool operator<=(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) == -1 || A.compare(B) == 0;
}

// operator>()
// Returns true if and only if A is greater than B.
bool operator>(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) == 1;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B.
bool operator>=(const BigInteger& A, const BigInteger& B) {
    return A.compare(B) == 1 || A.compare(B) == 0;
}

// operator+()
// Returns the sum A+B.
// friend BigInteger operator+(const BigInteger& A, const BigInteger& B);

// operator+=()
// Overwrites A with the sum A+B.
// friend BigInteger operator+=(BigInteger& A, const BigInteger& B);

// operator-()
// Returns the difference A-B.
// friend BigInteger operator-(const BigInteger& A, const BigInteger& B);

// operator-=()
// Overwrites A with the difference A-B.
// friend BigInteger operator-=(BigInteger& A, const BigInteger& B);

// operator*()
// Returns the product A*B.
// friend BigInteger operator*(const BigInteger& A, const BigInteger& B);

// operator*=()
// Overwrites A with the product A*B.
// friend BigInteger operator*=(BigInteger& A, const BigInteger& B);
