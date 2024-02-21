#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char ** argv) { 
    if (argc != 2) {
        fprintf(stderr, "Usage: %s inputFileName\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    FILE * f = fopen(argv[1], "r");
    if (f == NULL) {    
        perror("Could not open file");    
        return EXIT_FAILURE;  
    }  

    int array[26] = {0}; 
    int c;    
    while ((c = fgetc(f)) != EOF) {        
        if (isalpha(c)) {
            c = tolower(c);            
            array[c - 'a']++; 
        }
    }

    int maxIndex = 0;
    for (int j = 1; j < 26; j++) {
        if (array[j] > array[maxIndex]) {
            maxIndex = j; 
        }
    }

    int key = (maxIndex + 26 - ('e' - 'a')) % 26;

    printf("%d\n", key);

    if (fclose(f) != 0) {    
        perror("Failed to close the input file!");    
        return EXIT_FAILURE;  
    }  

    return EXIT_SUCCESS; 
}   
