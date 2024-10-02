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

func TestMoveObstacleCarUpward2(t *testing.T) {
	car := race.Car{Lane: 0, Y: 5}

	race.MoveObstacleCarUpward(&car, 0)

	if car.Y != 0 {
		t.Errorf("Expected Y to be 0, got %d", car.Y)
	}
	if car.Lane < 0 || car.Lane >= 3 {
		t.Errorf("Expected Lane to be in range 0-2, got %d", car.Lane)
	}
}

func TestHandleRivalCars2(t *testing.T) {
	game := race.NewCarRacingGame()
	game.Player.Y = 5
	game.RivalCars[0].Y = 5
	game.RivalCars[1].Y = 10

	race.HandleRivalCars(game)

	// Score should be increased since the first car is overtaken
	if game.Score != 1 {
		t.Errorf("Expected Score to be 1, got %d", game.Score)
	}

	// Rival cars should move closer
	if game.RivalCars[0].Y != 6 {
		t.Errorf("Expected RivalCar[0].Y to be 6, got %d", game.RivalCars[0].Y)
	}
	if game.RivalCars[1].Y != 11 {
		t.Errorf("Expected RivalCar[1].Y to be 11, got %d", game.RivalCars[1].Y)
	}
}

func TestHandleOvertakenRivalCar(t *testing.T) {
	game := race.NewCarRacingGame()
	game.TrackHeight = 20
	game.RivalCars[0].Y = 20
	game.RivalCars[1].Y = 10

	race.HandleOvertakenRivalCar(game, 0)

	if game.RivalCars[0].Y != 0 {
		t.Errorf("Expected RivalCar[0] Y to reset to 0, got %d", game.RivalCars[0].Y)
	}
	if game.RivalCars[0].Lane < 0 || game.RivalCars[0].Lane >= 3 {
		t.Errorf("Expected RivalCar[0] Lane to be in range 0-2, got %d", game.RivalCars[0].Lane)
	}
}

func TestHandleRivalCarGetsCloser(t *testing.T) {
	game := race.NewCarRacingGame()
	game.RivalCars[0].Y = 10

	race.HandleRivalCarGetsCloser(game, 0)

	if game.RivalCars[0].Y != 11 {
		t.Errorf("Expected RivalCar[0].Y to increment to 11, got %d", game.RivalCars[0].Y)
	}
}

func TestHandleScoreForOvertake(t *testing.T) {
	game := race.NewCarRacingGame()
	game.Player.Y = 5
	game.RivalCars[0].Y = 5
	game.Score = 0

	race.HandleScoreForOvertake(game, 0)

	if game.Score != 1 {
		t.Errorf("Expected Score to increase to 1, got %d", game.Score)
	}

	if game.RecordsScore != 1 {
		t.Errorf("Expected RecordsScore to increase to 1, got %d", game.RecordsScore)
	}
}

func TestUpdateLevel(t *testing.T) {
	game := race.NewCarRacingGame()
	game.Score = 15

	race.UpdateLevel(game)

	expectedLevel := 4 // 15 / 5 + 1
	if game.Level != expectedLevel {
		t.Errorf("Expected Level to be %d, got %d", expectedLevel, game.Level)
	}

	expectedTimeStep := int64(200 - ((expectedLevel - 1) * 17))
	if game.TimeStep != expectedTimeStep {
		t.Errorf("Expected TimeStep to be %d, got %d", expectedTimeStep, game.TimeStep)
	}
}

func TestCheckForCollision(t *testing.T) {
	game := race.NewCarRacingGame()
	game.Player.Lane = 1
	game.Player.Y = 5
	game.RivalCars[0].Lane = 1
	game.RivalCars[0].Y = 5

	race.CheckForCollision(game)

	if game.State != race.KCollide {
		t.Errorf("Expected game.State to be KCollide, got %d", game.State)
	}
}

func TestNoCollision(t *testing.T) {
	game := race.NewCarRacingGame()
	game.Player.Lane = 1
	game.Player.Y = 5
	game.RivalCars[0].Lane = 0
	game.RivalCars[0].Y = 5

	race.CheckForCollision(game)

	if game.State == race.KCollide {
		t.Errorf("Expected game.State to not be KCollide")
	}
}
