    import {applyRootStyles} from '../utils.js';
    import {GameBoard} from '../game-board.js';
    import {keyCodes, rootStyles} from '../config.js';
    import {FetchGameParameters, URL, PORT, ResetBoard, SelectGame} from "./game-utils.js";

    applyRootStyles(rootStyles);
    const gameBoard = new GameBoard(document.querySelector('#game-board'));

    const $sidePanel = document.querySelector('#side-panel');

    const MakeAction = async (direction) => {
        return await fetch(URL + ":" + PORT + "/api/actions", {
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

    function ClearBoard() {
        ResetBoard(gameBoard, 20, 10);
    }


    const Update = async () => {
        try {
            await MakeAction(0);
            const json = await FetchGameParameters();
            ClearBoard();
            DrawSnake(json);
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