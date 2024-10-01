package carracing

import "math/rand"

func MoveCarUpward(car *Car, y int) {
	car.Lane = rand.Intn(3)
	car.Y = y
}

func HandleRivalCars(game *CarRacingGame) {
	for i := range game.RivalCars {
		game.RivalCars[i].Y++
		if game.RivalCars[i].Y >= game.TrackHeight {
			MoveCarUpward(&game.RivalCars[i], 0)
		}
	}
}

func CheckForCollision(game *CarRacingGame) {
	for _, car := range game.RivalCars {
		if car.Lane == game.Player.Lane && car.Y == game.Player.Y {
			game.State = KCollide // Trigger collision
			return
		}
	}
}
