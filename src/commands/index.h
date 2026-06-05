#ifndef INDEX_H
#define INDEX_H

#include <concord/discord.h>

typedef void (*cmd_fn)(struct discord *client, const struct discord_interaction *event);

typedef struct {
  const char *name;
  cmd_fn run;
} Command;

typedef struct {
  size_t size;
  Command commands[];
} CommandTable;

extern CommandTable g_commands_tab;

extern struct discord_create_guild_application_command g_commands;

#endif // INDEX_H
