package race

import (
	"time"
)

func SignalAction(signal Signal, game *CarRacingGame) {
	switch game.State {
	case KStart:
		if signal == KSignalSpawn {
			game.State = KSpawn
		}
		if signal == KSignalExit {
			ActionExitState(game)
		}
	case KSpawn:
		if signal == KSignalSpawn {
			ActionSpawn(game)
			game.State = KMoving
		}
	case KMoving:
		switch signal {
		case KSignalMoveLeft:
			ActionMoveLeft(game)
		case KSignalMoveRight:
			ActionMoveRight(game)
		case KSignalMoveUp:
			ActionMoveUp(game)
		case KSignalMoveDown:
			ActionMoveDown(game)
		case KSignalPause:
			ActionPause(game)
		case KSignalExit:
			ActionExitState(game)
		}
		HandleTime(game)
	case KCollide:
		ActionCollide(game)
	case KPause:
		switch signal {
		case KSignalPause:
			ActionUnPause(game)
		}
	case KGameOver:
		ActionGameOver(game)
	}
}

func HandleTime(game *CarRacingGame) {
	currentTime := time.Now().UnixMilli()

	if currentTime-game.LastMovedTime > game.TimeStep {
		game.LastMovedTime = currentTime
		HandleRivalCars(game)
	}
	CheckForCollision(game)
}
