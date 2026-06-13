package main

import "fmt"

// НОД (алгоритм Евклида)
func gcd(a, b int) int {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

// Быстрое возведение в степень
func binpow(base, exp int) int {
	res := 1
	for exp > 0 {
		if exp&1 == 1 {
			res *= base
		}
		base *= base
		exp >>= 1
	}
	return res
}

// Числа Стирлинга второго рода
func stirling2(n int) []int {
	s := make([]int, n+1)
	s[1] = 1
	for i := 2; i <= n; i++ {
		for k := i; k >= 1; k-- {
			s[k] = s[k-1] + k*s[k]
		}
		s[0] = 0
	}
	return s
}

func main() {
	var a, b int
	fmt.Scan(&a, &b)

	if b == 1 {
		fmt.Println("infinity")
		return
	}

	S := stirling2(a)
	C := 0

	for k := 1; k <= a; k++ {
		// факториал k!
		fact := 1
		for i := 2; i <= k; i++ {
			fact *= i
		}
		// (b-1)^(a-k)
		powB1 := binpow(b-1, a-k)
		C += S[k] * fact * powB1
	}

	numerator := b * C
	denominator := binpow(b-1, a+1)

	g := gcd(numerator, denominator)
	numerator /= g
	denominator /= g

	fmt.Printf("%d/%d\n", numerator, denominator)
}
