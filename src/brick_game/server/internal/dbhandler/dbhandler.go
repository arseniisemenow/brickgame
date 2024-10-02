package dbhandler

import (
	"errors"
	"fmt"
	"gorm.io/driver/postgres"
	"gorm.io/gorm"
	"log"
)

type Record struct {
	Id    int `gorm:"id"`
	Score int `gorm:"column:score"`
}

type DBHandler struct {
	db *gorm.DB
}

func NewDBHandler(connectionString string) (*DBHandler, error) {
	db, err := gorm.Open(postgres.Open(connectionString), &gorm.Config{})
	if err != nil {
		return nil, err
	}

	err = db.AutoMigrate(&Record{})
	if err != nil {
		return nil, err
	}

	return &DBHandler{db: db}, nil
}

func (handler *DBHandler) StoreRecord(score int) error {
	record := Record{
		Id:    1,
		Score: score,
	}
	if err := handler.db.Save(&record).Error; err != nil {
		return err
	}
	log.Println("New record is stored:", record)
	return nil
}

func (handler *DBHandler) GetRecord() (Record, error) {
	var record Record

	if err := handler.db.First(&record, 1).Error; err != nil {
		if errors.Is(err, gorm.ErrRecordNotFound) {
			return Record{}, fmt.Errorf("Error Record Not Found")
		}
		return Record{}, err // Return the error if something went wrong
	}

	return record, nil
}
