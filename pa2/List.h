// James Tennant • jtennant • pa2

#pragma once

#include <stdbool.h>
#include <stdio.h>

// ██ Public Types ██

typedef struct ListObj* List;

// ██ Constructors & Destructors ██

List newList(); // Creates and returns a new empty List
void freeList(List* pL); // Frees all heap memory associated with *pL, and sets *pL to NULL

// ██ Access Functions ██

int length(List L); // Returns the number of elements in L
int index(List L); // Returns index of cursor element if defined, -1 otherwise
int front(List L); // Returns front element of L. Pre: length() > 0
int back(List L); // Returns back element of L. Pre: length() > 0
int get(List L); // Returns cursor element of L. Pre: length() > 0, index() >= 0
bool equals(List A, List B); // Returns true iff A & B are in same state, false otherwise

// ██ Manipulation Procedures ██

void clear(List L); // Resets L to its original empty state.
void set(
    List L, int x); // Overwrites the cursor element’s data with x. Pre: length() > 0, index() >= 0
void moveFront(
    List L); // If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveBack(
    List L); // If L is non-empty, sets cursor under the back element, otherwise does nothing.

// If cursor is defined and not at front, move cursor one step toward the front of L;
// if cursor is defined and at front, cursor becomes undefined; if cursor is undefined do nothing
void movePrev(List L);

// If cursor is defined and not at back, move cursor one step toward the back of L;
// if cursor is defined and at back, cursor becomes undefined; if cursor is undefined do nothing
void moveNext(List L);

// Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, int x);

// Insert new element into L. If L is non-empty, insertion takes place after back element.
void append(List L, int x);

void insertBefore(
    List L, int x); // Insert new element before cursor. Pre: length() > 0, index() >= 0
void insertAfter(List L, int x); // Insert new element after cursor. Pre: length() > 0, index() >= 0
void deleteFront(List L); // Delete the front element. Pre: length() > 0
void deleteBack(List L); // Delete the back element. Pre: length() > 0
void delete (
    List L); // Delete cursor element, making cursor undefined. Pre: length() > 0, index() >= 0

// ██ Other Functions ██

// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L);

// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L);
