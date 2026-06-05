#ifndef COMMAND_H
#define COMMAND_H

#include <concord/discord.h>

void deploy_commands(struct discord *client, u64snowflake application_id, u64snowflake guild_id) ;
void on_interaction(struct discord *client, const struct discord_interaction *event);

#endif // COMMAND_H
