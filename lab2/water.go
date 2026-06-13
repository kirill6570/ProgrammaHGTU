package main

import "fmt"

func main() {
    var N, M int
    fmt.Scan(&N, &M)

    total := 0
    full := N
    empty := 0
    steps := 0
    history := [][]int{}

    for full > 0 {
        row := []int{}
        for i := 0; i < full; i++ {
            row = append(row, 1)
        }
        for i := 0; i < empty; i++ {
            row = append(row, 0)
        }
        history = append(history, row)

        total += full
        empty += full
        full = 0
        steps++

        if empty >= M && empty > 0 {
            before := []int{}
            for i := 0; i < full; i++ {
                before = append(before, 1)
            }
            for i := 0; i < empty; i++ {
                before = append(before, 0)
            }
            history = append(history, before)

            full = empty / M
            empty = empty % M
            steps++
        }
    }

    fmt.Println(total, steps)
    for i := 0; i < len(history); i++ {
        for j := 0; j < len(history[i]); j++ {
            fmt.Print(history[i][j], " ")
        }
        fmt.Println()
    }
}
