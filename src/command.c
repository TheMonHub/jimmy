#include "command.h"

#include "commands/index.h"

#include <concord/discord.h>

#include <stdio.h>

#include <string.h>

void deploy_commands(struct discord *client, u64snowflake application_id, u64snowflake guild_id) {
  printf("Creating guild application command for guild id: %lu\n", guild_id);
  for (int i = 0; i < sizeof(g_commands) / sizeof(struct discord_create_guild_application_command); i++) {
    CCORDcode status = discord_create_guild_application_command(client, application_id, guild_id, &g_commands[i], NULL);
    if (status == CCORD_PENDING || status == CCORD_OK) {
      printf("Commands: %s\n", g_commands[i].name);
      printf("%s\n", discord_strerror(status, client));
      printf("%s\n", "OK!");
      continue;
    }
    fprintf(stderr, "ERROR: failed to create a new guild application command '%s'!\n", g_commands[i].name);
    fprintf(stderr, "%s\n", discord_strerror(status, client));
  }
}

void on_interaction(struct discord *client, const struct discord_interaction *event) {
  if (event->type != DISCORD_INTERACTION_APPLICATION_COMMAND) {
    return;
  }

  for (int i = 0; i < sizeof(g_commands_list) / sizeof(Command); i++) {
    if (strcmp(event->data->name, g_commands_list[i].name) == 0) {
      g_commands_list[i].run(client, event);
      return;
    }
  }
}