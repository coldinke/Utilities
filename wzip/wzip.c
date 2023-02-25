#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    printf("wzip: file1 [file2 ...]\n");
    exit(EXIT_FAILURE);
  }

  FILE *file;
  char character[2] = "";
  char previous_character[2] = "";
  int char_occurrences = 0;

  for (int i=1; i < argc; i++) {
    if ((file = fopen(argv[i], "r")) == NULL) {
      perror("wzip: cannot open file");
      exit(EXIT_FAILURE);
    }

    while (fread(&character, 1, 1, file)) {
      if (strcmp(character, previous_character) == 0) {
        char_occurrences++;
      } else {
        if (previous_character[0] != '\0') {
          fwrite(&char_occurrences, 4, 1, stdout);
          fwrite(previous_character, 1, 1, stdout);
        }
        char_occurrences = 1;
        strcpy(previous_character, character);
      }
    }
    fclose(file);
  }

  // Deal with the last input.
  fwrite(&char_occurrences, 4, 1, stdout);
  fwrite(previous_character, 1, 1, stdout);
}