package race_test

import (
	"github.com/arseniisemenow/race"
	"testing"
)

func TestPrintTrack(t *testing.T) {
	game := race.NewCarRacingGame()
	race.PrintTrack(game)
	// May capture to check the result
}
