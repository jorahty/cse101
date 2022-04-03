// James Tennant • jtennant • pa1

#include <stdio.h>
#include "List.h"

int main(int argc, char *argv[]) {

    // 1. Check that there are two command-line arguments
    if (argc != 3) {
        fprintf(stderr,
            "Error: more or less than two "
            "command-line arguments were given.\n"
        );
    }
    
    return 0;
}
