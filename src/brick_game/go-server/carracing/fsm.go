package carracing

var fsmTable = [7][8]func(game *CarRacingGame){
	{nil, nil, nil, nil, nil, ActionExitState, ActionSpawn, nil},                                                                             // kStart state
	{ActionSpawn, ActionSpawn, ActionSpawn, ActionSpawn, ActionSpawn, ActionSpawn, ActionSpawn, nil},                                         // KSpawn state
	{nil, ActionMoveUp, ActionMoveDown, ActionMoveLeft, ActionMoveRight, ActionExitState, nil, ActionPause},                                  // KMoving state
	{ActionCollide, ActionCollide, ActionCollide, ActionCollide, ActionCollide, ActionCollide, ActionCollide, ActionCollide},                 // KCollide state
	{ActionGameOver, ActionGameOver, ActionGameOver, ActionGameOver, ActionGameOver, ActionGameOver, ActionSpawn, ActionCollide},             // KGameOver state
	{ActionExitState, ActionExitState, ActionExitState, ActionExitState, ActionExitState, ActionExitState, ActionExitState, ActionExitState}, // KExitState
	{nil, nil, nil, nil, nil, nil, nil, ActionPause},                                                                                         // KPause state
}
