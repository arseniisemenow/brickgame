#include "retrieve_data.h"

int main() {
  SelectGame(3);
  MakeAction(6);
  MakeAction(6);
  cJSON *data = GetGameStateFromServer();
  MakeAction(7);
  MakeAction(7);
  return 0;
}