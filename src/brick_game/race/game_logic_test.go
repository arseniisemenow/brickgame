package race_test

import (
	"github.com/arseniisemenow/race"
	"testing"
)

func TestMoveObstacleCarUpward(t *testing.T) {
	game := race.NewCarRacingGame()
	car := &game.RivalCars[0]
	race.MoveObstacleCarUpward(car, 3)
	if car.Y != 3 {
		t.Errorf("Expected Y to be 3, got %d", car.Y)
	}
	if car.Lane < 0 || car.Lane > 2 {
		t.Errorf("Expected Lane between 0 and 2, got %d", car.Lane)
	}
}

func TestHandleRivalCars(t *testing.T) {
	game := race.NewCarRacingGame()
	race.HandleRivalCars(game)
	for _, car := range game.RivalCars {
		if car.Y <= 0 {
			t.Errorf("Expected RivalCar Y to increase, got %d", car.Y)
		}
	}
}
