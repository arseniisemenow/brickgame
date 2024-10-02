package race_test

import (
	"github.com/arseniisemenow/race"
	"testing"
)

func TestNewCarRacingGame(t *testing.T) {
	game := race.NewCarRacingGame()
	if game.State != race.KStart {
		t.Errorf("Expected initial state to be KStart, got %v", game.State)
	}
	if game.Player.Lane != 1 {
		t.Errorf("Expected Player Lane to be 1, got %d", game.Player.Lane)
	}
	if game.TrackHeight != 20 {
		t.Errorf("Expected TrackHeight to be 20, got %d", game.TrackHeight)
	}
}
