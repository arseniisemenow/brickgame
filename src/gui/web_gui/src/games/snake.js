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

    const MakeAction = async (direction) => {
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

        gameBoard.enableTile(json.player_snake.fruit.y, json.player_snake.fruit.x, 0)

        for (let snake_index = 0; snake_index < json.player_snake.snake_length; ++snake_index) {
            gameBoard.enableTile(json.player_snake.snake_body.body[snake_index].y,
                json.player_snake.snake_body.body[snake_index].x, 4) // Green color
        }
    }
    function ClearBoard(json) {
        for (let row = 0; row < 20; row++) {
            for (let col = 0; col < 10; col++) {
                gameBoard.disableTile(row, col)
            }
        }
    }


    const Update = async () => {
        try {
            await   MakeAction(0);
            const response = await fetch(`${url}:${port}/api/parameters`, {method: 'GET'});
            const json = await response.json();

            ClearBoard();
            DrawSnake(json);
            // Uncomment if you want to draw the whole board
            // DrawBoard(json);
        } catch (error) {
            console.error('Error updating the game board:', error);
        }
    };

    setInterval(await Update, 200);

    document.addEventListener('keydown', async function (event) {
        if (keyCodes.enter.includes(event.code)) {
            const response = await fetch('http://0.0.0.0:8080/api/games/2', {method: 'POST'});
            await MakeAction(6);
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
        Update()
    });
