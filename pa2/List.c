// James Tennant • jtennant • pa1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

// ██ Private Types ██

// Define private Node type
typedef struct NodeObj* Node;

// Define private NodeObj type
typedef struct NodeObj {
   int data;
   Node next;
   Node prev;
} NodeObj;

// Define private ListObj type
typedef struct ListObj {
   Node front;
   Node back;
   Node cursor;
   int index;
   int length;
} ListObj;

// ██ Constructors & Destructors ██

// Creates a Node
Node newNode(int data){
   Node N = calloc(1, sizeof(NodeObj));
   N->data = data;
   return N;
}

// Deletes a Node
void freeNode(Node* pN){
   if (pN && *pN){
      free(*pN);
      *pN = NULL;
   }
}

// Creates and returns a new empty List
List newList() {
   // Most fields (front, back, cursor, length) are NULL (i.e. 0)
   List L = calloc(1, sizeof(ListObj));
   L->index = -1; // index is undefined
   return L;
}

// Frees all heap memory associated with *pL, and sets *pL to NULL
void freeList(List* pL) {
   if (pL && *pL) {
      while (length(*pL) > 0) {
         deleteFront(*pL);
      }
      free(*pL);
      *pL = NULL;
   }
}

// ██ Access Functions ██

// Returns the number of elements in L
int length(List L) {
   if (L == NULL) {
      printf("List Error: calling length() on NULL List reference\n");
      exit(1);
   }
   return L->length;
}

// Returns index of cursor element if defined, -1 otherwise
int index(List L) {
   if (L == NULL) {
      printf("List Error: calling index() on NULL List reference\n");
      exit(1);
   }
   return L->index;
}

// Returns front element of L. Pre: length() > 0
int front(List L) {
   if (L == NULL) {
      printf("List Error: calling front() on NULL List reference\n");
      exit(1);
   }
   if (length(L) < 1) {
      printf("List Error: calling front() on an empty List\n");
      freeList(&L);
      exit(1);
   }
   return L->front->data;
}

// Returns back element of L. Pre: length() > 0
int back(List L) {
   if (L == NULL) {
      printf("List Error: calling back() on NULL List reference\n");
      exit(1);
   }
   if (length(L) < 1) {
      printf("List Error: calling back() on an empty List\n");
      freeList(&L);
      exit(1);
   }
   return L->back->data;
}

// Returns cursor element of L. Pre: length() > 0, index() >= 0
int get(List L) {
   if (L == NULL) {
      printf("List Error: calling get() on NULL List reference\n");
      exit(1);
   }
   if (length(L) < 1) {
      printf("List Error: calling get() on an empty List\n");
      freeList(&L);
      exit(1);
   }
   if (index(L) < 0) {
      printf("List Error: calling get() on List with undefined index\n");
      freeList(&L);
      exit(1);
   }
   return L->cursor->data;
}

// Returns true iff A & B are in same state, false otherwise
bool equals(List A, List B) {
   if (A == NULL || B == NULL) {
      printf("List Error: calling equals() on NULL List reference\n");
      exit(1);
   }

   bool eq = false;
   Node N = NULL;
   Node M = NULL;

   eq = (A->length == B->length);
   N = A->front;
   M = B->front;
   while (eq && N != NULL) {
      eq = (N->data == M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}

// ██ Manipulation Procedures ██

// Resets L to its original empty state.
void clear(List L) {
   if (L == NULL) {
      printf("List Error: calling clear() on NULL List reference\n");
      exit(1);
   }
   while (length(L) > 0) {
      deleteFront(L);
   }
   L->front = L->back = L->cursor = NULL;
   L->index = -1;
   L->length = 0;
}

// Overwrites the cursor element’s data with x. Pre: length() > 0, index() >= 0
void set(List L, int x) {
   if (L == NULL) {
      printf("List Error: calling set() on NULL List reference\n");
      exit(1);
   }
   if (length(L) < 1) {
      printf("List Error: calling set() on empty List\n");
      freeList(&L);
      exit(1);
   }
   if (index(L) < 0) {
      printf("List Error: calling set() on List with undefined index\n");
      freeList(&L);
      exit(1);
   }
   L->cursor->data = x;
}

// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L) {
   if (L == NULL) {
      printf("List Error: calling moveFront() on NULL List reference\n");
      exit(1);
   }
   if (length(L) > 0) {
      L->cursor = L->front;
      L->index = 0;
   }
}

// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L) {
   if (L == NULL) {
      printf("List Error: calling moveBack() on NULL List reference\n");
      exit(1);
   }
   if (length(L) > 0) {
      L->cursor = L->back;
      L->index = length(L) - 1;
   }
}

