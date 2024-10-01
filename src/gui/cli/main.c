#include "retrieve_data.h"

int main() {
  SelectGame(3);
  MakeAction(6);
  MakeAction(6);
  CarRacingParameters parameters = GetGameStateFromServer();
  MakeAction(7);
  MakeAction(7);

  parameters = GetGameStateFromServer();



  return 0;
}