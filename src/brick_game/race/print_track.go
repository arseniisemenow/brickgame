package race

import "fmt"

func PrintTrack(game *CarRacingGame) {
	track := make([][]rune, game.TrackHeight)
	for i := range track {
		track[i] = []rune{'.', '.', '.'}
	}

	track[game.Player.Y][game.Player.Lane] = 'P'

	for _, car := range game.RivalCars {
		if car.Y >= 0 && car.Y < game.TrackHeight {
			track[car.Y][car.Lane] = 'R'
		}
	}

	for _, row := range track {
		fmt.Println(string(row))
	}
	fmt.Println()
}
