import {applyRootStyles} from '../utils.js';
import {GameBoard} from '../game-board.js';
import {SidePanel} from '../side-panel.js';
import {keyCodes, rootStyles} from '../config.js';
import {FetchGameParameters, PORT, ResetBoard, SelectGame, URL} from "./game-utils.js";
import {UsernameInput} from "../username-input.js";
import {StateInfo} from "../state-info.js";


applyRootStyles(rootStyles);
const gameBoard = new GameBoard(document.querySelector('#game-board'));
const sidePanel = new SidePanel(document.querySelector('#side-panel'));
const $sidePanel = document.querySelector('#side-panel');
const stateInfo = new StateInfo(document.querySelector('#state-info'));

const usernameInput = new UsernameInput(document.querySelector('#username'));

const MakeAction = async (direction) => {
    return await fetch(URL + ":" + PORT + "/api/actions", {
        method: 'POST',
        body: JSON.stringify({"action": "" + direction})
    });
}

function DrawSnake(json) {
    let player = json.player_snake.snake_body.body

    let fruit_row = json.player_snake.fruit.y;
    let fruit_col = json.player_snake.fruit.x;
    gameBoard.enableTile(fruit_row, fruit_col, 0)

    for (let snake_index = 0; snake_index < json.player_snake.snake_length; ++snake_index) {
        let snake_row = json.player_snake.snake_body.body[snake_index].y;
        let snake_col = json.player_snake.snake_body.body[snake_index].x;
        if (snake_row === fruit_row &&
            snake_col === fruit_col) {
            gameBoard.enableTile(snake_row,
                snake_col, 8)
        } else {
            gameBoard.enableTile(snake_row,
                snake_col, 4)
        }
    }
}

function DrawRecords(json) {
    let records = json.records_snake.records
    sidePanel.updateRecords(records)
    sidePanel.updateScore(json.game_status_snake.score)
    sidePanel.updateLevel(json.game_status_snake.level)
    console.log("records", records)
}

function ClearBoard() {
    ResetBoard(gameBoard, 20, 10);
}


const Update = async () => {
    try {
        await MakeAction(0);
        const json = await FetchGameParameters();
        try {
            ClearBoard();
            DrawSnake(json);
            DrawRecords(json);
        } catch (e) {
            console.log(e)
        }

        stateInfo.Update(json.state_snake)
    } catch (error) {
        console.error('Error updating the game board:', error);
    }
};

setInterval(await Update, 200);


document.addEventListener('keydown', async function (event) {
    if (keyCodes.enter.includes(event.code)) {
        await SelectGame(2) // snake
        const data = await response.text();
        console.log(data);
    } else if (keyCodes.up.includes(event.code)) {
        const response = MakeAction(1);
    } else if (keyCodes.right.includes(event.code)) {
        const response = MakeAction(4);
    } else if (keyCodes.down.includes(event.code)) {
        const response = MakeAction(2);
    } else if (keyCodes.left.includes(event.code)) {
        const response = MakeAction(3);
    } else if (keyCodes.pause.includes(event.code)) {
        const response = MakeAction(7);
    } else {
        const response = MakeAction(0);
    }

    await Update();
});