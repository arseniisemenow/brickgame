package handlers

import (
	"github.com/gin-gonic/gin"
	"myserver/auxiliary"
	con "myserver/controller"
	t "myserver/types"
	"net/http"
)

func HandlerGetParameters(activeGameID *int) func(c *gin.Context) {
	return func(c *gin.Context) {
		if *activeGameID == 0 {
			c.JSON(http.StatusBadRequest, gin.H{"message": "No game is currently running"})
			return
		}
		tState := con.GetTStateValue(con.Parameters)
		board := auxiliary.GetBoardFromParameters()
		player := auxiliary.GetPlayerFromParameters()
		parameters := t.Parameters{State: tState, Board: board, Player: player}
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
		switch body.Action {
		case "0": //kSignalNone
			con.SignalAction(0, con.Parameters)
		case "1": //kSignalMoveUp
			con.SignalAction(1, con.Parameters)
		case "2": //kSignalMoveDown
			con.SignalAction(2, con.Parameters)
		case "3": //kSignalMoveLeft
			con.SignalAction(3, con.Parameters)
		case "4": //kSignalMoveRight
			con.SignalAction(4, con.Parameters)
		case "5": //kSignalEscapeButton
			con.SignalAction(5, con.Parameters)
		case "6": //kSignalEnterButton
			con.SignalAction(6, con.Parameters)
		case "7": //kSignalPauseButton
			con.SignalAction(7, con.Parameters)
		default:
			c.JSON(http.StatusBadRequest, gin.H{"message": "Unknown action"})
			return
		}

		c.String(http.StatusOK, "Action performed")
	}
}

func HandlerPostGames(activeGameID *int) func(c *gin.Context) {
	return func(c *gin.Context) {
		gameID := c.Param("gameId")

		if gameID == "1" { // tetris
			if *activeGameID != 0 {
				c.JSON(http.StatusConflict, gin.H{"message": "Another game is already running"})
				return
			}
			*activeGameID = 1
			con.InitParametersTetris(con.Parameters)
			c.String(http.StatusOK, "Tetris game started")
		} else if gameID == "2" {
			if *activeGameID != 0 {
				c.JSON(http.StatusConflict, gin.H{"message": "Another game is already running"})
				return
			}
			*activeGameID = 2
			c.String(http.StatusOK, "Snake game started")
		} else if gameID == "3" {
			if *activeGameID != 0 {
				c.JSON(http.StatusConflict, gin.H{"message": "Another game is already running"})
				return
			}
			*activeGameID = 3
			c.String(http.StatusOK, "Car Racing game started")
		} else {
			c.JSON(http.StatusNotFound, gin.H{"message": "Game not found"})
		}
	}
}
