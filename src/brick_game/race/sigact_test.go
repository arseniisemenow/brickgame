package race_test

import (
	"github.com/arseniisemenow/race"
	"testing"
)

func TestSignalAction_StartToSpawn(t *testing.T) {
	game := race.NewCarRacingGame()
	race.SignalAction(race.KSignalSpawn, game)
	if game.State != race.KSpawn {
		t.Errorf("Expected state to transition to KSpawn, got %v", game.State)
	}
}

func TestSignalAction_MovingState(t *testing.T) {
	game := race.NewCarRacingGame()
	game.State = race.KMoving
	initialLane := game.Player.Lane
	race.SignalAction(race.KSignalMoveLeft, game)
	if game.Player.Lane != initialLane-1 {
		t.Errorf("Expected Lane to decrease to %d, got %d", initialLane-1, game.Player.Lane)
	}
}

func TestSignalAction_MovingState2(t *testing.T) {
	game := race.NewCarRacingGame()
	game.State = race.KMoving
	initialLane := game.Player.Lane
	race.SignalAction(race.KSignalMoveRight, game)
	if game.Player.Lane != initialLane+1 {
		t.Errorf("Expected Lane to decrease to %d, got %d", initialLane+1, game.Player.Lane)
	}
}

func TestSignalAction_Collision(t *testing.T) {
	game := race.NewCarRacingGame()
	game.Player.Lane = 1
	game.RivalCars[0].Lane = 1
	game.RivalCars[0].Y = game.Player.Y
	race.CheckForCollision(game)
	if game.State != race.KCollide {
		t.Errorf("Expected state to be KCollide, got %v", game.State)
	}
}

func TestSignalAction_PauseUnpause(t *testing.T) {
	game := race.NewCarRacingGame()
	game.State = race.KMoving
	race.SignalAction(race.KSignalPause, game)
	if game.State != race.KPause {
		t.Errorf("Expected state to be KPause, got %v", game.State)
	}
	race.SignalAction(race.KSignalPause, game)
	if game.State != race.KMoving {
		t.Errorf("Expected state to be KMoving after unpausing, got %v", game.State)
	}
}
