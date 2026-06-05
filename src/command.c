#include "command.h"

#include "commands/index.h"

#include <concord/discord.h>

#include <stdio.h>

#include <string.h>

void deploy_commands(struct discord *client, u64snowflake application_id, u64snowflake guild_id) {
  printf("Creating guild application command for guild id: %lu\n", guild_id);
  CCORDcode status = discord_create_guild_application_command(client, application_id, guild_id, &g_commands, NULL);
  if (status != CCORD_OK) {
    fprintf(stderr, "%s", "ERROR: failed to create a new guild application command!\n");
    return;
  }
  printf("%s\n", "OK!");
}

void on_interaction(struct discord *client, const struct discord_interaction *event) {
  if (event->type != DISCORD_INTERACTION_APPLICATION_COMMAND) {
    return;
  }

  for (int i = 0; i < g_commands_tab.size; i++) {
    if (strcmp(event->data->name, g_commands_tab.commands[i].name) == 0) {
      g_commands_tab.commands[i].run(client, event);
      return;
    }
  }
}