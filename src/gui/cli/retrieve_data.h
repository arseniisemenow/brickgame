#ifndef BRICKGAME_DESKTOP_SRC_GUI_CLI_RETRIEVE_DATA_H_
#define BRICKGAME_DESKTOP_SRC_GUI_CLI_RETRIEVE_DATA_H_

#define SERVER "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 4096

#include "cjson.h"
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>

struct MemoryStruct {
  char *memory;
  size_t size;
};

typedef struct{
  int lane_;
  int y_;
}  Car;

typedef struct {
  int state_;
  int score_;
  int level_;
  int record_score_;
  Car player_car_racing_;
  Car rival_cars_[2];
  int track_height_;
  int track_width_;
  int time_step_;
  int last_moved_time_;
} CarRacingParameters;
// Callback function for handling data received by cURL
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb,
                                  void *userp);

void SelectGame(const int game_id);
int MakeAction(const int action);

CarRacingParameters GetGameStateFromServer();

#endif // BRICKGAME_DESKTOP_SRC_GUI_CLI_RETRIEVE_DATA_H_
