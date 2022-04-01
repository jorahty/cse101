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
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
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
   // Most fields (front, back, cursor, length) are NULL (or 0)
   List L = calloc(1, sizeof(ListObj));
   L->index = -1; // index is undefined
   return L;
}

// Frees all heap memory associated with *pL, and sets *pL to NULL
void freeList(List* pL) {
   if (pL && *pL) {
      while (length(*pL)) {
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

// Insert new element into L. If L is non-empty, insertion takes place after back element.
void append(List L, int x) {
   if (L == NULL) {
      printf("List Error: calling append() on NULL List reference\n");
      exit(1);
   }

   Node N = newNode(x);

   if (length(L) == 0) { 
      L->front = L->back = N; 
   } else { 
      L->back->next = N; 
      L->back = N; 
   }
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

   // If cursor in front, undefine cursor
   if (L->cursor == L->front) {
      delete(L);
   }

   // Save front before updating to new front
   // so original front can be deleted after
   Node N = L->front; 
   if (length(L) > 1) {
      L->front = L->front->next;
   } else {
      L->front = L->back = NULL; // Only one node
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
   L->cursor = NULL;
   L->index = -1;
}

// ██ Other Functions ██

// Prints to the file pointed to by out, a string representation of L
// consisting of a space-separated sequence of integers, with front on left.
void printList(FILE* out, List L) {
   if (L == NULL) {
      printf("List Error: calling printList() on NULL List reference\n");
      exit(1);
   }

   for (Node N = L->front; N != NULL; N = N->next) {
      printf("%d ", N->data);
   }
}