// If cursor is defined and not at front,
// move cursor one step toward the front of L;
// if cursor is defined and at front, cursor becomes undefined;
// if cursor is undefined do nothing
void movePrev(List L) {
   if (L == NULL) {
      printf("List Error: calling movePrev() on NULL List reference\n");
      exit(1);
   }
   if (L->cursor == NULL) { return; } // cursor undefined
   if (L->cursor == L->front) { // cursor defined and at front
      L->cursor = NULL;
      L->index = -1;
      return;
   } // cursor defined and not at front
   L->cursor = L->cursor->prev;
   L->index--;
}

// If cursor is defined and not at back,
// move cursor one step toward the back of L;
// if cursor is defined and at back, cursor becomes undefined;
// if cursor is undefined do nothing
void moveNext(List L) {
   if (L == NULL) {
      printf("List Error: calling moveNext() on NULL List reference\n");
      exit(1);
   }
   if (L->cursor == NULL) { return; } // cursor undefined
   if (L->cursor == L->back) { // cursor defined and at back
      L->cursor = NULL;
      L->index = -1;
      return;
   } // cursor defined and not at back
   L->cursor = L->cursor->next;
   L->index++;
}

// Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, int x) {
   if (L == NULL) {
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(1);
   }

   Node N = newNode(x); // Create new Node with data x

   if (length(L) == 0) {
      L->front = L->back = N; // List is empty
   } else { 
      // Hook up the Nodes
      L->front->prev = N;
      N->next = L->front;

      L->front = N; // Update the front

      if (L->index > -1) { 
         L->index++; // Update index if defined
      }
   }
   L->length++;
}

// Insert new element into L. If L is non-empty, insertion takes place after back element.
void append(List L, int x) {
   if (L == NULL) {
      printf("List Error: calling append() on NULL List reference\n");
      exit(1);
   }

   Node N = newNode(x); // Create new Node with data x

   if (length(L) == 0) {
      L->front = L->back = N; // List is empty
   } else {
      // Hook up the Nodes
      L->back->next = N;
      N->prev = L->back;

      L->back = N; // Update the back
   }
   L->length++;
}

// Insert new element before cursor. Pre: length() > 0, index() >= 0
void insertBefore(List L, int x) {
   if (L == NULL) {
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(1);
   }
   if (length(L) < 1) {
      printf("List Error: calling insertBefore() on empty List\n");
      freeList(&L);
      exit(1);
   }
   if (index(L) < 0) {
      printf("List Error: calling insertBefore() on List with undefined index\n");
      freeList(&L);
      exit(1);
   }

   Node N = newNode(x); // Create new Node with data x

   // Hook up the new Node
   N->prev = L->cursor->prev;
   N->next = L->cursor;

   // Hook up the surrounding Nodes
   if (L->cursor == L->front) { // If cursor in front
      L->front = N; // N is the new front
   } else {
      L->cursor->prev->next = N; // Link prev to N
   }
   L->cursor->prev = N; // Link cursor to N

   L->index++;
   L->length++;
}

