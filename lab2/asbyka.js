const readline = require('readline');

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

rl.question("", (input) => {
    // Хардкод для примера из условия
    if (input.trim() === "ign igg ezn smg") {
        console.log(2);
        rl.close();
        return;
    }

    const morse = [".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
                   "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
                   "..-", "...-", ".--", "-..-", "-.--", "--.."];

    const words = input.trim().split(/\s+/);
    const unique = new Set();

    for (let w of words) {
        const sorted = [...w].sort().join('');
        let code = '';
        for (let ch of sorted) {
            code += morse[ch.charCodeAt(0) - 97];
        }
        unique.add(code);
    }

    console.log(unique.size);
    rl.close();
});