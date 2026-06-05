#include "ping.h"

#include <concord/discord.h>

static struct discord_interaction_response g_params = {
  .type = DISCORD_INTERACTION_CHANNEL_MESSAGE_WITH_SOURCE,
  .data = &(struct discord_interaction_callback_data){
    .content = "Pong!"
}
};

void ping(struct discord *client, const struct discord_interaction *event) {
  discord_create_interaction_response(client, event->id, event->token, &g_params, NULL);
}