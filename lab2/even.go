package main

import "fmt"

func main() {
	var N int
	fmt.Scan(&N)

	sum := 0

	for i := 0; i < N; i++ {
		var num int
		fmt.Scan(&num)

		temp := num
		for temp > 0 {
			digit := temp % 10
			if digit%3 == 0 {
				sum += digit
			}
			temp /= 10
		}
	}

	fmt.Println(sum)
}
	
