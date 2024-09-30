import {applyRootStyles} from '../utils.js';
import {GameBoard} from '../game-board.js';
import {NextPlayerBoard} from "../next-player-board.js";
import {SidePanel} from "../side-panel.js";
import {StateInfo} from "../state-info.js";
import {FetchGameParameters, MakeAction, ResetBoard, SelectGame, STATE_TETRIS, STATE_SNAKE} from './game-utils.js';
import {keyCodes, rootStyles} from '../config.js';
import {UsernameInput} from "../username-input.js";

applyRootStyles(rootStyles);
const gameBoard = new GameBoard(document.querySelector('#game-board'));
const nextPlayerBoard = new NextPlayerBoard(document.querySelector('#next-player-board'));
const sidePanel = new SidePanel(document.querySelector('#side-panel'));
const usernameInput = new UsernameInput(document.querySelector('#username'));
const stateInfo = new StateInfo(document.querySelector('#state-info'));

function DrawRecords(json) {
    let records = json.records_tetris.records
    sidePanel.updateRecords(records)
    console.log("records", records)
}

function DrawPlayerBoard(player) {
    let playerPosX = player.x;
    let playerPosY = player.y;
    if (playerPosX === 4294967295) playerPosX = -1;
    if (playerPosX === 4294967294) playerPosX = -2;
    for (let row = 0; row < 4; ++row) {
        for (let col = 0; col < 4; ++col) {
            let printY = playerPosY + row;
            let printX = playerPosX + col;
            if (player.player_board.board[row][col].is_set) {
                let color = player.player_board.board[row][col].color
                gameBoard.enableTile(printY, printX, color)
            }
        }
    }
}


function DrawNextPlayerBoard(json) {
    for (let i = 0; i < 4; i++) {
        for (let j = 0; j < 4; j++) {
            nextPlayerBoard.disableTile(i, j)
        }
    }
    let player = json.next_player_tetris
    for (let row = 0; row < 4; ++row) {
        for (let col = 0; col < 4; ++col) {
            if (player.player_board.board[row][col].is_set) {
                let color = player.player_board.board[row][col].color
                nextPlayerBoard.enableTile(row, col, color)
            } else {
                nextPlayerBoard.disableTile(row, col)
            }
        }
    }
}

function ClearBoard(json) {
    ResetBoard(gameBoard, json.board.height, json.board.width);
}

function DrawBoard(json) {
    for (let i = 0; i < json.board.height; i++) {
        for (let j = 0; j < json.board.width; j++) {
            if (json.board.board[i][j].is_set) {
                let color = json.board.board[i][j].color
                gameBoard.enableTile(i, j, color)
            }
        }
    }
}

const Update = async () => {
    try {
        await MakeAction(0);
        const json = await FetchGameParameters();
        ClearBoard(json);
        DrawNextPlayerBoard(json);
        DrawPlayerBoard(json.predict_player_tetris);
        DrawPlayerBoard(json.player_tetris);
        DrawRecords(json)
        DrawBoard(json);
        // STATE_TETRIS = json.state_tetris
        stateInfo.Update(json.state_tetris)

        // if (*p_parameters->t_state_ != kStart &&
        //     *p_parameters->t_state_ != kPause) {
        //     PrintTetrisGame(p_parameters);
        // }
        // if (*p_parameters->t_state_ == kPause) {
        //     PrintPause();
        // }
        // if (*p_parameters->t_state_ == kGameOver) {
        //     GetPlayerName(p_parameters->t_username);
        //     PrintBegin();
        //     RemoveRecord(p_parameters->t_records_, "Unnamed",
        //         TETRIS_RECORDS_FILE_NAME);
        //     AddRecord(p_parameters->t_records_, p_parameters->t_username,
        //         p_parameters->t_game_status_->  score_, TETRIS_RECORDS_FILE_NAME);
        // }


    } catch (error) {
        console.error('Error updating the game board:', error);
    }
};

setInterval(await Update, 100);
document.addEventListener('keydown', async function (event) {
    if (keyCodes.enter.includes(event.code)) {
        await SelectGame(1) // snake
        const data = await response.text();
        console.log(data);
    }
    if (keyCodes.up.includes(event.code)) {
        const response = MakeAction(1);
    }
    if (keyCodes.right.includes(event.code)) {
        const response = MakeAction(4);
    }
    if (keyCodes.down.includes(event.code)) {
        const response = MakeAction(2);
    }
    if (keyCodes.left.includes(event.code)) {
        const response = MakeAction(3);
    } else {
        const response = MakeAction(0);
    }

    await Update();
});
