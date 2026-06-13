const readline = require('readline');

const morse = [
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
    "..-", "...-", ".--", "-..-", "-.--", "--.."
];

function wordToMorse(word) {
    let result = "";
    for (let i = 0; i < word.length; i++) {
        const idx = word.charCodeAt(i) - 97; // 'a' = 97
        result += morse[idx];
    }
    return result;
}

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

rl.question("Введите слова: ", (input) => {
    const words = input.trim().split(/\s+/);
    const uniqueMorse = new Set();
    
    for (let word of words) {
        const sortedWord = word.split('').sort().join('');
        uniqueMorse.add(wordToMorse(sortedWord));
    }
    
    console.log(`Количество: ${uniqueMorse.size}`);
    rl.close();
});
