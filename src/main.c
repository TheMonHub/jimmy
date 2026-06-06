#include "main.h"

#include "command.h"
#include "database.h"

#include <stdio.h>

#include <concord/discord.h>
#include <concord/logmod.h>

#include "token.h"

#include <assert.h>
#include <signal.h>

static volatile sig_atomic_t g_closing = 0;

static struct discord *g_current_client = NULL;
static const char *g_project_version = PROJECT_VERSION;

static u64snowflake g_appid = 0;

static void on_ready(struct discord *client, const struct discord_ready *event) {
  g_appid = event->application->id;
  printf("%s\n", "Discord bot is ready!");
  printf("Application ID: %lu\n", g_appid);
}

static void on_guild_create(struct discord* client, const struct discord_guild* event) {
  deploy_commands(client, g_appid, event->id);
}

void on_shutdown(int sig)
{
  if (g_closing == 1) {
    return;
  }
  g_closing = 1;
  printf("%s\n", "Shutting down...");
  discord_shutdown(g_current_client);
}

int main(const int argc, char *argv[]) {
  printf("  jimmy - %s\n", g_project_version);
  printf("%s\n", "  Made by TheMonHub");
  printf("%s\n", "  Licensed Under Apache-2.0");
  printf("%s\n", "=============================");

  signal(SIGINT, on_shutdown);
  signal(SIGTERM, on_shutdown);

  char token[TOKEN_MAX_SIZE];

  printf("%s\n", "Reading token from a file...");
  int read_status = read_token(argc, argv, token, sizeof(token));
  if (read_status != 0) {
    fprintf(stderr, "%s", "FATAL: failed to read token from a file!\n");
    return read_status;
  }
  printf("%s\n", "OK!");

  printf("%s\n", "Reading database...");
  int database_status = database_init(argc, argv);
  if (database_status != 0) {
    fprintf(stderr, "%s", "ERROR: failed to initialize database!\n");
    return database_status;
  }
  printf("%s\n", "OK!");

  printf("%s\n", "Initializing a discord bot...");
  ccord_global_init();
  struct discord *client = discord_init(token);
  if (client == NULL) {
    fprintf(stderr, "%s", "FATAL: failed to initialize a discord bot!\n");
    return 2;
  }
  printf("%s\n", "OK!");

  printf("%s\n", "Setting log level to warn...");
  struct logmod *logmod = discord_get_logmod(client);
  for (int i = 0; i < logmod->length; ++i) {
    logmod_logger_set_level((struct logmod_logger*) &logmod->loggers[i], LOGMOD_LEVEL_WARN);
  }
  printf("%s\n", "OK!");

  discord_set_on_ready(client, &on_ready);
  discord_set_on_interaction_create(client, &on_interaction);
  discord_set_on_guild_create(client, &on_guild_create);

  printf("%s\n", "Running a discord bot...");
  g_current_client = client;
  CCORDcode discord_status = discord_run(client);
  if (discord_status != CCORD_OK) {
    fprintf(stderr, "%s", "ERROR: An error occurred during discord run!\n");
  }
  printf("%s\n", "The discord bot has been stopped!\nCleaning up...");

  database_fini();
  discord_cleanup(client);
  ccord_global_cleanup();
  printf("%s\n", "Done!");
  return discord_status;
}
