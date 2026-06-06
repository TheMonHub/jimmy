#ifndef INDEX_H
#define INDEX_H

#include <concord/discord.h>

typedef void (*cmd_fn)(struct discord *client, const struct discord_interaction *event);

typedef struct {
  const char *name;
  cmd_fn run;
} Command;

extern Command g_commands_list[2];

extern struct discord_create_guild_application_command g_commands[2];

#endif // INDEX_H
