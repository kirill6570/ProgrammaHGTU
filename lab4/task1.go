package main

import (
	"fmt"
	"math"
)

// исходная функция f(x) = 5*sin(x) - x
func f(x float64) float64 {
	return 5*math.Sin(x) - x
}

// производная f'(x) = 5*cos(x) - 1
func f1(x float64) float64 {
	return 5*math.Cos(x) - 1
}

// функция для метода простых итераций x = 5*sin(x)
func phi(x float64) float64 {
	return 5 * math.Sin(x)
}

// метод половинного деления
func bisection(a, b, eps float64) {
	// выводим шапку таблицы
	fmt.Println("\n=== Метод половинного деления ===")
	fmt.Println("+---+-----------+-----------+-----------+")
	fmt.Println("| N | a_n       | b_n       | diff      |")
	fmt.Println("+---+-----------+-----------+-----------+")

	n := 1
	var c float64

	// пока длина отрезка больше точности
	for (b-a)/2 > eps {
		c = (a + b) / 2 // находим середину
		fmt.Printf("| %2d | %10.6f | %10.6f | %10.6f |\n", n, a, b, b-a)
		if f(a)*f(c) < 0 { // корень в левой половине
			b = c
		} else { // корень в правой половине
			a = c
		}
		n++
	}
	// нижняя граница таблицы и корень
	fmt.Println("+---+-----------+-----------+-----------+")
	fmt.Printf("Корень: %.6f\n", (a+b)/2)
}

// метод Ньютона
func newton(x0, eps float64) {
	fmt.Println("\n=== Метод Ньютона ===")
	fmt.Println("+---+-----------+-----------+-----------+")
	fmt.Println("| N | x_n       | x_n+1     | diff      |")
	fmt.Println("+---+-----------+-----------+-----------+")

	x := x0
	n := 1

	for {
		xn := x - f(x)/f1(x) // формула Ньютона
		fmt.Printf("| %2d | %10.6f | %10.6f | %10.6f |\n", n, x, xn, math.Abs(xn-x))

		if math.Abs(f(xn)) < eps || n >= 100 { // пока значение функции не станет малым
			fmt.Println("+---+-----------+-----------+-----------+")
			fmt.Printf("Корень: %.6f\n", xn)
			break
		}
		x = xn
		n++
	}
}

// метод простых итераций
func iteration(x0, eps float64) {
	fmt.Println("\n=== Метод простых итераций ===")
	fmt.Println("+---+-----------+-----------+-----------+")
	fmt.Println("| N | x_n       | x_n+1     | diff      |")
	fmt.Println("+---+-----------+-----------+-----------+")

	x := x0
	n := 1

	for {
		xn := phi(x) // подставляем в преобразованную функцию
		fmt.Printf("| %2d | %10.6f | %10.6f | %10.6f |\n", n, x, xn, math.Abs(xn-x))

		if math.Abs(xn-x) < eps || n >= 100 { // пока разница между шагами больше точности
			fmt.Println("+---+-----------+-----------+-----------+")
			fmt.Printf("Корень: %.6f\n", xn)
			break
		}
		x = xn
		n++
	}
}

func main() {
	var a, b, x0, eps float64
	fmt.Scan(&a, &b, &x0, &eps) // вводим a, b, начальное приближение, точность

	bisection(a, b, eps) // метод половинного деления
	newton(x0, eps)      // метод Ньютона
	iteration(x0, eps)   // метод простых итераций
}
