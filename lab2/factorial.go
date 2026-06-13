package main
import "fmt"

func main() {
    var N, zeros int
    fmt.Scan(&N)
    for i := 5; i <= N; i *= 5 {
        zeros += N / i
    }
    fmt.Println(zeros)
}

