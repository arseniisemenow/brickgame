import { GAME_BOARD_WIDTH, GAME_BOARD_HEIGHT, kColorArray } from './config.js';

export class GameBoard {
    constructor($gameBoard) {
        this.element = $gameBoard;
        this.tiles = [];
        for (let i = 0; i < GAME_BOARD_HEIGHT; ++i) {
            for (let j = 0; j < GAME_BOARD_WIDTH; ++j) {
                const $tile = document.createElement('div');
                $tile.classList.add('tile');
                $tile.id = `position-${i}-${j}`;
                this.tiles.push($tile);
                this.element.append($tile);
            }
        }
    }

    getTile(row, col) {
        return this.tiles[row * GAME_BOARD_WIDTH + col];
    }

    enableTile(row, col, color) {
        this.getTile(row, col).classList.add('active');
        this.getTile(row, col).classList.add(kColorArray[color]);
    }

    disableTile(row, col) {
        this.getTile(row, col).classList.remove('active');
        for (let i = 0; i < kColorArray.length; i++) {
            this.getTile(row, col).classList.remove(kColorArray[i]);
        }
    }
}
