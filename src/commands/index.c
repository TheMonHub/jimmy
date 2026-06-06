#include "index.h"

#include "about.h"
#include "ping.h"

#include <concord/discord.h>

Command g_commands_list[] = {
  {
    .name = "ping",
    .run = ping
  },
  {
    .name = "about",
    .run = about
  }
};

struct discord_create_guild_application_command g_commands[] = {
  {
    .name = "ping",
    .description = "Pong!"
  },
  {
    .name = "about",
    .description = "About this bot."
  }
};