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
const sidePanel = new SidePanel(document.querySelector('#side-panel'));
const stateInfo = new StateInfo(document.querySelector('#state-info'));

function DrawRecords(json) {
    let records = json.records_tetris.records
    sidePanel.updateRecords(records)
    sidePanel.updateScore(json.game_status_tetris.score)
    sidePanel.updateLevel(json.game_status_tetris.level)
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
    ResetBoard(gameBoard, json.car_racing_parameters.track_height, 10);
}

function DrawBoard(json) {
    console.log("DrawBoard", json.car_racing_parameters)
    let lane = json.car_racing_parameters.player_car_racing.lane
    let y = json.car_racing_parameters.player_car_racing.y
    gameBoard.enableTile(y, lane, 0)

    for (let i = 0; i < 2; i++) {
        lane = json.car_racing_parameters.rival_cars[i].lane
        y = json.car_racing_parameters.rival_cars[i].y
        gameBoard.enableTile(y, lane, 1)
    }
}

const Update = async () => {
    try {
        await MakeAction(0);
        const json = await FetchGameParameters();
        ClearBoard(json);
        stateInfo.Update(json.car_racing_parameters.state_car_racing)
        // console.log(json)
        DrawBoard(json)
    } catch (error) {
        console.error('Error updating the game board:', error);
    }
};

setInterval(await Update, 100);
document.addEventListener('keydown', async function (event) {
    if (keyCodes.enter.includes(event.code)) {
        await SelectGame(3) // car racing
        await MakeAction(6);
        const data = await response.text();
        console.log(data);
    }
    else if (keyCodes.up.includes(event.code)) {
        const response = MakeAction(1);
    }
    else if (keyCodes.right.includes(event.code)) {
        const response = MakeAction(4);
    }
    else if (keyCodes.down.includes(event.code)) {
        const response = MakeAction(2);
    }
    else if (keyCodes.left.includes(event.code)) {
        const response = MakeAction(3);
    }
    else if (keyCodes.pause.includes(event.code)) {
        const response = MakeAction(7);
    } else {
        const response = MakeAction(0);
    }

    await Update();
});
