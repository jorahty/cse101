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

// ██ Manipulation Procedures ██

// Deletes the front element. Pre: length() > 0
void deleteFront(List L) {
   if (L == NULL) {
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(1);
   }
   if (length(L) < 1) {
      printf("List Error: calling deleteFront on an empty List\n");
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
   printf("\n");
}
