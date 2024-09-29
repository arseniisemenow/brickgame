package types

type GameInfo struct {
	ID   int    `json:"id"`
	Name string `json:"name"`
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

//typedef struct {
//int x_;
//int y_;
//BlockType block_type_;
//PlayerBoard *board_;
//Cell *snake_body_;
//int snake_length_;
//Direction direction_;
//} Player;

type PlayerBoard struct {
	Board [4][4]Cell `json:"board"`
}
type SnakeBody struct {
	Body [200]Cell `json:"body"`
}
type Player struct {
	X           int         `json:"x"`
	Y           int         `json:"y"`
	BlockType   int         `json:"block_type"`
	PlayerBoard PlayerBoard `json:"player_board"`
	SnakeBody   SnakeBody   `json:"snake_body"`
	SnakeLength int         `json:"snake_length"`
	Direction   int         `json:"direction"`
}

type Parameters struct {
	State  int    `json:"state"`
	Board  Board  `json:"board"`
	Player Player `json:"player"`
}
