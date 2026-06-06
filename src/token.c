#include "token.h"

#include "main.h"

#include <linux/limits.h>
#include <stdio.h>
#include <string.h>

#include <stdlib.h>

static int parse_file(char* config_path, char *token, size_t token_size) {
  printf("Token path: %s\n", config_path);

  FILE *config_file = fopen(config_path, "r");

  if (config_file == NULL) {
    perror("Cannot open token file");
    return -1;
  }

  int status = fseek(config_file, 0L, SEEK_END);
  if (status == -1) {
    perror("Error seeking to end of file");
    goto error;
  }
  size_t file_size = ftell(config_file);
  if (file_size == -1L) {
    perror("Error retrieving file size");
    goto error;
  }
  status = fseek(config_file, 0L, SEEK_SET);
  if (status == -1) {
    perror("Error seeking to start of file");
    goto error;
  }
  if (file_size > TOKEN_MAX_SIZE) {
    fprintf(stderr, "%s\n", "Token file size is too big!");
    goto error;
  }

  char *read_status = fgets(token, token_size, config_file);
  if (read_status == NULL) {
    perror("Cannot read token file");
    goto error;
  }

  token[strcspn(token, "\r\n")] = 0;

  fclose(config_file);
  return 0;

  error:
  fclose(config_file);
  return -1;
}

int read_token(int argc, char **argv, char *token, size_t token_size) {
  if (argc <= 1) {
    return parse_file("jimmy.txt", token, token_size);
  }

  char config_path[PATH_MAX];
  strncpy(config_path, argv[1], sizeof(config_path));
  return parse_file(config_path, token, token_size);
}