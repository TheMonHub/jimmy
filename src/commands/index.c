#include "index.h"

#include "ping.h"

#include <concord/discord.h>

CommandTable g_commands_tab = {
  .size = 1,
  .commands = {
        {
          .name = "ping",
          .run = ping
        },
  }
};

struct discord_create_guild_application_command g_commands = {
  .name = "ping",
  .description = "Pong!"
};