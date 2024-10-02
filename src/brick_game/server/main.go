package main

import (
	"log"
	"myserver/cmd"
	con "myserver/internal/controller"
	"myserver/internal/dbhandler"
)

func main() {
	con.InitController()
	connectionString := "host=localhost user=carracinguser password=carracingpassword dbname=carracingdb port=5435 sslmode=disable TimeZone=Asia/Shanghai"

	dbHandler, err := dbhandler.NewDBHandler(connectionString)
	if err != nil {
		log.Fatalf("Failed to connect to database: %v", err)
	}
	r := cmd.SetupRouter(dbHandler)

	err = r.Run(":8080")
	if err != nil {
		log.Fatalf("Server is not started: %v\n", err)
	}
}
