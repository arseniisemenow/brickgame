package main

import "C"
import (
	"github.com/gin-gonic/gin"
	"log"
	"net/http"
)

// #cgo CFLAGS: -g -Wall
// #cgo LDFLAGS: -lstdc++
// #include <stdlib.h>
// #include legacy_include/controller.hpp"
import "C"

//#include "../tetris/fsm/fsm.h"

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
	params := C.struct_Parameters{}
	log.Println("params: ", params.t_player_.x_)

	r := gin.Default()

	r.GET("/api/games", func(c *gin.Context) {
		games := []GameInfo{
			{ID: 1, Name: "Tetris"},
			{ID: 2, Name: "Snake"},
			{ID: 3, Name: "Car Racing"},
		}
		c.JSON(http.StatusOK, gin.H{"games": games})
	})

	var activeGameID *int // Tracks the currently active game ID

	//if *activeGameID == 1 { //tetris
	//
	//} else if *activeGameID == 2 { // snake
	//
	//} else if *activeGameID == 3 { // racing
	//
	//}

	r.POST("/api/games/:gameId", func(c *gin.Context) {
		gameID := c.Param("gameId")

		// Convert gameID to int and check
		if gameID == "1" {
			if activeGameID != nil {
				c.JSON(http.StatusConflict, gin.H{"message": "Another game is already running"})
				return
			}
			activeGameID = new(int)
			*activeGameID = 1
			c.String(http.StatusOK, "Tetris game started")
		} else if gameID == "2" {
			if activeGameID != nil {
				c.JSON(http.StatusConflict, gin.H{"message": "Another game is already running"})
				return
			}
			activeGameID = new(int)
			*activeGameID = 2
			c.String(http.StatusOK, "Snake game started")
		} else if gameID == "3" {
			if activeGameID != nil {
				c.JSON(http.StatusConflict, gin.H{"message": "Another game is already running"})
				return
			}
			activeGameID = new(int)
			*activeGameID = 3
			c.String(http.StatusOK, "Car Racing game started")
		} else {
			c.JSON(http.StatusNotFound, gin.H{"message": "Game not found"})
		}
	})

	r.POST("/api/actions", func(c *gin.Context) {
		var action UserAction
		if err := c.ShouldBindJSON(&action); err != nil {
			c.JSON(http.StatusBadRequest, gin.H{"message": "Invalid action"})
			return
		}

		// Process action
		if activeGameID == nil {
			c.JSON(http.StatusBadRequest, gin.H{"message": "No game is currently running"})
			return
		}

		switch action.ActionID {
		case 1:
			// Accelerate
		case 2:
			// Brake
		case 3:
			// Turn Left/Right
		default:
			c.JSON(http.StatusBadRequest, gin.H{"message": "Unknown action"})
			return
		}

		c.String(http.StatusOK, "Action performed")
	})

	var gameState = GameState{
		Speed:     100,
		Score:     0,
		HighScore: 5000,
		Level:     1,
		Pause:     false,
	}

	r.GET("/api/state", func(c *gin.Context) {
		if activeGameID == nil {
			c.JSON(http.StatusBadRequest, gin.H{"message": "No game is currently running"})
			return
		}
		c.JSON(http.StatusOK, gameState)
	})

	r.Run(":8080") // Start the server
}
