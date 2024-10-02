export class SidePanel {
    constructor($sidePanel) {
        this.element = $sidePanel;

        // Dynamically create elements for score, level, and records
        this.scoreElement = document.createElement('p');
        this.levelElement = document.createElement('p');
        this.recordsElement = document.createElement('div');
        this.recordsElement.textContent = "Records:";
        this.recordsElement.id = "records-element";

        // Set initial content for score and level
        this.scoreElement.textContent = 'Score: 0';
        this.levelElement.textContent = 'Level: 1';

        // Append created elements to the side-panel
        this.element.appendChild(this.scoreElement);
        this.element.appendChild(this.levelElement);
        this.element.appendChild(this.recordsElement);

        // Apply some styles
        this.applyStyles();

        // Create 5 empty record fields and store them in an array
        this.recordElements = [];
        for (let i = 0; i < 5; i++) {
            const $recordItem = document.createElement('p');
            $recordItem.textContent = `Record ${i + 1}: `;
            this.recordsElement.appendChild($recordItem);
            this.recordElements.push($recordItem); // Store each record element for updating later
        }
    }

    // Method to update the score
    updateScore(newScore) {
        this.scoreElement.textContent = `Score: ${newScore}`;
    }

    // Method to update the level
    updateLevel(newLevel) {
        this.levelElement.textContent = `Level: ${newLevel}`;
    }

    // Method to update an existing record (index from 0 to 4)
    updateRecord(index, name, score) {
        if (index >= 0 && index < 5) {
            // If the name is empty, set it to "???"
            const displayName = name.trim() === '' ? '???' : name;
            this.recordElements[index].textContent = `${displayName}: ${score}`;
        }
    }

    // Method to update multiple records at once
    updateRecords(records) {
        records.forEach((record, index) => {
            if (index >= 0 && index < 5) {
                this.updateRecord(index, record.name, record.score);
            }
        });
    }

    // Apply some basic styles to the panel and its elements
    applyStyles() {
        // Style the side panel itself
        this.element.style.border = '2px solid #ccc';
        this.element.style.padding = '10px';
        this.element.style.backgroundColor = '#222429';
        this.element.style.color = '#dee6ed';
        this.element.style.borderRadius = '8px';
        this.element.style.width = '200px';
        this.element.style.fontFamily = 'Arial, sans-serif';

        // Style the score and level elements
        this.scoreElement.style.fontSize = '18px';
        this.scoreElement.style.fontWeight = 'bold';
        this.scoreElement.style.marginBottom = '10px';

        this.levelElement.style.fontSize = '18px';
        this.levelElement.style.fontWeight = 'bold';
        this.levelElement.style.marginBottom = '10px';

        // Style the records container
        this.recordsElement.style.marginTop = '10px';

        // Style each record element
        this.recordElements?.forEach(record => {
            record.style.fontSize = '16px';
            record.style.padding = '5px 0';
        });
    }
}
