#include "api_client.h"

CarRacingParameters ParseParameters1(CarRacingParameters *parameters,
                                     const cJSON *car_racing_parameters,
                                     const cJSON *player_car_racing);
CarRacingParameters ParseParameters2(CarRacingParameters *parameters,
                                     const cJSON *rival_cars);
static size_t IgnoreResponseCallback(void *contents, size_t size, size_t nmemb,
                                     void *userp) {
  return size * nmemb;
}

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb,
                                  void *userp) {
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  mem->memory = (char *)realloc(mem->memory, mem->size + realsize + 1);
  if (mem->memory == NULL) {
    printf("Not enough memory to allocate\n");
    return 0;
  }

  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}
int MakePostRequestWithJson(const char *url, const char *port,
                            const char *endpoint, const char *json) {
  CURL *curl;
  CURLcode res;
  int error_code = 0;

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();

  if (curl) {
    char full_url[64] = {0};
    snprintf(full_url, 64 - 1, "%s:%s/%s", url, port, endpoint);

    curl_easy_setopt(curl, CURLOPT_URL, full_url);

    curl_easy_setopt(curl, CURLOPT_POST, 1L);

    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, IgnoreResponseCallback);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
      error_code = 1;
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    } else {
      error_code = 0;
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();

  return error_code;
}

const cJSON *MakeGetRequestRetrieveState(const char *url, const char *port,
                                         const char *endpoint) {
  CURL *curl;
  CURLcode res;
  struct MemoryStruct chunk;
  CarRacingParameters parameters = {0};

  chunk.memory = (char *)malloc(1);
  chunk.size = 0;

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();

  if (curl) {
    char full_url[64] = {0};
    snprintf(full_url, 64 - 1, "%s:%s/%s", url, port, endpoint);
    curl_easy_setopt(curl, CURLOPT_URL, full_url);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    }

    curl_easy_cleanup(curl);
  }

  const cJSON *game_state = cJSON_Parse(chunk.memory);
  if (game_state == NULL) {
    printf("Error parsing JSON\n");
    free(chunk.memory);
    curl_global_cleanup();
    return NULL;
  }
  return game_state;
}
CarRacingParameters ParseParameters2(CarRacingParameters *parameters,
                                     const cJSON *rival_cars) {
  for (int i = 0; i < cJSON_GetArraySize(rival_cars); i++) {
    const cJSON *rival_car = cJSON_GetArrayItem(rival_cars, i);
    if (!rival_car) {
      break;
    }
    (*parameters).rival_cars_[i].lane_ =
        cJSON_GetObjectItem(rival_car, "lane")->valueint;
    (*parameters).rival_cars_[i].y_ =
        cJSON_GetObjectItem(rival_car, "y")->valueint;
  }
  return (*parameters);
}
CarRacingParameters ParseParameters1(CarRacingParameters *parameters,
                                     const cJSON *car_racing_parameters,
                                     const cJSON *player_car_racing) {
  (*parameters).state_ =
      cJSON_GetObjectItem(car_racing_parameters, "state_car_racing")->valueint;
  (*parameters).score_ =
      cJSON_GetObjectItem(car_racing_parameters, "score")->valueint;
  (*parameters).level_ =
      cJSON_GetObjectItem(car_racing_parameters, "level")->valueint;
  (*parameters).record_score_ =
      cJSON_GetObjectItem(car_racing_parameters, "record_score")->valueint;
  (*parameters).time_step_ =
      cJSON_GetObjectItem(car_racing_parameters, "time_step")->valueint;
  (*parameters).last_moved_time_ =
      cJSON_GetObjectItem(car_racing_parameters, "last_moved_time")->valueint;

  (*parameters).track_height_ =
      cJSON_GetObjectItem(car_racing_parameters, "track_height")->valueint;
  (*parameters).track_width_ =
      cJSON_GetObjectItem(car_racing_parameters, "track_width")->valueint;

  (*parameters).player_car_racing_.lane_ =
      cJSON_GetObjectItem(player_car_racing, "lane")->valueint;
  (*parameters).player_car_racing_.y_ =
      cJSON_GetObjectItem(player_car_racing, "y")->valueint;
  return (*parameters);
}

int MakePostRequestWithInlineQueryNumber(const char *url, const char *port,
                                         const char *endpoint,
                                         const int game_id) {
  int error_code = 0;
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if (curl) {
    char full_url[64] = {0};
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    snprintf(full_url, 64 - 1, "%s:%s/%s/%d", url, port, endpoint, game_id);

    curl_easy_setopt(curl, CURLOPT_URL, full_url);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
      error_code = 1;
    }

    curl_easy_cleanup(curl);
  }
  return error_code;
}

int SendSignalAction(const int action){
  char json[64] = {0};
  snprintf(json, 64-1, "{\"action\": \"%d\"}", action);
  return MakePostRequestWithJson("http://localhost", "8080", "api/actions", json);
}


CarRacingParameters GetParameters(){
  CarRacingParameters parameters = {0};
  const cJSON *json = MakeGetRequestRetrieveState("http://127.0.0.1", "8080", "api/parameters");
  if (json == NULL) {
    printf("Error parsing JSON\n");
    return parameters;
  }

  const cJSON *car_racing_parameters =
      cJSON_GetObjectItem(json, "car_racing_parameters");
  if (!car_racing_parameters) {
    return parameters;
  }

  const cJSON *player_car_racing =
      cJSON_GetObjectItem(car_racing_parameters, "player_car_racing");
  if (!player_car_racing) {
    return parameters;
  }
  const cJSON *rival_cars =
      cJSON_GetObjectItem(car_racing_parameters, "rival_cars");
  if (!rival_cars) {
    return parameters;
  }
  ParseParameters1(&parameters, car_racing_parameters, player_car_racing);
  ParseParameters2(&parameters, rival_cars);

  return parameters;
}


int SelectGame(const int game_id){
  return MakePostRequestWithInlineQueryNumber("http://localhost", "8080", "api/games", game_id);
}

