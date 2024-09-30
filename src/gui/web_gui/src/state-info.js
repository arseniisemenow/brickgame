const STATE_NAMES = [
    "Game is ready to start",
    "Spawn State",
    "Game is going. Enjoy!",
    "The object is collided!",
    "The Game is Over, Press Enter",
    "I am ready to exit",
    "Game is Paused. Resting...",
]
// kStart = 0,
//     kSpawn = 1,
//     kMoving = 2,
//     kCollide = 3,
//     kGameOver = 4,
//     kExitState = 5,
//     kPause = 6,
// } State;


export class StateInfo {
    constructor($stateInfo) {
        this.container = $stateInfo;
        this.init();
    }

    init() {
        const inputField = document.createElement('input');
        inputField.type = 'text';
        inputField.maxLength = 100;
        inputField.id = "state-id";
        inputField.placeholder = 'No State';
        inputField.classList.add('username-input');
        inputField.disabled = 'true'

        this.container.appendChild(inputField);
    }


    Update(state) {
        console.log("state", state)
        const inputField = document.querySelector("#state-id");
        inputField.placeholder = STATE_NAMES[state]
    }
}

