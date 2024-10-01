package carracing

import (
	"fmt"
	"time"
)

func GameLoop(game *CarRacingGame) {
	for game.State != KExitState {
		switch game.State {
		case KStart:
			fmt.Println("Game Starting...")
			game.State = KSpawn // Transition to spawning rival cars
		case KSpawn:
			ActionSpawn(game)
			PrintTrack(game)
			game.State = KMoving
		case KMoving:
			PrintTrack(game)
			HandleRivalCars(game)
			CheckForCollision(game)
		case KCollide:
			ActionCollide(game)
		case KGameOver:
			ActionGameOver(game)
		}
		time.Sleep(200 * time.Millisecond) // Control game speed
	}
}
