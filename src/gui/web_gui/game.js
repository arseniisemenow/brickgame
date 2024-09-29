import {applyRootStyles} from './src/utils.js';
import {GameBoard} from './src/game-board.js';
import {keyCodes, rootStyles} from './src/config.js';

applyRootStyles(rootStyles);
const gameBoard = new GameBoard(document.querySelector('#game-board'));

const $sidePanel = document.querySelector('#side-panel');

const url = "http://0.0.0.0"
const port = "8080"

const MoveCodeNone = 0
const MoveCodeUp = 1
const MoveCodeDown = 2
const MoveCodeLeft = 3
const MoveCodeRight = 4
const MoveCodeEnter = 5
const MoveCodeEscape = 6
const MoveCodePause = 7

const MoveSide = async (direction) => {
    return await fetch(url + ":" + port + "/api/actions", {
        method: 'POST',
        body: JSON.stringify({"action": "" + direction})
    });
}


// void PrintBlock(Player *p_player) {
//     int player_pos_x = p_player->x_;
//     int player_pos_y = p_player->y_;
//     const PlayerBoard *player_board = (const PlayerBoard *)p_player->board_;
//
//     for (int row_index = 0; row_index < PLAYER_BOARD_SIZE; ++row_index) {
//         for (int column_index = 0; column_index < PLAYER_BOARD_SIZE;
//         ++column_index) {
//             int print_y = player_pos_y + BOARDS_BEGIN + 1 + row_index;
//             int print_x = player_pos_x + BOARDS_BEGIN + 1 + column_index;
//             if (player_board->board_[row_index][column_index].is_set_) {
//                 int color = player_board->board_[row_index][column_index].color_;
//                 attron(COLOR_PAIR(kBlockColorPairsArray[color]));
//                 mvprintw(print_y, print_x, "F");
//                 attroff(COLOR_PAIR(kBlockColorPairsArray[color]));
//             }
//         }
//     }
// }
//


function DrawPlayerBoard(json) {
    let player = json.player
    let playerPosX = player.x;
    let playerPosY = player.y;
    console.log(playerPosX)
    if (playerPosX === 4294967295) playerPosX = -1;
    if (playerPosX === 4294967294) playerPosX = -2;
    for (let row = 0; row < 4; ++row) {
        for (let col = 0; col < 4; ++col) {
            let printY = playerPosY + row;
            let printX = playerPosX + col;
            if (player.player_board.board[row][col].is_set) {
                let color = player.player_board.board[row][col].color
                gameBoard.enableTile(printY, printX, color)
            } else {
                // gameBoard.enableTile(printY, printX)
            }
        }
    }
}

function ClearBoard(json) {
    for (let i = 0; i < json.board.height; i++) {
        for (let j = 0; j < json.board.width; j++) {
            gameBoard.disableTile(i, j)
        }
    }
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
    const response = await fetch('http://0.0.0.0:8080/api/parameters', {method: 'GET'})
    var json = await response.json();

    ClearBoard(json);
    DrawPlayerBoard(json);
    DrawBoard(json);
}

document.addEventListener('keydown', async function (event) {
    if (keyCodes.enter.includes(event.code)) {
        const response = await fetch('http://0.0.0.0:8080/api/games/1', {method: 'POST'});
        await MoveSide(6);
        const data = await response.text();
        console.log(data);
    }
    if (keyCodes.up.includes(event.code)) {
        const response = MoveSide(1);
    }
    if (keyCodes.right.includes(event.code)) {
        const response = MoveSide(4);
    }
    if (keyCodes.down.includes(event.code)) {
        const response = MoveSide(2);
    }
    if (keyCodes.left.includes(event.code)) {
        const response = MoveSide(3);
    }
    Update()
});
