#ifndef DATABASE_INIT_H
#define DATABASE_INIT_H

#include "helper.h"

static const char *g_database_init_stmt = MK_STMT(
CREATE TABLE IF NOT EXISTS guild_config (
                                         guild_id TEXT PRIMARY KEY,
                                         message_channel TEXT,
                                         member_channel TEXT,
                                         join_leave_channel TEXT,
                                         media_channel TEXT,
                                         mod_channel TEXT
) STRICT ;
CREATE TABLE IF NOT EXISTS member_data (
                                        member_id TEXT PRIMARY KEY,
                                        message_count INTEGER NOT NULL DEFAULT 0
) STRICT;
CREATE TABLE IF NOT EXISTS autorole_config (
                                            guild_id TEXT PRIMARY KEY,
                                            role_id TEXT,
                                            messages_needed INTEGER NOT NULL DEFAULT 0
) STRICT;
CREATE TABLE IF NOT EXISTS guild_rules (
    guild_id TEXT PRIMARY KEY,
    rules TEXT,
    channel TEXT
) STRICT;
CREATE TABLE IF NOT EXISTS warnings (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    guild_id TEXT NOT NULL,
    user_id TEXT NOT NULL,
    rule_number INTEGER NOT NULL,
    note TEXT,
    timestamp INTEGER NOT NULL
) STRICT;
CREATE TABLE IF NOT EXISTS cases (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    guild_id TEXT NOT NULL,
    user_id TEXT NOT NULL,
    case_type TEXT NOT NULL,
    rule_number INTEGER NOT NULL,
    note TEXT,
    timestamp INTEGER NOT NULL
) STRICT;
CREATE TABLE IF NOT EXISTS temp_bans (
    guild_id TEXT NOT NULL,
    user_id TEXT NOT NULL,
    unban_at INTEGER NOT NULL,
    PRIMARY KEY (guild_id, user_id)
) STRICT;
);

#endif // DATABASE_INIT_H
