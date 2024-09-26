#include "parameters.h"

Parameters* AllocParameters(){
    return (Parameters*) calloc(sizeof(Parameters), 1);
}