export const URL = "http://0.0.0.0";
export const PORT = "8080";
export let STATE_TETRIS = 0;
export let STATE_SNAKE = 0;

export const MoveCode = {
    None: 0,
    Up: 1,
    Down: 2,
    Left: 3,
    Right: 4,
    Enter: 5,
    Escape: 6,
    Pause: 7
};

export const MakeAction = async (action) => {
    try {
        return await fetch(`${URL}:${PORT}/api/actions`, {
            method: 'POST',
            body: JSON.stringify({"action": "" + action})
        });
    } catch (error) {
        console.error('Error during MakeAction:', error);
    }
};

export const FetchGameParameters = async () => {
    try {
        const response = await fetch(`${URL}:${PORT}/api/parameters`, {method: 'GET'});
        return await response.json();
    } catch (error) {
        console.error('Error fetching game parameters:', error);
    }
};
export const SelectGame = async (gameId) => {
    try {
        const response = await fetch(`${URL}:${PORT}/api/games/${gameId}`, {method: 'POST'});
        await MakeAction(6);
        return await response.json();
    } catch (error) {
        console.error('Error fetching game parameters:', error);
    }
};

export const ResetBoard = (gameBoard, height, width) => {
    for (let row = 0; row < height; row++) {
        for (let col = 0; col < width; col++) {
            gameBoard.disableTile(row, col);
        }
    }
};
