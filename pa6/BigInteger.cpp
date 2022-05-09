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
// BigInteger(std::string s);

// BigInteger()
// Constructor that creates a copy of N.
// BigInteger(const BigInteger& N);

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
// int compare(const BigInteger& N) const;

// ██ Manipulation procedures ██

// makeZero()
// Re-sets this BigInteger to the zero state.
// void makeZero();

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of
// this BigInteger positive <--> negative.
// void negate();

// ██ BigInteger Arithmetic operations ██

// add()
// Returns a BigInteger representing the sum of this and N.
// BigInteger add(const BigInteger& N) const;

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
// std::string to_string();

// ██ Overriden Operators ██

// operator<<()
// Inserts string representation of N into stream.
// friend std::ostream& operator<<(std::ostream& stream, BigInteger N);

// operator==()
// Returns true if and only if A equals B.
// friend bool operator==(const BigInteger& A, const BigInteger& B);

// operator<()
// Returns true if and only if A is less than B.
// friend bool operator<(const BigInteger& A, const BigInteger& B);

// operator<=()
// Returns true if and only if A is less than or equal to B.
// friend bool operator<=(const BigInteger& A, const BigInteger& B);

// operator>()
// Returns true if and only if A is greater than B.
// friend bool operator>(const BigInteger& A, const BigInteger& B);

// operator>=()
// Returns true if and only if A is greater than or equal to B.
// friend bool operator>=(const BigInteger& A, const BigInteger& B);

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
