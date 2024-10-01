#ifndef BRICKGAME_DESKTOP_SRC_GUI_CLI_RETRIEVE_DATA_H_
#define BRICKGAME_DESKTOP_SRC_GUI_CLI_RETRIEVE_DATA_H_

#define SERVER "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 4096

#include "../cjson/cjson.h"
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include "../parameters/parameters.h"

struct MemoryStruct {
  char *memory;
  size_t size;
};
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb,
                                  void *userp);

static size_t IgnoreResponseCallback(void *contents, size_t size, size_t nmemb,
                                     void *userp);

void SelectGame(const int game_id);
int MakeAction(const int action);

CarRacingParameters GetGameStateFromServer();

#endif // BRICKGAME_DESKTOP_SRC_GUI_CLI_RETRIEVE_DATA_H_