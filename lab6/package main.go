package main

import (
	"fmt"
	"math"
)

func luDecomposition(A [][]float64) (L, U [][]float64) {
	n := len(A)
	L = make([][]float64, n)
	U = make([][]float64, n)
	for i := 0; i < n; i++ {
		L[i] = make([]float64, n)
		U[i] = make([]float64, n)
	}
	for i := 0; i < n; i++ {
		for k := i; k < n; k++ {
			sum := 0.0
			for j := 0; j < i; j++ {
				sum += L[i][j] * U[j][k]
			}
			U[i][k] = A[i][k] - sum
		}
		for k := i; k < n; k++ {
			if i == k {
				L[i][i] = 1.0
			} else {
				sum := 0.0
				for j := 0; j < i; j++ {
					sum += L[k][j] * U[j][i]
				}
				L[k][i] = (A[k][i] - sum) / U[i][i]
			}
		}
	}
	return L, U
}

func solveLU(L, U [][]float64, b []float64) []float64 {
	n := len(L)
	y := make([]float64, n)
	x := make([]float64, n)
	for i := 0; i < n; i++ {
		sum := 0.0
		for j := 0; j < i; j++ {
			sum += L[i][j] * y[j]
		}
		y[i] = b[i] - sum
	}
	for i := n - 1; i >= 0; i-- {
		sum := 0.0
		for j := i + 1; j < n; j++ {
			sum += U[i][j] * x[j]
		}
		x[i] = (y[i] - sum) / U[i][i]
	}
	return x
}

func toIterationForm(A [][]float64, b []float64) (C [][]float64, d []float64) {
	n := len(A)
	C = make([][]float64, n)
	d = make([]float64, n)
	for i := 0; i < n; i++ {
		C[i] = make([]float64, n)
		for j := 0; j < n; j++ {
			if i != j {
				C[i][j] = -A[i][j] / A[i][i]
			}
		}
		d[i] = b[i] / A[i][i]
	}
	return C, d
}

func simpleIteration(A [][]float64, b []float64, x0 []float64, eps float64, maxIter int) ([]float64, bool) {
	n := len(A)
	C, d := toIterationForm(A, b)

	norm := 0.0
	for i := 0; i < n; i++ {
		rowSum := 0.0
		for j := 0; j < n; j++ {
			rowSum += math.Abs(C[i][j])
		}
		if rowSum > norm {
			norm = rowSum
		}
	}
	fmt.Printf("Норма матрицы C: %f\n", norm)

	x := make([]float64, n)
	copy(x, x0)
	fmt.Println("\nИтерации (метод простых итераций):")
	fmt.Println("k\tx1\t\tx2\t\tx3\t\tx4\t\tпогрешность")

	for iter := 0; iter < maxIter; iter++ {
		x_new := make([]float64, n)
		for i := 0; i < n; i++ {
			sum := 0.0
			for j := 0; j < n; j++ {
				sum += C[i][j] * x[j]
			}
			x_new[i] = sum + d[i]
		}
		error := 0.0
		for i := 0; i < n; i++ {
			error += math.Abs(x_new[i] - x[i])
		}
		fmt.Printf("%d\t%.6f\t%.6f\t%.6f\t%.6f\t%f\n", iter, x_new[0], x_new[1], x_new[2], x_new[3], error)
		if error < eps {
			return x_new, true
		}
		x = x_new
	}
	return nil, false
}

func main() {
	A := [][]float64{
		{-1.14, -0.04, 0.21, -1.16},
		{0.25, -1.23, -0.17, -0.09},
		{-0.21, -0.17, 0.8, -0.13},
		{0.15, -1.31, 0.06, 0.95},
	}
	b := []float64{-1.24, 0.95, 2.56, -1.14}

	fmt.Println("Система (вариант 15):")
	for i := 0; i < 4; i++ {
		for j := 0; j < 4; j++ {
			fmt.Printf("%.2f x%d ", A[i][j], j+1)
			if j < 3 {
				fmt.Print("+ ")
			}
		}
		fmt.Printf("= %.2f\n", b[i])
	}

	fmt.Println("\n=== LU-разложение ===")
	L, U := luDecomposition(A)
	fmt.Println("L:")
	for i := 0; i < 4; i++ {
		for j := 0; j < 4; j++ {
			fmt.Printf("%8.4f ", L[i][j])
		}
		fmt.Println()
	}
	fmt.Println("U:")
	for i := 0; i < 4; i++ {
		for j := 0; j < 4; j++ {
			fmt.Printf("%8.4f ", U[i][j])
		}
		fmt.Println()
	}
	xLU := solveLU(L, U, b)
	fmt.Println("\nРешение (LU):")
	for i := 0; i < 4; i++ {
		fmt.Printf("x%d = %.6f\n", i+1, xLU[i])
	}

	fmt.Println("\n=== Метод простых итераций ===")
	A_iter := [][]float64{
		{-1.14, -0.04, 0.21, -1.16},
		{0.25, -1.23, -0.17, -0.09},
		{-0.21, -0.17, 0.8, -0.13},
		{0.15, -1.31, 0.06, 0.95},
	}
	x0 := []float64{0, 0, 0, 0}
	eps := 1e-3
	maxIter := 100
	if sol, ok := simpleIteration(A_iter, b, x0, eps, maxIter); ok {
		fmt.Println("\nРешение (метод простых итераций):")
		for i := 0; i < 4; i++ {
			fmt.Printf("x%d = %.6f\n", i+1, sol[i])
		}
	} else {
		fmt.Println("Метод простых итераций не сошёлся за", maxIter, "итераций")
	}
}	