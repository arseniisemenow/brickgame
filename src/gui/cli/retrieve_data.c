#include "retrieve_data.h"

// Callback function for handling data received by cURL
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

    // Perform the POST request
    res = curl_easy_perform(curl);

    // Check if the request was successful
    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    } else {
      printf("Action \"%s\" sent successfully.\n", action);
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

cJSON *GetGameStateFromServer() {
  CURL *curl;
  CURLcode res;
  struct MemoryStruct chunk;

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

  return game_state;
}

void SendAction(char *action) {
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8080/api/actions");

    // Set the POST data
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS,
                     action); // Example: "{\"action\": \"move_left\"}"

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
