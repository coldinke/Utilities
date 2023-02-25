#include <stdio.h>
#include <stdlib.h>
#include <string.h>


FILE* Fopen(char* filename, char* mode) {
    FILE* file = fopen(filename, mode);
    if (file == NULL) {
        printf("wunzip: cannot open file\n");
        exit(EXIT_FAILURE);
    }
    return file;
}


int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("wunzip: file1 [file2 ...]\n");
        exit(EXIT_FAILURE);
    }

    FILE* file;
    int occur = 0;
    char sets;

    for (int i = 1; i < argc; ++i) {
        file = Fopen(argv[i], "r");

        while(fread(&occur, 4, 1, file) > 0) {
            
            // memset(sets, 0, strlen(sets));
            fread( &sets, 1, 1, file);
            while (occur >= 1) {
                fwrite(&sets, 1, 1, stdout);
                // printf("%c", sets);
                occur --;
            }
        }
        fclose(file);   
    }

    return 0;
}