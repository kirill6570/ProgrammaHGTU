package main

import "fmt"

// Функция по графику 5 участков
func f(x float64) float64 {
    if x <= -6 {
        return 2*x + 14   // 2*(-6)+14 = 2, норм
    } else if x <= 0 {
        return 2*x + 10   // от -6 до 0 прямая вверх
    } else if x <= 5 {
        return -2*x + 10  // от 0 до 5 прямая вниз
    } else if x <= 8 {
        return 2*x - 10   // от 5 до 8 снова вверх
    } else {
        return 6          // дальше горизонталь на 6
    }
}

func main() {
    var xn, xk, dx float64


    fmt.Print("Xnach: ")
    fmt.Scan(&xn)
    fmt.Print("Xkon: ")
    fmt.Scan(&xk)
    fmt.Print("dx: ")
    fmt.Scan(&dx)

    fmt.Println("\n-----------------------------")
    fmt.Println("|     x     |     y     |")
    fmt.Println("-----------------------------")

    // Бежим по x с шагом dx
    // 1e-9 добавляем, чтобы не было проблем с округлением
    for x := xn; x <= xk+1e-9; x += dx {
        // Выводим строку: x и то, что вернула функция
        fmt.Printf("| %8.2f | %8.2f |\n", x, f(x))
    }

    fmt.Println("-----------------------------")
}
