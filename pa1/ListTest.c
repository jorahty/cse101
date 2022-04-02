// James Tennant • jtennant • pa1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include "List.h"

// Macros for colored output
#define GRN "\033[0;32m"
#define CLR "\033[0m"

// Uses all possible access functions
// to print details about a List L
void printDetails(List L) {
   printf(GRN "String: " CLR);
   printList(stdout, L);
   putchar('\n');
   printf(GRN "length():" CLR " %d\n", length(L));
   printf(GRN "index():" CLR " %d\n", index(L));
   if (length(L) > 0) {
      printf(GRN "front():" CLR " %d\n", front(L));
      printf(GRN "back():" CLR " %d\n", back(L));
      if (index(L) >= 0) {
         printf(GRN "get():" CLR " %d\n", get(L));
      }
   }
   putchar('\n');
}

int main(int argc, char* argv[]) {

   srand(time(NULL));

   // Run test from ListClient.c
   List A = newList(), B = newList(), C = NULL;
   for (int i = 1; i <= 20; i++) { append(A,i); prepend(B,i); }
   printList(stdout, A);
   printf("\n");
   printList(stdout, B);
   printf("\n");
   for (moveFront(A); index(A) >= 0; moveNext(A)) { printf("%d ", get(A)); }
   printf("\n");
   for (moveBack(B); index(B) >= 0; movePrev(B)) { printf("%d ", get(B)); }
   printf("\n");
   C = copyList(A);
   printf("%s\n", equals(A, B) ? "true" : "false");
   printf("%s\n", equals(B, C) ? "true" : "false");
   printf("%s\n", equals(C, A) ? "true" : "false");
   moveFront(A);
   for (int i = 0; i < 5; i++) moveNext(A); // at index 5
   insertBefore(A, -1);                     // at index 6
   for (int i = 0; i < 9; i++) moveNext(A); // at index 15
   insertAfter(A, -2);                      // at index 15
   for (int i = 0; i < 5; i++) movePrev(A); // at index 10
   delete(A);
   printList(stdout, A);
   printf("\n");
   printf("%d\n", length(A));
   clear(A);
   printf("%d\n", length(A));
   freeList(&A);
   freeList(&B);
   freeList(&C);
   printf("\n");

   // newList()
   List L = newList();
   printDetails(L);

   // clear()
   clear(L);
   printDetails(L);
   for (int i = 1; i <= 5 + rand() % 15; i++) { append(L, rand() % 100 ); }
   printDetails(L);
   clear(L);
   printDetails(L);

   // moveBack() movePrev() set() deleteBack()
   for (int i = 1; i <= 5 + rand() % 15; i++) { append(L, rand() % 100 ); }
   printDetails(L);
   moveBack(L);
   movePrev(L);
   set(L, 21);
   printDetails(L);
   deleteBack(L);
   printDetails(L);

   // freeList()
   freeList(&L);
   assert(L == NULL);

   printf(GRN "Success!\n\n" CLR);
   
   return 0;
}
