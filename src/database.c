#include "database.h"

#include <sqlite3.h>
#include <stdio.h>

static sqlite3 *g_database = NULL;

int database_init(int argc, char **argv) {
  int status;
  if (argc <= 2) {
    printf("Database path: %s\n", "jimmy.db");
    status = sqlite3_open_v2("jimmy.db", &g_database, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    if (status != SQLITE_OK) {
      fprintf(stderr, "%s\n", sqlite3_errstr(status));
    }
    return status;
  }

  printf("Database path: %s\n", argv[2]);
  status = sqlite3_open_v2(argv[2], &g_database, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
  if (status != SQLITE_OK) {
    fprintf(stderr, "%s\n", sqlite3_errstr(status));
  }
  return status;
}

void database_fini() {
  int status = sqlite3_close_v2(g_database);
  if (status != SQLITE_OK) {
    fprintf(stderr, "%s\n", sqlite3_errstr(status));
  }
}