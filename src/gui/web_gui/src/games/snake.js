import {applyRootStyles} from '../utils.js';
import {GameBoard} from '../game-board.js';
import {keyCodes, rootStyles} from '../config.js';

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

function DrawSnake(json) {
    let player = json.player_snake.snake_body.body
    let playerPosX = player[0].x;
    let playerPosY = player[0].y;
    console.log("playerPosX, playerPosY", playerPosX, playerPosY)

    gameBoard.enableTile(json.player_snake.fruit.y,json.player_snake.fruit.x, 3 )

    for (let snake_index = 0; snake_index < json.player_snake.snake_length; ++snake_index) {
            gameBoard.enableTile(json.player_snake.snake_body.body[snake_index].y,
                json.player_snake.snake_body.body[snake_index].x, 2) // Green color
        }

//     for (let y = 0; y < json.board.height; y++) {
//         for (let x = 0; x < json.board.width; x++) {
//             let is_snake_body = false
//
//             // for (let snake_index = 0; snake_index < json.player_snake.snake_length; ++snake_index) {
//             //     if (json.player_snake.snake_body.body[snake_index].x == x &&
//             //     json.player_snake.snake_body.body[snake_index].y == y){
//             //         gameBoard.enableTile(y, x, 2) // Green       color
//             //
//             //         is_snake_body = true;
//             //     break;
//             //     }
//             // }
//
//
//             if (!is_snake_body && x == json.player_snake.fruit.x &&
//                 y == json.player_snake.fruit.y) {
//                 gameBoard.enableTile(y, x, 3) // Red color
//             }
//             if (is_snake_body && x == json.player_snake.fruit.x &&
//                 y == json.player_snake.fruit.y) {
//                 gameBoard.enableTile(y, x, 4) // Another Green color
//             }
//
// //         if (is_snake_body && x == p_parameters->s_fruit_->x_ &&
// //             y == p_parameters->s_fruit_->y_) {
// //             attron(COLOR_PAIR(PREDICT_COLOR_PAIR_INDEX));
// //             mvprintw(y + BOARDS_BEGIN + 1, x + BOARDS_BEGIN + 1, "*");
// //             attroff(COLOR_PAIR(PREDICT_COLOR_PAIR_INDEX));
// //         }
// //         }
//         }
//     }
}

function ClearBoard(json) {
    for (let row = 0; row < 20; row++) {
        for (let col = 0; col < 10; col++) {
            gameBoard.disableTile(row, col)
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
        DrawSnake(json);
    // DrawBoard(json);
}

document.addEventListener('keydown', async function (event) {
    if (keyCodes.enter.includes(event.code)) {
        const response = await fetch('http://0.0.0.0:8080/api/games/2', {method: 'POST'});
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
