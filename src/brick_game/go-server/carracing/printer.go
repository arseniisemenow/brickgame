package carracing

import "fmt"

// Visual representation of the game track
func PrintTrack(game *CarRacingGame) {
	track := make([][]rune, game.TrackHeight)
	for i := range track {
		track[i] = []rune{'.', '.', '.'}
	}

	// Place the player's car on the track
	track[game.Player.Y][game.Player.Lane] = 'P'

	// Place rival cars on the track
	for _, car := range game.RivalCars {
		if car.Y >= 0 && car.Y < game.TrackHeight {
			track[car.Y][car.Lane] = 'R'
		}
	}

	// Print the track
	for _, row := range track {
		fmt.Println(string(row))
	}
	fmt.Println()
}
