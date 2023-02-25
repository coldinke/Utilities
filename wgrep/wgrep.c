#include <stdio.h>  /* printf(), getline(), */
#include <assert.h> /* assert() */
#include <stdlib.h> /* exit() */
#include <string.h> /* strstr() */


FILE* Fopen(const char* filenmae, const char* mode) {
    FILE* file = fopen(filenmae, mode);
    if (file == NULL) {
        printf("wgrep: cannot open file\n");
        exit(1);
    }
    return file;
}

int Search(const char* searchterm, FILE* file) {
    char *buffer = NULL;
    size_t len;
    
    while (getline(&buffer, &len, file) > 0) {
        if (strstr(buffer, searchterm) != 0) {
            printf("%s", buffer);
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    } else if (argc == 2) {
        const char* searchterm = argv[1];
        char buffer[1024];

        while (fgets(buffer, 1023, stdin) != NULL) {
            if (strstr(buffer, searchterm) != 0) {
                printf("%s", buffer);
            }
        }
    } else {
        size_t index = 2;
        
        FILE* file;
        const char* searchterm = argv[1];
        
        while (index < argc) {
            file = Fopen(argv[index], "r");
            Search(searchterm, file);
            fclose(file);
            index++;
        }
    }
    return 0;
}