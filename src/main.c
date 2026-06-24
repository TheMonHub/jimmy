#include "main.h"

#include "command.h"
#include "database.h"

#include <stdio.h>

#include <concord/discord.h>
#include <concord/logmod.h>

#include "token.h"

#include <pthread.h>
#include <string.h>

#include <termios.h>
#include <unistd.h>

#define OK printf("%s\n", "OK!")

static const char *g_project_version = PROJECT_VERSION;

static pthread_mutex_t g_mutex_ready = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t g_cond_ready = PTHREAD_COND_INITIALIZER;
static u64snowflake g_appid = 0;

static void on_ready(struct discord *client, const struct discord_ready *event) {
  pthread_mutex_lock(&g_mutex_ready);
  g_appid = event->application->id;
  pthread_cond_signal(&g_cond_ready);
  pthread_mutex_unlock(&g_mutex_ready);
  printf("%s\n", "Discord bot is ready!");
  printf("Application ID: %lu\n", g_appid);
}

static void on_guild_create(struct discord* client, const struct discord_guild* event) {
  pthread_mutex_lock(&g_mutex_ready);

  while (g_appid == 0) {
    pthread_cond_wait(&g_cond_ready, &g_mutex_ready);
  }

  pthread_mutex_unlock(&g_mutex_ready);

  deploy_commands(client, g_appid, event->id);
}

int main(const int argc, char *argv[]) {
  printf("  jimmy - %s\n", g_project_version);
  printf("%s\n", "  Made by TheMonHub");
  printf("%s\n", "  Licensed Under Apache-2.0");

  printf("%s\n", " !!! THIS IS AN INDEV BUILD\n !!! SOME FUNCTIONALITY ARE\n !!! NOT FINISHED AND MUST\n !!! NOT BE USED");

  printf("%s\n", "=============================");

  printf("%s\n", "Press ENTER to continue...");

  getchar();

  char token[TOKEN_MAX_SIZE];

  if (argc > 1 && strncmp(argv[1], "migrate", 7) == 0) {
    printf("%s\n", "Migrating database...");
    return database_migrate(argc, argv);
  }

  printf("%s\n", "Reading token from a file...");
  int read_status = read_token(argc, argv, token, sizeof(token));
  if (read_status != 0) {
    fprintf(stderr, "%s", "FATAL: failed to read token from a file!\n");
    return read_status;
  }
  OK;

  printf("%s\n", "Reading database...");
  int database_status = database_init(argc, argv);
  if (database_status != 0) {
    fprintf(stderr, "%s", "ERROR: failed to initialize database!\n");
    return database_status;
  }
  OK;

  printf("%s\n", "Initializing a discord bot...");

  const struct discord_config CONFIG = {
    .token = token,
    .log = {
      .level = LOGMOD_LEVEL_INFO,
      .quiet = false,
      .color = true
    }
  };

  struct discord *client = discord_from_config(&CONFIG);
  if (client == NULL) {
    fprintf(stderr, "%s", "FATAL: failed to initialize a discord bot!\n");
    database_fini();
    discord_cleanup(client);
    return 2;
  }
  OK;

  printf("%s\n", "Setting callback functions...");
  discord_set_on_ready(client, &on_ready);
  discord_set_on_interaction_create(client, &on_interaction);
  discord_set_on_guild_create(client, &on_guild_create);


  printf("%s\n", "Running a discord bot...");

  CCORDcode discord_status = CCORD_OK;

  discord_status = discord_run(client);
  if (discord_status != CCORD_OK) {
    fprintf(stderr, "%s", "ERROR: An error occurred during discord run!\n");
  }

  printf("%s\n", "The discord bot has been stopped!\nCleaning up...");

  database_fini();
  discord_cleanup(client);
  OK;
  return discord_status;
}
