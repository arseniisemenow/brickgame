package cmd

import (
	"github.com/gin-gonic/gin"
	h "myserver/handlers"
	"myserver/internal/dbhandler"
	"net/http"
)

func SetupRouter(dbHandler *dbhandler.DBHandler) *gin.Engine {
	r := gin.Default()

	r.Static("/static", "./../../gui/web_gui/static")
	// CORS middleware
	r.Use(func(c *gin.Context) {
		c.Header("Access-Control-Allow-Origin", "*")
		c.Header("Access-Control-Allow-Methods", "GET, POST, OPTIONS")
		c.Header("Access-Control-Allow-Headers", "Content-Type")

		c.Header("Cache-Control", "no-cache, no-store, must-revalidate")
		c.Header("Pragma", "no-cache")
		c.Header("Expires", "0")

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
	r.GET("/api/parameters", h.HandlerGetParameters(activeGameID, dbHandler))

	return r
}
