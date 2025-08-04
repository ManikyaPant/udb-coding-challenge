#include <stdio.h>
#include <stdlib.h> 

#define BUFFER_SIZE 4000

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <file1> <file2>\n", argv[0]);
        return 1; // Return an error code
    }

    const char *f1_path = argv[1];
    const char *f2_path = argv[2];

    FILE* F1 = fopen(f1_path, "rb");
    if (F1 == NULL) {
        perror("Error opening file1"); 
        return 1;
    }

    FILE* F2 = fopen(f2_path, "rb");
    if (F2 == NULL) {
        perror("Error opening file2");
        fclose(F1); 
        return 1;
    }

    
    char buf1[BUFFER_SIZE];
    char buf2[BUFFER_SIZE];
    size_t bytes_read1, bytes_read2;
    int files_are_same = 1; 

    // Loop until we reach the end of one of the files
    do {
        bytes_read1 = fread(buf1, 1, BUFFER_SIZE, F1);
        bytes_read2 = fread(buf2, 1, BUFFER_SIZE, F2);

        // 1. Check if the number of bytes read is different
        if (bytes_read1 != bytes_read2) {
            files_are_same = 0;
            break; 
        }

        
        for (size_t i = 0; i < bytes_read1; i++) {
            if (buf1[i] != buf2[i]) {
                files_are_same = 0;
                break; 
            }
        }
        
        if (!files_are_same) {
            break; 
        }

    } while (bytes_read1 > 0);

   
    fclose(F1);
    fclose(F2);

    if (files_are_same) {
        printf("Files are identical.\n");
    } else {
        printf("Files are different.\n");
    }

    return 0;
}