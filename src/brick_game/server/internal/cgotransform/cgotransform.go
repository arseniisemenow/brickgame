package cgotransform

import "C"
import (
	con "myserver/internal/controller"
	t "myserver/types"
)

func GetBoardFromParameters() t.Board {
	board := t.Board{}
	tBoard := con.GetTBoard(con.Parameters)
	board.Height = con.BoardGetHeight(tBoard)
	board.Width = con.BoardGetWidth(tBoard)
	for i := 0; i < board.Height; i++ {
		for j := 0; j < board.Width; j++ {
			cell := con.BoardGetCellXY(tBoard, i, j)
			board.Board[i][j].X = con.CellGetX(cell)
			board.Board[i][j].Y = con.CellGetY(cell)
			board.Board[i][j].IsSet = con.CellGetIsSet(cell)
			board.Board[i][j].Color = con.CellGetColor(cell)
		}
	}
	return board
}

func GetTetrisPlayersFromParameters() (t.Player, t.Player, t.Player) {
	player := GetPlayer()
	predictPlayer := GetPredictPlayer()
	nextPlayer := GetNextPlayer()
	return player, predictPlayer, nextPlayer
}

func GetPlayer() t.Player {
	player := t.Player{}
	tPlayer := con.GetTPlayer(con.Parameters)
	player.X = con.PlayerGetX(tPlayer)
	player.Y = con.PlayerGetY(tPlayer)
	player.BlockType = con.PlayerGetBlockType(tPlayer)
	player.Direction = con.PlayerGetDirection(tPlayer)

	tPlayerBoard := con.PlayerGetPlayerBoard(tPlayer)

	for i := 0; i < 4; i++ {
		for j := 0; j < 4; j++ {
			tCell := con.PlayerBoardGetCellXY(tPlayerBoard, i, j)
			player.PlayerBoard.Board[i][j].X = con.CellGetX(tCell)
			player.PlayerBoard.Board[i][j].Y = con.CellGetY(tCell)
			player.PlayerBoard.Board[i][j].IsSet = con.CellGetIsSet(tCell)
			player.PlayerBoard.Board[i][j].Color = con.CellGetColor(tCell)
		}
	}
	return player
}
func GetNextPlayer() t.Player {
	player := t.Player{}
	tPlayer := con.GetTNextPlayer(con.Parameters)
	player.X = con.PlayerGetX(tPlayer)
	player.Y = con.PlayerGetY(tPlayer)
	player.BlockType = con.PlayerGetBlockType(tPlayer)
	player.Direction = con.PlayerGetDirection(tPlayer)

	tPlayerBoard := con.PlayerGetPlayerBoard(tPlayer)

	for i := 0; i < 4; i++ {
		for j := 0; j < 4; j++ {
			tCell := con.PlayerBoardGetCellXY(tPlayerBoard, i, j)
			player.PlayerBoard.Board[i][j].X = con.CellGetX(tCell)
			player.PlayerBoard.Board[i][j].Y = con.CellGetY(tCell)
			player.PlayerBoard.Board[i][j].IsSet = con.CellGetIsSet(tCell)
			player.PlayerBoard.Board[i][j].Color = con.CellGetColor(tCell)
		}
	}
	return player
}

func GetPredictPlayer() t.Player {
	player := t.Player{}
	tPlayer := con.GetTPredictPlayer(con.Parameters)
	player.X = con.PlayerGetX(tPlayer)
	player.Y = con.PlayerGetY(tPlayer)
	player.BlockType = con.PlayerGetBlockType(tPlayer)
	player.Direction = con.PlayerGetDirection(tPlayer)

	tPlayerBoard := con.PlayerGetPlayerBoard(tPlayer)

	for i := 0; i < 4; i++ {
		for j := 0; j < 4; j++ {
			tCell := con.PlayerBoardGetCellXY(tPlayerBoard, i, j)
			player.PlayerBoard.Board[i][j].X = con.CellGetX(tCell)
			player.PlayerBoard.Board[i][j].Y = con.CellGetY(tCell)
			player.PlayerBoard.Board[i][j].IsSet = con.CellGetIsSet(tCell)
			player.PlayerBoard.Board[i][j].Color = con.CellGetColor(tCell)
		}
	}
	return player
}

func GetSnakePlayerFromParameters() t.Player {
	player := t.Player{}
	sPlayer := con.GetSPlayer(con.Parameters)
	player.X = con.PlayerGetX(sPlayer)
	player.Y = con.PlayerGetY(sPlayer)
	player.BlockType = con.PlayerGetBlockType(sPlayer)
	player.SnakeLength = con.PlayerGetSnakeLength(sPlayer)
	player.Direction = con.PlayerGetDirection(sPlayer)
	sFruit := con.GetSFruit(con.Parameters)
	player.Fruit.X = con.CellGetX(sFruit)
	player.Fruit.Y = con.CellGetY(sFruit)
	player.Fruit.IsSet = con.CellGetIsSet(sFruit)
	player.Fruit.Color = con.CellGetColor(sFruit)

	for i := 0; i < 200; i++ {
		sCell := con.PlayerGetSnakeBodyIndex(sPlayer, i)
		player.SnakeBody.Body[i].X = con.CellGetX(sCell)
		player.SnakeBody.Body[i].Y = con.CellGetY(sCell)
		player.SnakeBody.Body[i].IsSet = con.CellGetIsSet(sCell)
		player.SnakeBody.Body[i].Color = con.CellGetColor(sCell)
	}
	return player
}

func GetGameStates() (t.GameStatus, t.GameStatus) {
	tetrisGameStatus := t.GameStatus{}
	tGameStatus := con.GetTGameStatus(con.Parameters)
	tetrisGameStatus.Score = con.GameStateGetScore(tGameStatus)
	tetrisGameStatus.Level = con.GameStateGetLevel(tGameStatus)

	snakeGameStatus := t.GameStatus{}
	sGameStatus := con.GetSGameStatus(con.Parameters)

	snakeGameStatus.Score = con.GameStateGetScore(sGameStatus)
	snakeGameStatus.Level = con.GameStateGetLevel(sGameStatus)
	return tetrisGameStatus, snakeGameStatus
}

func GetRecords() (t.Records, t.Records) {
	tetrisRecords := t.Records{}
	tRecords := con.GetTRecords(con.Parameters)
	for i := 0; i < 5; i++ {
		tRecord := con.RecordGetRecordIndex(tRecords, i)
		cLikeString := con.RecordGetName(tRecord)
		tetrisRecords.Records[i].Name = C.GoString((*C.char)(cLikeString))
		tetrisRecords.Records[i].Score = con.RecordGetScore(tRecord)
		tetrisRecords.Records[i].IsCurrentPlayer = con.RecordGetIsCurrentPlayer(tRecord)
	}
	snakeRecords := t.Records{}
	sRecords := con.GetSRecords(con.Parameters)
	for i := 0; i < 5; i++ {
		sRecord := con.RecordGetRecordIndex(sRecords, i)
		snakeRecords.Records[i].Name = C.GoString((*C.char)(con.RecordGetName(sRecord)))
		snakeRecords.Records[i].Score = con.RecordGetScore(sRecord)
		snakeRecords.Records[i].IsCurrentPlayer = con.RecordGetIsCurrentPlayer(sRecord)
	}
	return tetrisRecords, snakeRecords
}
