package race

import "time"

type State int

const (
	KStart State = iota
	KSpawn
	KMoving
	KCollide
	KGameOver
	KExitState
	KPause
)

type Signal int

const (
	KSignalNone Signal = iota
	KSignalMoveUp
	KSignalMoveDown
	KSignalMoveLeft
	KSignalMoveRight
	KSignalExit
	KSignalSpawn
	KSignalPause
)

type Car struct {
	Lane int `json:"lane"`
	Y    int `json:"y"`
}

type CarRacingGame struct {
	State         State  `json:"state_car_racing"`
	Score         int    `json:"score"`
	Level         int    `json:"level"`
	RecordsScore  int    `json:"record_score"`
	Player        Car    `json:"player_car_racing"`
	RivalCars     [2]Car `json:"rival_cars"`
	TrackHeight   int    `json:"track_height"`
	TrackWidth    int    `json:"track_width"`
	TimeStep      int64  `json:"time_step"`
	LastMovedTime int64  `json:"last_moved_time"`
}

func NewCarRacingGame() *CarRacingGame {
	return &CarRacingGame{
		State:         KStart,
		Score:         0,
		Player:        Car{Lane: 1, Y: 10},
		RivalCars:     [2]Car{{Lane: 0, Y: 0}, {Lane: 0, Y: 0}},
		TrackHeight:   20,
		TrackWidth:    10,
		TimeStep:      200,
		LastMovedTime: time.Now().UnixMilli(),
	}
}
