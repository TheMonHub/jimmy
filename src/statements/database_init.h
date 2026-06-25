#ifndef DATABASE_INIT_H
#define DATABASE_INIT_H

#include "helper.h"

static const char *g_database_init_stmt = MK_STMT(
PRAGMA journal_mode = WAL;
PRAGMA synchronous = NORMAL;
PRAGMA cache_size = -200000;

PRAGMA user_version = 1;

CREATE TABLE IF NOT EXISTS guild_dat (
  gid INTEGER PRIMARY KEY,
  ccid INTEGER NOT NULL,
  crid INTEGER NOT NULL
) STRICT;

CREATE TABLE IF NOT EXISTS rules (
  rid INTEGER PRIMARY KEY,
  indx INTEGER,
  title TEXT NOT NULL,
  desc TEXT NOT NULL,
  color TEXT NOT NULL,
  img TEXT NOT NULL
) STRICT;

CREATE TABLE IF NOT EXISTS log_conf (
  gid INTEGER PRIMARY KEY,
  message INTEGER,
  member INTEGER,
  welcome INTEGER,
  media INTEGER,
  mod INTEGER
) STRICT;

CREATE TABLE IF NOT EXISTS cases (
  id INTEGER NOT NULL,
  gid INTEGER NOT NULL,
  uid INTEGER NOT NULL,
  type INTEGER NOT NULL,
  rid INTEGER NOT NULL,
  note TEXT,
  time INTEGER NOT NULL,
  PRIMARY KEY (gid, uid)
) STRICT;

CREATE TABLE IF NOT EXISTS tbans (
  gid INTEGER NOT NULL,
  uid INTEGER NOT NULL,
  expire INTEGER NOT NULL,
  PRIMARY KEY (gid, uid)
) STRICT;
);

#endif // DATABASE_INIT_H
