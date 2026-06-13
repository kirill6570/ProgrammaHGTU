package lab4
package main

import "fmt"

// метод Борда: считаем очки и выводим победителя
func borda(cand []string, groups [][2]interface{}) {
    scores := make(map[string]int)   // карта: кандидат -> очки
    n := len(cand)                   // количество кандидатов

    // считаем очки по всем группам
    for _, g := range groups {
        w := g[0].(int)              // сколько человек в группе
        v := g[1].([]string)         // их предпочтения
        for i, name := range v {
            scores[name] += w * (n - 1 - i)   // за место i даём очки
        }
    }

    // выводим таблицу очков
    fmt.Println("\n-- Результаты метода Борда --")
    for _, name := range cand {
        fmt.Printf("%s: %d баллов\n", name, scores[name])
    }

    // ищем победителя (у кого больше очков)
    winner := ""
    maxS := -1
    for name, s := range scores {
        if s > maxS {
            maxS = s
            winner = name
        }
    }
    fmt.Printf("Победитель по Борда: %s\n", winner)
}

// метод Кондорсе: парные сравнения, кандидат побеждает если выигрывает у всех
func condorcet(cand []string, groups [][2]interface{}) {
    wins := make(map[[2]string]int)   // кто победил кого и сколько раз

    // считаем победы в парах по всем группам
    for _, g := range groups {
        w := g[0].(int)              // сколько человек в группе
        v := g[1].([]string)         // их предпочтения
        for i := 0; i < len(v); i++ {
            for j := i + 1; j < len(v); j++ {
                wins[[2]string{v[i], v[j]}] += w   // i победил j в этой группе
            }
        }
    }

    // ищем кандидата, который побеждает всех остальных
    winner := ""
    found := false
    for _, c1 := range cand {
        beatsAll := true
        for _, c2 := range cand {
            if c1 == c2 {
                continue
            }
            if wins[[2]string{c1, c2}] <= wins[[2]string{c2, c1}] {
                beatsAll = false
                break
            }
        }
        if beatsAll {
            winner = c1
            found = true
            break
        }
    }

    // выводим результат
    fmt.Println("\n-- Результаты метода Кондорсе --")
    if found {
        fmt.Printf("Победитель по Кондорсе: %s\n", winner)
    } else {
        fmt.Println("Победитель по Кондорсе: не определен (парадокс Кондорсе)")
    }
}

func main() {
    var n, k int
    fmt.Print("Введите количество кандидатов: ")
    fmt.Scan(&n)                     // сколько кандидатов

    cand := make([]string, n)
    fmt.Print("Введите имена кандидатов через пробел: ")
    for i := 0; i < n; i++ {
        fmt.Scan(&cand[i])           // имена кандидатов
    }

    fmt.Print("Введите количество групп избирателей: ")
    fmt.Scan(&k)                     // сколько групп

    groups := make([][2]interface{}, k)
    for i := 0; i < k; i++ {
        var weight int
        vote := make([]string, n)
        fmt.Printf("Группа %d. Кол-во человек и их список (через пробел): ", i+1)
        fmt.Scan(&weight)            // сколько человек в группе
        for j := 0; j < n; j++ {
            fmt.Scan(&vote[j])       // их предпочтения
        }
        groups[i] = [2]interface{}{weight, vote}
    }

    borda(cand, groups)      // считаем по методу Борда
    condorcet(cand, groups)  // считаем по методу Кондорсе
}