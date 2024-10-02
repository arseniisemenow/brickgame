package race_test

import (
	"github.com/arseniisemenow/race"
	"testing"
)

func TestActionMoveUp(t *testing.T) {
	game := race.NewCarRacingGame()
	game.Player.Y = 1
	race.ActionMoveUp(game)
	if game.Player.Y != 0 {
		t.Errorf("Expected Y to be 0, got %d", game.Player.Y)
	}
}

func TestActionMoveDown(t *testing.T) {
	game := race.NewCarRacingGame()
	game.Player.Y = game.TrackHeight - 2
	race.ActionMoveDown(game)
	if game.Player.Y != game.TrackHeight-1 {
		t.Errorf("Expected Y to be %d, got %d", game.TrackHeight-1, game.Player.Y)
	}
}

func TestActionMoveLeft(t *testing.T) {
	game := race.NewCarRacingGame()
	game.Player.Lane = 1
	race.ActionMoveLeft(game)
	if game.Player.Lane != 0 {
		t.Errorf("Expected Lane to be 0, got %d", game.Player.Lane)
	}
}

func TestActionMoveRight(t *testing.T) {
	game := race.NewCarRacingGame()
	game.Player.Lane = 1
	race.ActionMoveRight(game)
	if game.Player.Lane != 2 {
		t.Errorf("Expected Lane to be 2, got %d", game.Player.Lane)
	}
}

func TestActionSpawn(t *testing.T) {
	game := race.NewCarRacingGame()
	race.ActionSpawn(game)
	if game.Player.Y != game.TrackHeight-1 || game.Player.Lane != 1 {
		t.Errorf("Expected Player.Y to be %d and Player.Lane to be 1, got Y=%d Lane=%d", game.TrackHeight-1, game.Player.Y, game.Player.Lane)
	}
}

func TestActionCollide(t *testing.T) {
	game := race.NewCarRacingGame()
	race.ActionCollide(game)
	if game.State != race.KGameOver {
		t.Errorf("Expected game state to be KGameOver, got %v", game.State)
	}
}
