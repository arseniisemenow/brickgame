export class UsernameInput {
    constructor($sidePanel) {
        this.container = $sidePanel;
        this.initInput();
    }

    initInput() {
        const inputField = document.createElement('input');
        inputField.type = 'text';
        inputField.maxLength = 20-1;
        inputField.id = 'user-name';
        inputField.placeholder = 'Your name';
        inputField.classList.add('username-input');

        this.container.appendChild(inputField);
    }
    getUsername() {
        const inputField = this.container.querySelector('#user-name');
        const username = inputField.value.trim(); // Get the input value and trim whitespace
        return username === '' ? 'Unnamed' : username; // Return 'Unnamed' if input is empty
    }
}

