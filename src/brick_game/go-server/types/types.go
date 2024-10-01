package types

import "myserver/carracing"

type GameInfo struct {
	ID   int    `json:"id"`
	Name string `json:"name"`
}

type GameStatus struct {
	Score int `json:"score"`
	Level int `json:"level"`
}

type Cell struct {
	Color int `json:"color"`
	IsSet int `json:"is_set"`
	X     int `json:"x"`
	Y     int `json:"y"`
}

type Board struct {
	Height int          `json:"height"`
	Width  int          `json:"width"`
	Board  [20][10]Cell `json:"board"`
}

type PlayerBoard struct {
	Board [4][4]Cell `json:"board"`
}
type SnakeBody struct {
	Body [200]Cell `json:"body"`
}
type Record struct {
	Name            string `json:"name"`
	Score           int    `json:"score"`
	IsCurrentPlayer int    `json:"is_current_player"`
}
type Records struct {
	Records [5]Record `json:"records"`
}
type Player struct {
	X           int         `json:"x"`
	Y           int         `json:"y"`
	BlockType   int         `json:"block_type"`
	PlayerBoard PlayerBoard `json:"player_board"`
	SnakeBody   SnakeBody   `json:"snake_body"`
	SnakeLength int         `json:"snake_length"`
	Direction   int         `json:"direction"`
	Fruit       Cell        `json:"fruit"`
}

type Parameters struct {
	StateTetris         int                     `json:"state_tetris"`
	StateSnake          int                     `json:"state_snake"`
	GameStatusTetris    GameStatus              `json:"game_status_tetris"`
	GameStatusSnake     GameStatus              `json:"game_status_snake"`
	Board               Board                   `json:"board"`
	PlayerTetris        Player                  `json:"player_tetris"`
	PredictPlayerTetris Player                  `json:"predict_player_tetris"`
	NextPlayerTetris    Player                  `json:"next_player_tetris"`
	PlayerSnake         Player                  `json:"player_snake"`
	RecordsTetris       Records                 `json:"records_tetris"`
	RecordsSnake        Records                 `json:"records_snake"`
	CarRacingParameters carracing.CarRacingGame `json:"car_racing_parameters"`
}
