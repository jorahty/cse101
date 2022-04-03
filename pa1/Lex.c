// James Tennant • jtennant • pa1

#include <stdio.h>
#include "List.h"

#define KB 1024

int main(int argc, char *argv[]) {

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

    rewind(in);

    fclose(in);
    fclose(out);
    
    return 0;
}