// Insert new element after cursor. Pre: length() > 0, index() >= 0
void insertAfter(List L, int x) {
   if (L == NULL) {
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(1);
   }
   if (length(L) < 1) {
      printf("List Error: calling insertAfter() on empty List\n");
      freeList(&L);
      exit(1);
   }
   if (index(L) < 0) {
      printf("List Error: calling insertAfter() on List with undefined index\n");
      freeList(&L);
      exit(1);
   }

   Node N = newNode(x); // Create new Node with data x

   // Hook up the new Node
   N->next = L->cursor->next;
   N->prev = L->cursor;

   // Hook up the surrounding Nodes
   if (L->cursor == L->back) { // If cursor in back
      L->back = N; // N is the new back
   } else {
      L->cursor->next->prev = N; // Link next to N
   }
   L->cursor->next = N; // Link cursor to N

   L->length++;
}

// Deletes the front element. Pre: length() > 0
void deleteFront(List L) {
   if (L == NULL) {
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(1);
   }
   if (length(L) < 1) {
      printf("List Error: calling deleteFront() on an empty List\n");
      freeList(&L);
      exit(1);
   }

   // If cursor in front, undefine cursor element
   if (L->cursor == L->front) {
      L->cursor = NULL;
      L->index = -1;
   }

   // Save front before updating to new front
   // so original front can be deleted after
   Node N = L->front;

   if (length(L) > 1) { // Multiple elements
      L->front->next->prev = NULL; // Unhook second element
      L->front = L->front->next; // Update front
      if (index(L) > 0) {
         L->index--; // Decrement index if defined (& not in front)
      }
   } else {
      // Only one element so front & back become NULL
      L->front = L->back = NULL;
   }
   L->length--;
   freeNode(&N);
}

// Delete the back element. Pre: length() > 0
void deleteBack(List L) {
   if (L == NULL) {
      printf("List Error: calling deleteBack() on NULL List reference\n");
      exit(1);
   }
   if (length(L) < 1) {
      printf("List Error: calling deleteBack() on an empty List\n");
      freeList(&L);
      exit(1);
   }

   // If cursor in back, undefine cursor element
   if (L->cursor == L->back) {
      L->cursor = NULL;
      L->index = -1;
   }

   // Save back before updating to new back
   // so original back can be deleted after
   Node N = L->back;

   if (length(L) > 1) { // Multiple elements
      L->back->prev->next = NULL; // Unhook second-to-last element
      L->back = L->back->prev; // Update back
   } else {
      // Only one element so front & back become NULL
      L->front = L->back = NULL;
   }
   L->length--;
   freeNode(&N);
}

// Deletes cursor element, making cursor undefined. Pre: length() > 0, index() >= 0
void delete(List L) {
   if (L == NULL) {
      printf("List Error: calling delete() on NULL List reference\n");
      exit(1);
   }
   if (length(L) < 1) {
      printf("List Error: calling delete() on an empty List\n");
      freeList(&L);
      exit(1);
   }
   if (index(L) < 0) {
      printf("List Error: calling delete() on List with undefined index\n");
      freeList(&L);
      exit(1);
   }

   // Adjust Node before cursor if it exists
   if (L->cursor->prev != NULL) {
      L->cursor->prev->next = L->cursor->next;
   } else {
      L->front = L->cursor->next; // Cursor at front so update front
   }

   // Adjust Node after cursor if it exists
   if (L->cursor->next != NULL) {
      L->cursor->next->prev = L->cursor->prev;
   } else {
      L->back = L->cursor->prev; // Cursor at back so update back
   }

   freeNode(&(L->cursor));
   L->index = -1;
   L->length--;
}

// ██ Other Functions ██

// Prints to the file pointed to by out, a string representation of L
// consisting of a space-separated sequence of integers, with front on left.
void printList(FILE* out, List L) {
   if (L == NULL) {
      printf("List Error: calling printList() on NULL List reference\n");
      exit(1);
   }
	
   printf("%d", L->front->data);
   for (Node N = L->front->next; N != NULL; N = N->next) {
      printf(" %d", N->data);
   }
}

// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L) {
   if (L == NULL) {
      printf("List Error: calling copyList() on NULL List reference\n");
      exit(1);
   }

   List C = newList(); // Create new List

   for (Node N = L->front; N != NULL; N = N->next) {
      append(C, N->data); // Transfer integer sequence
   }

   return C;
}
