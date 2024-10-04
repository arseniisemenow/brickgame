#include "fsm_types.h"

#include <stdlib.h>

State *AllocState() { return (State *)calloc(sizeof(State), 1); }
SignalType *AllocSignalType() {
  return (SignalType *)calloc(sizeof(SignalType), 1);
}

void FreeState(State *p_state) { free(p_state); }
void FreeSignalType(SignalType *p_signal_type) { free(p_signal_type); }