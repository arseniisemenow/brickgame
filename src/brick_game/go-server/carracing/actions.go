package carracing

import (
	"fmt"
)

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
	Lane int // Lane position (0, 1, or 2)
	Y    int // Vertical position on the track
}

type CarRacingGame struct {
	Player      Car
	RivalCars   [2]Car
	TrackHeight int
	State       State
}

func GetUserInput(code int) Signal {
	return Signal(code)
}

func ActionMoveUp(game *CarRacingGame) {
	if game.Player.Y > 0 {
		game.Player.Y--
	}
}

func ActionMoveDown(game *CarRacingGame) {
	if game.Player.Y < game.TrackHeight-1 {
		game.Player.Y++
	}
}

func ActionMoveLeft(game *CarRacingGame) {
	if game.Player.Lane > 0 {
		game.Player.Lane--
	}
}

func ActionMoveRight(game *CarRacingGame) {
	if game.Player.Lane < 2 {
		game.Player.Lane++
	}
}

func ActionSpawn(game *CarRacingGame) {
	game.Player.Y = game.TrackHeight - 1
	game.Player.Lane = 1
	for i := 0; i < 2; i++ {
		MoveCarUpward(&game.RivalCars[i], i*3)
	}
}

func ActionCollide(game *CarRacingGame) {
	fmt.Println("Collision! Game Over.")
	game.State = KGameOver
}

func ActionGameOver(game *CarRacingGame) {
	fmt.Println("Resetting game...")
	game.Player = Car{Lane: 1, Y: game.TrackHeight - 1}
	game.State = KStart
}

func ActionExitState(game *CarRacingGame) {
	fmt.Println("Exiting game...")
	game.State = KExitState
}

func ActionPause(game *CarRacingGame) {
	fmt.Println("Game is paused...")
	game.State = KPause
}
