package race_test

import (
	"github.com/arseniisemenow/race"
	"testing"
)

func TestSummary(t *testing.T) {
	game := race.NewCarRacingGame()
	if game.State != race.KStart {
		t.Errorf("Expected KStart state, got %d", game.State)
	}
	race.SignalAction(race.KSignalSpawn, game) // Start -> Spawn state
	if game.State != race.KSpawn {
		t.Errorf("Expected KSpawn state, got %d", game.State)
	}
	race.SignalAction(race.KSignalSpawn, game) // Spawn -> Moving state
	if game.State != race.KMoving {
		t.Errorf("Expected KMoving state, got %d", game.State)
	}
	race.SignalAction(race.KSignalMoveLeft, game) // Moving in diff directions
	race.SignalAction(race.KSignalMoveRight, game)
	race.SignalAction(race.KSignalMoveRight, game)
}
