import { applyRootStyles } from './src/utils.js';
import { GameBoard } from './src/game-board.js';
import { rootStyles, keyCodes } from './src/config.js';

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
    return await fetch(url + ":" + port + "/api/actions", { method: 'POST',
        body: JSON.stringify({"action": "" + direction})});
}

const Update = async () => {
    const response =await  fetch('http://0.0.0.0:8080/api/parameters', { method: 'GET' })
    var json = await response.json();
    console.log(json)
    for (let i = 0; i < json.board.height; i++) {
        for (let j = 0; j < json.board.width; j++) {
            if (json.board.board[i][j].is_set) {
                gameBoard.enableTile(i, j)
            } else {
                gameBoard.disableTile(i, j)
            }
        }
    }
}

document.addEventListener('keydown', async function (event) {
    if (keyCodes.enter.includes(event.code)) {
        const response = await fetch('http://0.0.0.0:8080/api/games/1', { method: 'POST' });
        await MoveSide(6);
        const data = await response.text();
        console.log(data);
        Update()
    }
    if (keyCodes.up.includes(event.code)) {
        const response = MoveSide(1);
        console.log('up');
        Update()
    }
    if (keyCodes.right.includes(event.code)) {
        const response = MoveSide(4);
        console.log('right');
        Update()
    }
    if (keyCodes.down.includes(event.code)) {
        const response = MoveSide(2);
        console.log('down');
        Update()
    }
    if (keyCodes.left.includes(event.code)) {
        const response = MoveSide(3);
        console.log('left');
        Update()
    }
});
