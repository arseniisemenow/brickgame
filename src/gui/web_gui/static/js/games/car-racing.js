import {applyRootStyles} from '../utils.js';
import {GameBoard} from '../game-board.js';
import {SidePanel} from "../side-panel.js";
import {StateInfo} from "../state-info.js";
import {FetchGameParameters, MakeAction, ResetBoard, SelectGame} from './game-utils.js';
import {keyCodes, rootStyles} from '../config.js';

applyRootStyles(rootStyles);
const gameBoard = new GameBoard(document.querySelector('#game-board'));
const sidePanel = new SidePanel(document.querySelector('#side-panel'));
const stateInfo = new StateInfo(document.querySelector('#state-info'));

function DrawRecords(json) {
    // let records = json.records_tetris.records
    let records = [
        {
            name: "",
            score: 0,
            is_current_player: 0
        },
        {
            name: "",
            score: 0,
            is_current_player: 0
        },
        {
            name: "",
            score: 0,
            is_current_player: 0
        },
        {
            name: "",
            score: 0,
            is_current_player: 0
        },
        {
            name: "",
            score: 0,
            is_current_player: 0
        }
    ];
    records[0].name = "Unnamed"
    records[0].score = json.car_racing_parameters.record_score
    sidePanel.updateRecords(records)
    sidePanel.updateScore(json.car_racing_parameters.score)
    sidePanel.updateLevel(json.car_racing_parameters.level)
}

function ClearBoard(json) {
    ResetBoard(gameBoard, json.car_racing_parameters.track_height, 10);
}

const DrawCar = (y, lane, color) => {
    lane *= 3
    gameBoard.enableTile(y, lane, color)
    gameBoard.enableTile(y, lane + 1, color)
    gameBoard.enableTile(y, lane + 2, color)
    gameBoard.enableTile(y, lane + 3, color)

    gameBoard.enableTile(y - 2, lane, color)
    gameBoard.enableTile(y - 2, lane + 1, color)
    gameBoard.enableTile(y - 2, lane + 2, color)
    gameBoard.enableTile(y - 2, lane + 3, color)

    gameBoard.enableTile(y - 1, lane + 1, color)
    gameBoard.enableTile(y - 1, lane + 2, color)

    gameBoard.enableTile(y - 3, lane + 1, color)
    gameBoard.enableTile(y - 3, lane + 2, color)

}

function DrawBoard(json) {
    let lane = json.car_racing_parameters.player_car_racing.lane
    let y = json.car_racing_parameters.player_car_racing.y
    DrawCar(y, lane, 0)

    for (let i = 0; i < 2; i++) {
        lane = json.car_racing_parameters.rival_cars[i].lane
        y = json.car_racing_parameters.rival_cars[i].y
        DrawCar(y, lane, 1)
    }
}

const Update = async () => {
    try {
        await MakeAction(0);
        const json = await FetchGameParameters();
        ClearBoard(json);
        DrawRecords(json);
        stateInfo.Update(json.car_racing_parameters.state_car_racing)
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
