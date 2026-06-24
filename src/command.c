#include "command.h"

#include "commands/index.h"

#include <concord/discord.h>

#include <string.h>

void deploy_commands(struct discord *client, u64snowflake application_id, u64snowflake guild_id) {
  for (int i = 0; i < sizeof(g_commands) / sizeof(struct discord_create_guild_application_command); i++) {
    discord_create_guild_application_command(client, application_id, guild_id, &g_commands[i], NULL);
  }
}

void on_interaction(struct discord *client, const struct discord_interaction *event) {
  if (event->type != DISCORD_INTERACTION_APPLICATION_COMMAND) {
    return;
  }

  for (int i = 0; i < sizeof(g_commands_list) / sizeof(Command); i++) {
    if (strcmp(event->data->name, g_commands_list[i].name) != 0) {
      continue;
    }
    g_commands_list[i].run(client, event);
    return;
  }
}