package main

import (
	"fmt"
	"github.com/ebitengine/purego"
	"log"
	"runtime"
	"unsafe"
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

var GetTimeInMS func() int64

var AllocState func() *C.struct_State
var AllocGameStatus func() *C.struct_GameStatus
var AllocBoard func() *C.struct_Board
var AllocPlayer func() *C.struct_Player
var AllocRecords func() *C.struct_Records
var AllocLastMovedTime func() *int64
var AllocUsername func() *C.char

var AllocParameters func() *C.struct_Parameters
var FreeParameters func(*C.struct_Parameters)
var ControllerSnake func(int, *C.struct_Parameters)
var SignalAction func(int, *C.struct_Parameters)
var GetTState func(*C.struct_Parameters) *C.struct_State
var GetTGameStatus func(*C.struct_Parameters) *C.struct_GameStatus
var GetTBoard func(*C.struct_Parameters) *C.struct_Board
var GetTPlayer func(*C.struct_Parameters) *C.struct_Player
var GetTNextPlayer func(*C.struct_Parameters) *C.struct_Player
var GetTPredictPlayer func(*C.struct_Parameters) *C.struct_Player
var GetTRecords func(*C.struct_Parameters) *C.struct_Records
var GetTLastMoveTime func(*C.struct_Parameters) *int64
var GetTUserName func(*C.struct_Parameters) *C.char

var InitPlayer func(*C.struct_Player)
var InitNextPlayer func(*C.struct_Player)
var InitBoard func(*C.struct_Board)
var InitGameStatus func(*C.struct_GameStatus)

func GetLibrary() (uintptr, error) {
	handle, err := purego.Dlopen(getSystemLibrary(), purego.RTLD_NOW|purego.RTLD_GLOBAL)
	return handle, err
}

func InitFunctions(handle uintptr) {
	purego.RegisterLibFunc(&GetTimeInMS, handle, "GetTimeInMS")
	purego.RegisterLibFunc(&AllocBoard, handle, "AllocBoard")

	purego.RegisterLibFunc(&AllocParameters, handle, "AllocParameters")
	purego.RegisterLibFunc(&FreeParameters, handle, "FreeParameters")
	purego.RegisterLibFunc(&ControllerSnake, handle, "ControllerSnake")
	purego.RegisterLibFunc(&SignalAction, handle, "SignalAction")

	purego.RegisterLibFunc(&GetTState, handle, "GetTState")
	purego.RegisterLibFunc(&GetTGameStatus, handle, "GetTGameStatus")
	purego.RegisterLibFunc(&GetTBoard, handle, "GetTBoard")
	purego.RegisterLibFunc(&GetTPlayer, handle, "GetTPlayer")
	purego.RegisterLibFunc(&GetTNextPlayer, handle, "GetTNextPlayer")
	purego.RegisterLibFunc(&GetTPredictPlayer, handle, "GetTPredictPlayer")
	purego.RegisterLibFunc(&GetTRecords, handle, "GetTRecords")
	purego.RegisterLibFunc(&GetTLastMoveTime, handle, "GetTLastMoveTime")
	purego.RegisterLibFunc(&GetTUserName, handle, "GetTUserName")

	purego.RegisterLibFunc(&InitPlayer, handle, "InitPlayer")
	purego.RegisterLibFunc(&InitNextPlayer, handle, "InitNextPlayer")
	purego.RegisterLibFunc(&InitBoard, handle, "InitBoard")
	purego.RegisterLibFunc(&InitGameStatus, handle, "InitGameStatus")

	purego.RegisterLibFunc(&AllocState, handle, "AllocState")
	purego.RegisterLibFunc(&AllocGameStatus, handle, "AllocGameStatus")
	purego.RegisterLibFunc(&AllocBoard, handle, "AllocBoard")
	purego.RegisterLibFunc(&AllocPlayer, handle, "AllocPlayer")
	purego.RegisterLibFunc(&AllocRecords, handle, "AllocRecords")
	purego.RegisterLibFunc(&AllocLastMovedTime, handle, "AllocLastMovedTime")
	purego.RegisterLibFunc(&AllocUsername, handle, "AllocUsername")
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

	//log.Println(*parameters.t_state_)

	// Access t_state_ (offset 0 bytes)
	tStatePtr := (*C.struct_State)(unsafe.Pointer(uintptr(unsafe.Pointer(parameters)) + 0))
	log.Println(tStatePtr)

	// Access t_game_status_ (offset 8 bytes)
	tGameStatus := (*C.struct_GameStatus)(unsafe.Pointer(uintptr(unsafe.Pointer(parameters)) + 8))
	log.Println(tGameStatus)

	// Access t_board_ (offset 16 bytes)
	tBoard := (*C.struct_Board)(unsafe.Pointer(uintptr(unsafe.Pointer(parameters)) + 16))
	log.Println(tBoard)

	// Access t_player_ (offset 24 bytes)
	tPlayer := (*C.struct_Player)(unsafe.Pointer(uintptr(unsafe.Pointer(parameters)) + 24))
	log.Println(tPlayer)

	// Access t_next_player_ (offset 32 bytes)
	tNextPlayer := (*C.struct_Player)(unsafe.Pointer(uintptr(unsafe.Pointer(parameters)) + 32))
	log.Println(tNextPlayer)

	// Access t_predict_player_ (offset 40 bytes)
	tPredictPlayer := (*C.struct_Player)(unsafe.Pointer(uintptr(unsafe.Pointer(parameters)) + 40))
	log.Println(tPredictPlayer)

	// Access t_records_ (offset 48 bytes)
	tRecords := (*C.struct_Records)(unsafe.Pointer(uintptr(unsafe.Pointer(parameters)) + 48))
	log.Println(tRecords)

	// Access t_last_moved_time_ (offset 56 bytes)
	tLastMoveTime := (*int64)(unsafe.Pointer(uintptr(unsafe.Pointer(parameters)) + 56))
	log.Println(tLastMoveTime)

	// Access t_username (offset 64 bytes)
	tUsername := (*C.char)(unsafe.Pointer(uintptr(unsafe.Pointer(parameters)) + 64))
	log.Println(C.GoString(tUsername))

	//*tLastMoveTime = GetTimeInMS()
	//log.Println("Updated Last Move Time:", *tLastMoveTime)

	tStatePtr = AllocState()
	tGameStatus = AllocGameStatus()
	tBoard = AllocBoard()
	tPlayer = AllocPlayer()
	tNextPlayer = AllocPlayer()
	tPredictPlayer = AllocPlayer()
	tRecords = AllocRecords()
	tLastMoveTime = AllocLastMovedTime()
	tUsername = AllocUsername()

	//tStatePtr := (*int32)(unsafe.Pointer(uintptr(unsafe.Pointer(parameters)) + 0))
	//tGameStatus := (*C.struct_GameStatus)(unsafe.Pointer(uintptr(unsafe.Pointer(parameters)) + 8))
	//tBoard := (*C.struct_Board)(unsafe.Pointer(uintptr(unsafe.Pointer(parameters)) + 16))
	//*tStatePtr = C.kStart

	//InitPlayer(GetTPlayer(parameters))
	//InitNextPlayer(GetTNextPlayer(parameters))
	//InitBoard(tBoard)
	InitBoard(tBoard)
	InitGameStatus(tGameStatus)
	//*GetTLastMoveTime(parameters) = GetTimeInMS()

	//LoadRecords(p_parameters->t_records_, TETRIS_RECORDS_FILE_NAME);
	//SaveRecords(p_parameters->t_records_, TETRIS_RECORDS_FILE_NAME);

	SignalAction(kSignalEnterButton, parameters)

	//SetPlayerBlockType(p_parameters->t_player_, kBlockO);
	//RepeatSignal(kSignalMoveLeft, p_parameters, 10);
	//RepeatSignal(kSignalMoveDown, p_parameters, 20);

	//FreeParameters(parameters)
}
