#include "database.h"

#include <sqlite3.h>
#include <stdbool.h>
#include <stdio.h>

#include "statements/database_init.h"

static sqlite3 *g_database = NULL;

// static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
//   for (int i = 0; i<argc; i++) {
//     printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
//   }
//   printf("%s", "\n");
//   return 0;
// }

static int internal_database_init(int argc, char **argv, bool run_init) {
  char *path = "jimmy.db";
  if (argc > 2) {
    path = argv[2];
  }

  printf("Database path: %s\n", path);
  int status = sqlite3_open_v2(path, &g_database, SQLITE_OPEN_READWRITE |
                                                          SQLITE_OPEN_CREATE |
                                                          SQLITE_OPEN_FULLMUTEX, NULL);
  if (status != SQLITE_OK) {
    fprintf(stderr, "%s\n", sqlite3_errstr(status));
  }

  if (run_init == false) {
    return status;
  }

  status = sqlite3_exec(g_database, g_database_init_stmt, NULL, NULL, NULL);
  if (status != SQLITE_OK) {
    fprintf(stderr, "%s\n", sqlite3_errstr(status));
    database_fini();
  }
  return status;
}

int database_migrate(int argc, char **argv) {
  int status = internal_database_init(argc, argv, false);
  if (status != SQLITE_OK) {
    fprintf(stderr, "%s\n", sqlite3_errstr(status));
    return status;
  }

  database_fini();
  return status;
}

int database_init(int argc, char **argv) {
  return internal_database_init(argc, argv, true);
}

void database_fini() {
  int status = sqlite3_close_v2(g_database);
  if (status != SQLITE_OK) {
    fprintf(stderr, "%s\n", sqlite3_errstr(status));
  }
}

