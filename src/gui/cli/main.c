#include "retrieve_data.h"

int main(){
  SelectGame(3);
  cJSON* data = GetGameStateFromServer();
  return 0;
}