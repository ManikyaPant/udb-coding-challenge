#include <stdio.h>
#include "instructions.h" // The header file generated 
int main() {
    for (int i = 0; i < NUM_DATA_PAIRS; i++) {
                printf("%s: %s\n", data_pairs[i].key, data_pairs[i].value);
    }

    return 0;
}