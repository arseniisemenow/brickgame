package race

func ActionMoveUp(game *CarRacingGame) {
	if game.Player.Y > 0 {
		game.Player.Y--
	}
}

func ActionMoveDown(game *CarRacingGame) {
	if game.Player.Y < game.TrackHeight-1 {
		game.Player.Y++
	}
}

func ActionMoveLeft(game *CarRacingGame) {
	if game.Player.Lane > 0 {
		game.Player.Lane--
	}
}

func ActionMoveRight(game *CarRacingGame) {
	if game.Player.Lane < 2 {
		game.Player.Lane++
	}
}

func ActionSpawn(game *CarRacingGame) {
	game.Player.Y = game.TrackHeight - 1
	game.Player.Lane = 1
	for i := 0; i < 2; i++ {
		MoveObstacleCarUpward(&game.RivalCars[i], i*3)
	}
}

func ActionCollide(game *CarRacingGame) {
	game.State = KGameOver
}

func ActionGameOver(game *CarRacingGame) {
	game.Player = Car{Lane: 1, Y: game.TrackHeight - 1}
	game.State = KStart
}

func ActionExitState(game *CarRacingGame) {
	game.State = KExitState
}

func ActionPause(game *CarRacingGame) {
	game.State = KPause
}

func ActionUnPause(game *CarRacingGame) {
	game.State = KMoving
}
