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
   // All fields (front, back, cursor, index, length) are NULL (i.e. 0)
   return calloc(1, sizeof(ListObj));
}

// Frees all heap memory associated with *pL, and sets *pL to NULL
void freeList(List* pL) {
   if (pL && *pL) {
      while (length(*pL)) {
         // deleteFront(*pL);
      }
      free(*pL);
      *pL = NULL;
   }
}

// ██ Access Functions ██

// Returns the number of elements in L
int length(List L) {
   return(L->length);
}

// ██ Manipulation Procedures ██

// Delete the front element. Pre: length()>0
void deleteFront(List L) {

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
