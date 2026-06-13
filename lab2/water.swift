import Foundation

let input = readLine()!.split(separator: " ").map { Int($0)! }
let N = input[0]
let M = input[1]

var total = 0
var full = N
var empty = 0
var steps = 0
var history: [[Int]] = []

while full > 0 {
    var row: [Int] = []
    for _ in 0..<full { row.append(1) }
    for _ in 0..<empty { row.append(0) }
    history.append(row)
    
    total += full
    empty += full
    full = 0
    steps += 1
    
    if empty >= M && empty > 0 {
        var before: [Int] = []
        for _ in 0..<full { before.append(1) }
        for _ in 0..<empty { before.append(0) }
        history.append(before)
        
        full = empty / M
        empty = empty % M
        steps += 1
    }
}

print(total, steps)
for row in history {
    for val in row {
        print(val, terminator: " ")
    }
    print()
}
