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
		return "libbrickgame.so"
	case "linux":
		return "libbrickgame.so"
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

func main() {
	libc, err := purego.Dlopen(getSystemLibrary(), purego.RTLD_NOW|purego.RTLD_GLOBAL)
	if err != nil {
		panic(err)
	}

	var AllocParameters func() *C.struct_Parameters
	purego.RegisterLibFunc(&AllocParameters, libc, "AllocParameters")
	var FreeParameters func(*C.struct_Parameters)
	purego.RegisterLibFunc(&FreeParameters, libc, "FreeParameters")

	parameters := AllocParameters()
	signal := kSignalNone

	var ControllerSnake func(int, *C.struct_Parameters)
	purego.RegisterLibFunc(&ControllerSnake, libc, "ControllerSnake")
	ControllerSnake(signal, parameters)

	FreeParameters(parameters)
}
