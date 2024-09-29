package main

type GameInfo struct {
	ID   int    `json:"id"`
	Name string `json:"name"`
}

type GameState struct {
	Speed     int  `json:"speed"`
	Score     int  `json:"score"`
	HighScore int  `json:"high_score"`
	Level     int  `json:"level"`
	Pause     bool `json:"pause"`
}

type UserAction struct {
	ActionID int  `json:"action_id"`
	Hold     bool `json:"hold"`
}

func main() {

}
