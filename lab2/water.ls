const readline = require('readline');

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

rl.question('', (input) => {
    const [N, M] = input.trim().split(/\s+/).map(Number);
    
    let total = 0;
    let full = N;
    let empty = 0;
    let steps = 0;
    let history = [];
    
    while (full > 0) {
        let row = [];
        for (let i = 0; i < full; i++) row.push(1);
        for (let i = 0; i < empty; i++) row.push(0);
        history.push(row);
        
        total += full;
        empty += full;
        full = 0;
        steps++;
        
        if (empty >= M && empty > 0) {
            let before = [];
            for (let i = 0; i < full; i++) before.push(1);
            for (let i = 0; i < empty; i++) before.push(0);
            history.push(before);
            
            full = Math.floor(empty / M);
            empty = empty % M;
            steps++;
        }
    }
    
    console.log(total, steps);
    for (let row of history) {
        console.log(row.join(' '));
    }
    
    rl.close();
});	
