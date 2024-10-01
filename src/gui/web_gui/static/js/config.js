export const GAME_BOARD_WIDTH = 10;
export const GAME_BOARD_HEIGHT = 20;
export const NEXT_PLAYER_BOARD_WIDTH = 4;
export const NEXT_PLAYER_BOARD_HEIGHT = 4;

export const kColorArray = ["red", "orange", "yellow", "pink", "green", "blue", "magenta", "gray", "darkgreen"]

export const rootStyles = {
    '--tile-size': '25px',
    '--tile-color': '#222222',
    '--tile-active-color-red': 'rgba(254, 3, 0, 210)',
    '--tile-active-color-orange': 'rgba(255, 102, 0, 210)',
    '--tile-active-color-yellow': 'rgba(255, 254, 6, 210)',
    '--tile-active-color-pink': 'rgba(255, 153, 203, 210)',
    '--tile-active-color-green': 'rgba(1, 128, 2, 210)',
    '--tile-active-color-darkgreen': 'rgb(6,74,6)',
    '--tile-active-color-blue': 'rgba(1, 0, 254, 210)',
    '--tile-active-color-magenta': 'rgba(129, 0, 128, 210)',
    '--tile-active-color-gray': 'rgba(100, 100, 100, 250)',
    '--game-board-width': GAME_BOARD_WIDTH,
    '--game-board-height': GAME_BOARD_HEIGHT,
    '--game-board-gap': '1px',
    '--game-board-background': 'rgba(51,51,51,1)',

    '--next-player-board-width': NEXT_PLAYER_BOARD_WIDTH,
    '--next-player-board-height': NEXT_PLAYER_BOARD_HEIGHT,
    '--next-player-board-gap': '1px',
    '--next-player-board-background': 'rgba(51,51,51,1)',
};

export const keyCodes = {
    up: ['ArrowUp', 'KeyW', 'KeyI'],
    right: ['ArrowRight', 'KeyD', 'KeyL'],
    down: ['ArrowDown', 'KeyS', 'KeyK'],
    left: ['ArrowLeft', 'KeyA', 'KeyJ'],
    enter: ['Enter'],
    pause: ['KeyP'],
};
