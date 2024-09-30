package controller

import "C"
import (
	"fmt"
	"github.com/ebitengine/purego"
	"runtime"
)

func getSystemLibrary() string {
	switch runtime.GOOS {
	case "darwin":
		return "../../../libbrickgame.so"
	case "linux":
		return "../../../libbrickgame.so"
	default:
		panic(fmt.Errorf("GOOS=%s is not supported", runtime.GOOS))
	}
}

var GetTimeInMS func() int64

var AllocState func() *int32
var AllocGameStatus func() *C.struct_GameStatus
var AllocBoard func() *C.struct_Board
var AllocPlayer func() *C.struct_Player
var AllocRecords func() *C.struct_Records
var AllocLastMovedTime func() *int64
var AllocUsername func() *C.char

var AllocParameters func() *C.struct_Parameters
var InitParametersTetris func(*C.struct_Parameters)
var InitParametersSnake func(*C.struct_Parameters)
var FreeParameters func(*C.struct_Parameters)
var ControllerSnake func(int, *C.struct_Parameters)
var SignalAction func(int, *C.struct_Parameters)
var GetTState func(*C.struct_Parameters) *int32
var GetTStateValue func(*C.struct_Parameters) int
var GetTGameStatus func(*C.struct_Parameters) *C.struct_GameStatus
var GetTBoard func(*C.struct_Parameters) *C.struct_Board
var GetTPlayer func(*C.struct_Parameters) *C.struct_Player
var GetTNextPlayer func(*C.struct_Parameters) *C.struct_Player
var GetTPredictPlayer func(*C.struct_Parameters) *C.struct_Player
var GetTRecords func(*C.struct_Parameters) *C.struct_Records
var GetTLastMoveTime func(*C.struct_Parameters) *int64
var GetTUserName func(*C.struct_Parameters) *C.char

var GetSState func(*C.struct_Parameters) *int32
var GetSStateValue func(*C.struct_Parameters) int
var GetSGameStatus func(*C.struct_Parameters) *C.struct_GameStatus
var GetSBoard func(*C.struct_Parameters) *C.struct_Board
var GetSPlayer func(*C.struct_Parameters) *C.struct_Player
var GetSRecords func(*C.struct_Parameters) *C.struct_Records
var GetSLastMoveTime func(*C.struct_Parameters) *int64
var GetSUserName func(*C.struct_Parameters) *C.char
var GetSFruit func(*C.struct_Parameters) *C.struct_Cell

var BoardGetHeight func(*C.struct_Board) int
var BoardGetWidth func(*C.struct_Board) int
var BoardGetCellXY func(*C.struct_Board, int, int) *C.struct_Cell

var CellGetColor func(*C.struct_Cell) int
var CellGetIsSet func(*C.struct_Cell) int
var CellGetX func(*C.struct_Cell) int
var CellGetY func(*C.struct_Cell) int

var InitPlayer func(*C.struct_Player)
var InitNextPlayer func(*C.struct_Player)
var InitBoard func(*C.struct_Board)
var InitGameStatus func(*C.struct_GameStatus)

var PlayerGetDirection func(*C.struct_Player) int
var PlayerGetSnakeLength func(*C.struct_Player) int
var PlayerGetSnakeBodyIndex func(*C.struct_Player, int) *C.struct_Cell
var PlayerGetPlayerBoard func(*C.struct_Player) *C.struct_PlayerBoard
var PlayerGetBlockType func(*C.struct_Player) int
var PlayerGetX func(*C.struct_Player) int
var PlayerGetY func(*C.struct_Player) int

var PlayerBoardGetCellXY func(*C.struct_PlayerBoard, int, int) *C.struct_Cell

var RecordGetRecordIndex func(*C.struct_Records, int) *C.struct_Record
var RecordGetName func(*C.struct_Record) *C.char
var RecordGetScore func(*C.struct_Record) int
var RecordGetIsCurrentPlayer func(*C.struct_Record) int

var GameStateGetScore func(*C.struct_GameStatus) int
var GameStateGetLevel func(*C.struct_GameStatus) int

//int GameStateGetScore(const GameStatus* p_game_status);
//int GameStateGetLevel(const GameStatus* p_game_status);

func GetLibrary() (uintptr, error) {
	handle, err := purego.Dlopen(getSystemLibrary(), purego.RTLD_NOW|purego.RTLD_GLOBAL)
	return handle, err
}

