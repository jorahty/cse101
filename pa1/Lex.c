// James Tennant • jtennant • pa1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define KB 1024

int main(int argc, char* argv[]) {

    // Check for correct number of arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        return 1;
    }

    // Open input file for reading
    FILE *in = fopen(argv[1], "r");
    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        return 1;
    }

    // Open output file for reading
    FILE *out = fopen(argv[2], "w");
    if (out == NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        return 1;
    }

    // Count the number of lines n in the input file
    int n = 0;
    char line[KB];
    while (fgets(line, KB, in) != NULL) { n++; }


    // Allocate heap memory for array of strings
    char** strings = calloc(n, sizeof(char*));

    rewind(in); // Go back to start of input file

    for (int i = 0; i < n; i++) { // Read all n lines again

        // Read each line from input file
        // and store it in line buffer
        fgets(line, KB, in);

        // Allocate minimum heap memory for string
        strings[i] = calloc(strlen(line), sizeof(char)); 

        // Copy string from line buffer to array
        strcpy(strings[i], line);

        // Remove newline
        // strings[i][strlen(strings[i]) - 1] = '\0';
        // strings[i] = strtok(strings[i], "\n");
    }

    // Create List of indices that indirectly sorts array
    List L = newList();
    append(L, 0);
    for (int i = 1; i < n; i++) { // For every index i in (0, n)

        // Scan for a place to insert i
        for (moveFront(L); 1; moveNext(L)) {

            // Have we reached the end of the List?
            if (index(L) == -1) {
                append(L, i);
                break;
            }

            // Does this index i belong before the cursor element?
            if (strcmp(strings[i], strings[get(L)]) < 0) {
                insertBefore(L, i);
                break;
            }
        }
    }

    // Free the array of strings
    for (int i = 0; i < n; i++) { free(strings[i]); }
    free(strings);

    // Close files
    fclose(in);
    fclose(out);
    
    return 0;
}
