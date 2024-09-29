package auxiliary

import (
	con "myserver/controller"
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

func GetPlayerFromParameters() t.Player {
	player := t.Player{}
	tPlayer := con.GetTPlayer(con.Parameters)
	player.X = con.PlayerGetX(tPlayer)
	player.Y = con.PlayerGetY(tPlayer)
	player.BlockType = con.PlayerGetBlockType(tPlayer)
	player.SnakeLength = con.PlayerGetSnakeLength(tPlayer)
	player.Direction = con.PlayerGetDirection(tPlayer)

	tPlayerBoard := con.PlayerGetPlayerBoard(tPlayer)

	for i := 0; i < 200; i++ {
		tCell := con.PlayerGetSnakeBodyIndex(tPlayer, i)
		player.SnakeBody.Body[i].X = con.CellGetX(tCell)
		player.SnakeBody.Body[i].Y = con.CellGetY(tCell)
		player.SnakeBody.Body[i].IsSet = con.CellGetIsSet(tCell)
		player.SnakeBody.Body[i].Color = con.CellGetColor(tCell)
	}

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
