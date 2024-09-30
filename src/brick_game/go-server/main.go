package main

import "C"
import (
	"github.com/gin-gonic/gin"
	con "myserver/controller"
	h "myserver/handlers"
	"net/http"
)

func setupRouter() *gin.Engine {
	r := gin.Default()

	r.Static("/static", "./../../gui/web_gui/static")
	// CORS middleware
	r.Use(func(c *gin.Context) {
		c.Header("Access-Control-Allow-Origin", "*")
		c.Header("Access-Control-Allow-Methods", "GET, POST, OPTIONS")
		c.Header("Access-Control-Allow-Headers", "Content-Type")
		if c.Request.Method == "OPTIONS" {
			c.AbortWithStatus(http.StatusNoContent)
			return
		}
		c.Next()
	})

	var activeGameID = new(int)

	r.GET("/api/games", h.HandlerGetGames())
	r.POST("/api/games/:gameId", h.HandlerPostGames(activeGameID))
	r.POST("/api/actions", h.HandlerPostActions(activeGameID))
	r.GET("/api/parameters", h.HandlerGetParameters(activeGameID))

	return r
}

func main() {
	con.InitController()
	r := setupRouter()

	r.Run(":8080")
}
