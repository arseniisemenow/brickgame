package main

import (
	"fmt"
	"github.com/ebitengine/purego"
	"runtime"
)

// #cgo CFLAGS: -g -Wall
// #cgo LDFLAGS: -lstdc++
// #include <stdlib.h>
// #include "brick_game/common/parameters/parameters.h"
// #include "brick_game/common/fsm_types.h"
import "C"

func getSystemLibrary() string {
	switch runtime.GOOS {
	case "darwin":
		return "../libbrickgame.so"
	case "linux":
		return "../libbrickgame.so"
	default:
		panic(fmt.Errorf("GOOS=%s is not supported", runtime.GOOS))
	}
}

const (
	kStart = iota
	kSpawn
	kMoving
	kCollide
	kGameOver
	kExitState
	kPause
)

const (
	kSignalNone = iota
	kSignalMoveUp
	kSignalMoveDown
	kSignalMoveLeft
	kSignalMoveRight
	kSignalEscapeButton
	kSignalEnterButton
	kSignalPauseButton
)

var AllocParameters func() *C.struct_Parameters
var FreeParameters func(*C.struct_Parameters)
var ControllerSnake func(int, *C.struct_Parameters)
var SignalAction func(int, *C.struct_Parameters)

func GetLibrary() (uintptr, error) {
	handle, err := purego.Dlopen(getSystemLibrary(), purego.RTLD_NOW|purego.RTLD_GLOBAL)
	return handle, err
}

func InitFunctions(handle uintptr) {
	purego.RegisterLibFunc(&AllocParameters, handle, "AllocParameters")
	purego.RegisterLibFunc(&FreeParameters, handle, "FreeParameters")
	purego.RegisterLibFunc(&ControllerSnake, handle, "ControllerSnake")
	purego.RegisterLibFunc(&SignalAction, handle, "SignalAction")
}

func main() {
	handle, err := GetLibrary()
	if err != nil {
		panic(err)
	}

	InitFunctions(handle)

	parameters := AllocParameters()
	//signal := kSignalNone

	//ControllerSnake(signal, parameters)

	SignalAction(kSignalEnterButton, parameters)
	SignalAction(kSignalMoveLeft, parameters)
	SignalAction(kSignalMoveLeft, parameters)
	SignalAction(kSignalMoveLeft, parameters)
	SignalAction(kSignalMoveLeft, parameters)

	FreeParameters(parameters)
}
