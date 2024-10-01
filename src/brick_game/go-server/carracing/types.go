package carracing

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
	Lane int `json:"lane"` // Lane position (0, 1, or 2)
	Y    int `json:"y"`    // Vertical position on the track
}

type CarRacingGame struct {
	State         State  `json:"state_car_racing"`
	Player        Car    `json:"player_car_racing"`
	RivalCars     [2]Car `json:"rival_cars"`
	TrackHeight   int    `json:"track_height"`
	TimeStep      int64  `json:"time_step"`
	LastMovedTime int64  `json:"last_moved_time"`
}

func NewCarRacingGame() *CarRacingGame {
	return &CarRacingGame{
		State:         KStart,
		Player:        Car{Lane: 1, Y: 10},
		RivalCars:     [2]Car{{Lane: 0, Y: 0}, {Lane: 0, Y: 0}},
		TrackHeight:   20,
		TimeStep:      500, // Time step in milliseconds for obstacle movement
		LastMovedTime: time.Now().UnixMilli(),
	}
}

func InitParametersCarRacing() {
	Parameters = NewCarRacingGame()
}