func InitFunctions(handle uintptr) {
	purego.RegisterLibFunc(&GetTimeInMS, handle, "GetTimeInMS")
	purego.RegisterLibFunc(&AllocBoard, handle, "AllocBoard")

	purego.RegisterLibFunc(&AllocParameters, handle, "AllocParameters")
	purego.RegisterLibFunc(&InitParametersTetris, handle, "InitParametersTetris")
	purego.RegisterLibFunc(&InitParametersSnake, handle, "InitParametersSnake")
	purego.RegisterLibFunc(&FreeParameters, handle, "FreeParameters")

	purego.RegisterLibFunc(&ControllerSnake, handle, "ControllerSnake")
	purego.RegisterLibFunc(&SignalAction, handle, "SignalAction")

	purego.RegisterLibFunc(&GetTState, handle, "GetTState")
	purego.RegisterLibFunc(&GetTStateValue, handle, "GetTStateValue")
	purego.RegisterLibFunc(&GetTGameStatus, handle, "GetTGameStatus")
	purego.RegisterLibFunc(&GetTBoard, handle, "GetTBoard")
	purego.RegisterLibFunc(&GetTPlayer, handle, "GetTPlayer")
	purego.RegisterLibFunc(&GetTNextPlayer, handle, "GetTNextPlayer")
	purego.RegisterLibFunc(&GetTPredictPlayer, handle, "GetTPredictPlayer")
	purego.RegisterLibFunc(&GetTRecords, handle, "GetTRecords")
	purego.RegisterLibFunc(&GetTLastMoveTime, handle, "GetTLastMoveTime")
	purego.RegisterLibFunc(&GetTUserName, handle, "GetTUserName")

	purego.RegisterLibFunc(&GetSState, handle, "GetSState")
	purego.RegisterLibFunc(&GetSStateValue, handle, "GetSStateValue")
	purego.RegisterLibFunc(&GetSGameStatus, handle, "GetSGameStatus")
	purego.RegisterLibFunc(&GetSBoard, handle, "GetSBoard")
	purego.RegisterLibFunc(&GetSPlayer, handle, "GetSPlayer")
	purego.RegisterLibFunc(&GetSRecords, handle, "GetSRecords")
	purego.RegisterLibFunc(&GetSLastMoveTime, handle, "GetSLastMoveTime")
	purego.RegisterLibFunc(&GetSUserName, handle, "GetSUserName")
	purego.RegisterLibFunc(&GetSFruit, handle, "GetSFruit")

	purego.RegisterLibFunc(&BoardGetHeight, handle, "BoardGetHeight")
	purego.RegisterLibFunc(&BoardGetWidth, handle, "BoardGetWidth")
	purego.RegisterLibFunc(&BoardGetCellXY, handle, "BoardGetCellXY")

	purego.RegisterLibFunc(&CellGetColor, handle, "CellGetColor")
	purego.RegisterLibFunc(&CellGetIsSet, handle, "CellGetIsSet")
	purego.RegisterLibFunc(&CellGetX, handle, "CellGetX")
	purego.RegisterLibFunc(&CellGetY, handle, "CellGetY")

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

	purego.RegisterLibFunc(&PlayerGetDirection, handle, "PlayerGetDirection")
	purego.RegisterLibFunc(&PlayerGetSnakeLength, handle, "PlayerGetSnakeLength")
	purego.RegisterLibFunc(&PlayerGetSnakeBodyIndex, handle, "PlayerGetSnakeBodyIndex")
	purego.RegisterLibFunc(&PlayerGetPlayerBoard, handle, "PlayerGetPlayerBoard")
	purego.RegisterLibFunc(&PlayerGetBlockType, handle, "PlayerGetBlockType")
	purego.RegisterLibFunc(&PlayerGetX, handle, "PlayerGetX")
	purego.RegisterLibFunc(&PlayerGetY, handle, "PlayerGetY")

	purego.RegisterLibFunc(&PlayerBoardGetCellXY, handle, "PlayerBoardGetCellXY")

	purego.RegisterLibFunc(&RecordGetRecordIndex, handle, "RecordGetRecordIndex")
	purego.RegisterLibFunc(&RecordGetName, handle, "RecordGetName")
	purego.RegisterLibFunc(&RecordGetScore, handle, "RecordGetScore")
	purego.RegisterLibFunc(&RecordGetIsCurrentPlayer, handle, "RecordGetIsCurrentPlayer")

	purego.RegisterLibFunc(&GameStateGetScore, handle, "GameStateGetScore")
	purego.RegisterLibFunc(&GameStateGetLevel, handle, "GameStateGetLevel")
}

var Parameters *C.struct_Parameters

func InitController() {
	handle, err := GetLibrary()
	if err != nil {
		panic(err)
	}

	InitFunctions(handle)
	Parameters = AllocParameters()
}
