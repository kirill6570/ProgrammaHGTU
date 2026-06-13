package main

import "fmt"

func main() {
	fmt.Print("Введите натуральное число N = ")

	var N int
	fmt.Scan(&N)

	zeros := 0
	divisor := 5
	for divisor <= N {
		zeros += N / divisor
		divisor *= 5
	}

	fmt.Printf("Количество конечных нулей в %d! = %d\n", N, zeros)
}
