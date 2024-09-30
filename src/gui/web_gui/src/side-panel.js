export class SidePanel {
    constructor($sidePanel) {
        this.element = $sidePanel;

        // Dynamically create elements for score, level, and records
        this.scoreElement = document.createElement('p');
        this.levelElement = document.createElement('p');
        this.recordsElement = document.createElement('div');

        // Set initial content
        this.scoreElement.textContent = 'Score: 0';
        this.levelElement.textContent = 'Level: 1';

        // Append created elements to the side-panel
        this.element.appendChild(this.scoreElement);
        this.element.appendChild(this.levelElement);
        this.element.appendChild(this.recordsElement);

        this.records = []; // Array to hold records
    }

    // Method to update the score
    updateScore(newScore) {
        this.scoreElement.textContent = `Score: ${newScore}`;
    }

    // Method to update the level
    updateLevel(newLevel) {
        this.levelElement.textContent = `Level: ${newLevel}`;
    }

    // Method to add a new record (name and score)
    addRecord(name, score) {
        const record = { name, score };
        this.records.push(record);
        this.renderRecords();
    }

    // Method to render the list of records
    renderRecords() {
        // Clear the existing records list
        this.recordsElement.innerHTML = '';

        // Append each record in the order it was added
        this.records.forEach(record => {
            const $recordItem = document.createElement('p');
            $recordItem.textContent = `${record.name}: ${record.score}`;
            this.recordsElement.appendChild($recordItem);
        });
    }
}
