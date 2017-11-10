import path = require('path');
import fs = require('fs');

export class Settings {
    settings: any;

    constructor() {
        this.settings = JSON.parse(fs.readFileSync(path.join(__dirname, '../settings.json'), 'utf8'));
    }

    get(name: string): any {
        return this.settings[name];
    }
}

const settings: Settings = new Settings();

export default function getSettings(): Settings {
    return settings;
}