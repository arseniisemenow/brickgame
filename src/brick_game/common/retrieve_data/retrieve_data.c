#include "retrieve_data.h"

static size_t IgnoreResponseCallback(void *contents, size_t size, size_t nmemb, void *userp) {
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


int MakeAction(const int action) {
  CURL *curl;
  CURLcode res;
  int success = 0;

  // Initialize cURL
  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();

  if (curl) {
    // Prepare the URL and data to send
    const char *url = "http://127.0.0.1:8080/api/actions";
    char json_data[256];
    snprintf(json_data, sizeof(json_data), "{\"action\": \"%d\"}", action);

    // Set the URL
    curl_easy_setopt(curl, CURLOPT_URL, url);

    // Set the request type to POST
    curl_easy_setopt(curl, CURLOPT_POST, 1L);

    // Set the POST data
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data);

    // Set the content type to JSON
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, IgnoreResponseCallback);


    // Perform the POST request
    res = curl_easy_perform(curl);

    // Check if the request was successful
    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    } else {
      success = 1;
    }

    // Clean up
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
  }

  // Clean up cURL globally
  curl_global_cleanup();

  return success;
}
//todo: add a security by checking pointer for NULL
CarRacingParameters GetGameStateFromServer() {
  CURL *curl;
  CURLcode res;
  struct MemoryStruct chunk;
  CarRacingParameters parameters = {0};

  // Initialize the response memory
  chunk.memory = (char *)malloc(1);
  chunk.size = 0;

  // Initialize cURL
  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();

  if (curl) {
    // Set the URL for the request
    curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:8080/api/parameters");

    // Set the write callback function to handle data
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

    // Pass the chunk struct to the callback function
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

    // Perform the request
    res = curl_easy_perform(curl);

    // Check for errors
    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    }

    // Clean up cURL
    curl_easy_cleanup(curl);
  }

  // Parse the received JSON data
  cJSON *game_state = cJSON_Parse(chunk.memory);
  if (game_state == NULL) {
    printf("Error parsing JSON\n");
  }

  // Free the chunk memory
  free(chunk.memory);

  // Clean up cURL global environment
  curl_global_cleanup();

  cJSON *car_racing_parameters =
      cJSON_GetObjectItem(game_state, "car_racing_parameters");

  cJSON *player_car_racing =
      cJSON_GetObjectItem(car_racing_parameters, "player_car_racing");
  cJSON *rival_cars = cJSON_GetObjectItem(car_racing_parameters, "rival_cars");

  parameters.state_ =
      cJSON_GetObjectItem(car_racing_parameters, "state_car_racing")->valueint;
  parameters.score_ =
      cJSON_GetObjectItem(car_racing_parameters, "score")->valueint;
  parameters.level_ =
      cJSON_GetObjectItem(car_racing_parameters, "level")->valueint;
  parameters.record_score_ =
      cJSON_GetObjectItem(car_racing_parameters, "record_score")->valueint;
  parameters.time_step_ =
      cJSON_GetObjectItem(car_racing_parameters, "time_step")->valueint;
  parameters.last_moved_time_ =
      cJSON_GetObjectItem(car_racing_parameters, "last_moved_time")->valueint;

  parameters.track_height_ =
      cJSON_GetObjectItem(car_racing_parameters, "track_height")->valueint;
  parameters.track_width_ =
      cJSON_GetObjectItem(car_racing_parameters, "track_width")->valueint;

  parameters.player_car_racing_.lane_ =
      cJSON_GetObjectItem(player_car_racing, "lane")->valueint;
  parameters.player_car_racing_.y_ =
      cJSON_GetObjectItem(player_car_racing, "y")->valueint;

  for (int i = 0; i < cJSON_GetArraySize(rival_cars); i++) {
    cJSON *rival_car = cJSON_GetArrayItem(rival_cars, i);
    parameters.rival_cars_[i].lane_ =
        cJSON_GetObjectItem(rival_car, "lane")->valueint;
    parameters.rival_cars_[i].y_ =
        cJSON_GetObjectItem(rival_car, "y")->valueint;
  }

  return parameters;
}

void SelectGame(const int game_id) {
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if (curl) {
    const char *json = "{\"gameId\": \"3\"}";
    struct curl_slist *slist1 = NULL;
    slist1 = curl_slist_append(slist1, "Content-Type: application/json");
    slist1 = curl_slist_append(slist1, "Accept: application/json");

    /* set custom headers */
    //    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist1);

    char full_url[64] = {0};
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    snprintf(full_url, 64 - 1, "http://localhost:8080/api/games/%d", game_id);

    curl_easy_setopt(curl, CURLOPT_URL, full_url);

    /* pass in a pointer to the data - libcurl does not copy */
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json);

    // Perform the request
    res = curl_easy_perform(curl);

    // Check for errors
    if (res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    // Cleanup
    curl_easy_cleanup(curl);
  }
}
