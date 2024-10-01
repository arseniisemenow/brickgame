package handlers

import (
	"github.com/gin-gonic/gin"
	"myserver/auxiliary"
	con "myserver/controller"
	t "myserver/types"
	"net/http"
	"strconv"
)

func HandlerGetParameters(activeGameID *int) func(c *gin.Context) {
	return func(c *gin.Context) {
		if *activeGameID == 0 {
			c.JSON(http.StatusBadRequest, gin.H{"message": "No game is currently running"})
			return
		}
		tState := con.GetTStateValue(con.Parameters)
		sState := con.GetSStateValue(con.Parameters)
		board := auxiliary.GetBoardFromParameters()
		tetrisPlayer, tetrisPredictPlayer, tetrisNextPlayer := auxiliary.GetTetrisPlayersFromParameters()
		snakePlayer := auxiliary.GetSnakePlayerFromParameters()
		tetrisRecords, snakeRecords := auxiliary.GetRecords()
		tetrisGameStatus, snakeGameStatus := auxiliary.GetGameStates()
		parameters := t.Parameters{
			RecordsTetris:       tetrisRecords,
			RecordsSnake:        snakeRecords,
			GameStatusTetris:    tetrisGameStatus,
			GameStatusSnake:     snakeGameStatus,
			StateTetris:         tState,
			StateSnake:          sState,
			Board:               board,
			PlayerTetris:        tetrisPlayer,
			PredictPlayerTetris: tetrisPredictPlayer,
			NextPlayerTetris:    tetrisNextPlayer,
			PlayerSnake:         snakePlayer}
		c.JSON(http.StatusOK, parameters)
	}
}

func HandlerGetGames() func(c *gin.Context) {
	return func(c *gin.Context) {
		games := []t.GameInfo{
			{ID: 1, Name: "Tetris"},
			{ID: 2, Name: "Snake"},
			{ID: 3, Name: "Car Racing"},
		}
		c.JSON(http.StatusOK, gin.H{"games": games})
	}
}

func HandlerPostActions(activeGameID *int) func(c *gin.Context) {
	return func(c *gin.Context) {
		body := struct {
			Action string `json:"action"`
		}{}
		if err := c.ShouldBindJSON(&body); err != nil {
			c.JSON(http.StatusBadRequest, gin.H{"message": "Invalid action"})
			return
		}

		// Process action
		if *activeGameID == 0 {
			c.JSON(http.StatusBadRequest, gin.H{"message": "No game is currently running"})
			return
		}

		signalNumber, _ := strconv.Atoi(body.Action)
		if signalNumber < 0 && signalNumber > 7 {
			c.JSON(http.StatusBadRequest, gin.H{"message": "Unknown action"})
			return
		}
		if *activeGameID == 1 {
			con.SignalAction(signalNumber, con.Parameters)

		} else if *activeGameID == 2 {
			con.ControllerSnake(signalNumber, con.Parameters)
		}

		c.String(http.StatusOK, "Action performed")
	}
}

func HandlerPostGames(activeGameID *int) func(c *gin.Context) {
	return func(c *gin.Context) {
		gameID := c.Param("gameId")

		if gameID == "1" { // tetris
			con.InitParametersTetris(con.Parameters)
			*activeGameID = 1
			c.String(http.StatusOK, "Tetris game started")
		} else if gameID == "2" {
			con.InitParametersSnake(con.Parameters)
			*activeGameID = 2
			c.String(http.StatusOK, "Snake game started")
		} else if gameID == "3" {
			*activeGameID = 3
			c.String(http.StatusOK, "Car Racing game started")
		} else {
			c.JSON(http.StatusNotFound, gin.H{"message": "Game not found"})
		}
	}
}
