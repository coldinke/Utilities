#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
  FILE *stream;
  char buffer[BUFFER_SIZE];

  for (size_t i = 1; i < argc; ++i) {
		  if ((stream = fopen(argv[i], "r")) == NULL) {
			fprintf(stdout, "wcat: cannot open file\n");
			exit(EXIT_FAILURE);
		  }

		  while ((fgets(buffer, BUFFER_SIZE, stream)) != NULL) {
			fprintf(stdout, "%s", buffer);
		  }
		  
		  errno = 0;
		  if (fclose(stream) != 0) {
		  	strerror(errno);
			exit(EXIT_FAILURE);
			}
	}

	fclose(stream);

	return 0;
}
