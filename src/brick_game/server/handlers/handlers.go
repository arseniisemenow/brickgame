package handlers

import (
	"github.com/arseniisemenow/race"
	"github.com/gin-gonic/gin"
	"log"
	"myserver/internal/cgotransform"
	con "myserver/internal/controller"
	"myserver/internal/dbhandler"
	t "myserver/types"
	"net/http"
	"strconv"
)

func HandlerGetParameters(activeGameID *int, dbHandler *dbhandler.DBHandler) func(c *gin.Context) {
	return func(c *gin.Context) {
		if *activeGameID == 0 {
			c.JSON(http.StatusBadRequest, gin.H{"message": "No game is currently running"})
			return
		}
		tState := con.GetTStateValue(con.Parameters)
		sState := con.GetSStateValue(con.Parameters)
		board := cgotransform.GetBoardFromParameters()
		tetrisPlayer, tetrisPredictPlayer, tetrisNextPlayer := cgotransform.GetTetrisPlayersFromParameters()
		snakePlayer := cgotransform.GetSnakePlayerFromParameters()
		tetrisRecords, snakeRecords := cgotransform.GetRecords()
		tetrisGameStatus, snakeGameStatus := cgotransform.GetGameStates()
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
			PlayerSnake:         snakePlayer,
			CarRacingParameters: *con.CarRacingParameters,
		}
		getCurrentRecord, err := dbHandler.GetRecord()
		if err != nil {
			log.Printf("dbHandler.GetRecord(): %s\n", err)
		}
		if con.CarRacingParameters.RecordsScore > getCurrentRecord.Score {
			err := dbHandler.StoreRecord(con.CarRacingParameters.RecordsScore)
			if err != nil {
				log.Printf("Store record error: {%d}: %s\n", con.CarRacingParameters.RecordsScore, err)
			}
		} else {
			parameters.CarRacingParameters.RecordsScore = getCurrentRecord.Score
		}
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
		} else if *activeGameID == 3 {
			race.SignalAction(race.Signal(signalNumber), con.CarRacingParameters)
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
		} else if gameID == "2" { // snake
			con.InitParametersSnake(con.Parameters)
			*activeGameID = 2
			c.String(http.StatusOK, "Snake game started")
		} else if gameID == "3" { // car racing
			con.CarRacingParameters.State = race.KStart
			con.CarRacingParameters.Score = 0
			*activeGameID = 3
			//todo: store
			c.String(http.StatusOK, "Car Racing game started")
		} else {
			c.JSON(http.StatusNotFound, gin.H{"message": "Game not found"})
		}
	}
}