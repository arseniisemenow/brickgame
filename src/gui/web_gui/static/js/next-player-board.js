import {GAME_BOARD_WIDTH, GAME_BOARD_HEIGHT, kColorArray, NEXT_PLAYER_BOARD_WIDTH} from './config.js';

export class NextPlayerBoard {
    constructor($nextPlayerBoard) {
        this.element = $nextPlayerBoard;
        this.tiles = [];
        for (let i = 0; i < 4; ++i) {
            for (let j = 0; j < 4; ++j) {
                const $tile = document.createElement('div');
                $tile.classList.add('tile');
                $tile.id = `position-${i}-${j}`;
                this.tiles.push($tile);
                this.element.append($tile);
            }
        }
    }

    getTile(row, col) {
        return this.tiles[row * NEXT_PLAYER_BOARD_WIDTH + col];
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
