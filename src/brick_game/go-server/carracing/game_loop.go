package carracing

import (
	"fmt"
)

var Parameters *CarRacingGame

// SignalAction processes a signal and performs the corresponding action
func SignalAction(signal Signal, game *CarRacingGame) {
	switch game.State {
	case KStart:
		if signal == KSignalSpawn {
			fmt.Println("Game Starting...")
			game.State = KSpawn
		}
	case KSpawn:
		if signal == KSignalSpawn {
			ActionSpawn(game)
			PrintTrack(game)
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
		}
		PrintTrack(game)
		HandleRivalCars(game)
		CheckForCollision(game)
		//if (*p_parameters->t_state_ == kMoving) {
		//    long long time_step = GetTimeStepMS(p_parameters->t_game_status_);
		//    if (time_in_ms - *p_parameters->t_last_moved_time_ > time_step) {
		//      *p_parameters->t_last_moved_time_ = time_in_ms;
		//      ActionMoveDown(p_parameters);
		//    }
		//  }
	case KCollide:
		ActionCollide(game)
	case KGameOver:
		ActionGameOver(game)
	}
}

//func SignalAction(game *CarRacingGame, signal Signal) {
//	switch game.State {
//	case KMoving:
//		switch signal {
//		case KSignalMoveLeft:
//			ActionMoveLeft(game)
//		case KSignalMoveRight:
//			ActionMoveRight(game)
//		case KSignalMoveUp:
//			ActionMoveUp(game)
//		case KSignalMoveDown:
//			ActionMoveDown(game)
//		}
//		HandleRivalCars(game)
//		CheckForCollision(game)
//	}
//}

//func GameLoop(game *CarRacingGame) {
//	for game.State != KExitState {
//		SignalAction(game, signal)
//		time.Sleep(200 * time.Millisecond) // Control game speed
//	}
//}
