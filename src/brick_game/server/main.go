package main

import "C"
import (
	"github.com/gin-gonic/gin"
	"log"
	con "myserver/controller"
	"myserver/dbhandler"
	h "myserver/handlers"
	"net/http"
)

func setupRouter(dbHandler *dbhandler.DBHandler) *gin.Engine {
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

func main() {
	con.InitController()

	connectionString := "host=localhost user=carracinguser password=carracingpassword dbname=carracingdb port=5435 sslmode=disable TimeZone=Asia/Shanghai"

	dbHandler, err := dbhandler.NewDBHandler(connectionString)
	if err != nil {
		log.Fatalf("Failed to connect to database: %v", err)
	}
	r := setupRouter(dbHandler)

	r.Run(":8080")
}
