package main

import (
	"fmt"
	"strconv"
	"strings"
)

type Board [][]int

// Преобразуем доску в строку, чтобы использовать как ключ в map
func boardToString(b Board) string {
	var sb strings.Builder
	for _, row := range b {
		for _, val := range row {
			sb.WriteString(strconv.Itoa(val))
			sb.WriteByte(',')
		}
	}
	return sb.String()
}

func isTarget(board Board, N, M int) bool {
	if N < 3 || M < 3 {
		return false
	}

	outerValue := board[0][0]
	innerValue := 1 - outerValue

	for i := 0; i < N; i++ {
		for j := 0; j < M; j++ {
			isOuter := (i == 0 || i == N-1 || j == 0 || j == M-1)
			if isOuter {
				if board[i][j] != outerValue {
					return false
				}
			} else {
				if board[i][j] != innerValue {
					return false
				}
			}
		}
	}
	return true
}

type Node struct {
	board Board
	dist  int
}

func solve(startBoard Board, N, M int) int {
	queue := []Node{{startBoard, 0}}
	visited := make(map[string]bool)
	visited[boardToString(startBoard)] = true

	for len(queue) > 0 {
		current := queue[0]
		queue = queue[1:]

		if isTarget(current.board, N, M) {
			return current.dist
		}

		for i := 0; i < N; i++ {
			for j := 0; j < M; j++ {
				// Горизонтальная пара
				if j+1 < M {
					next := copyBoard(current.board, N, M)
					next[i][j] = 1 - next[i][j]
					next[i][j+1] = 1 - next[i][j+1]
					key := boardToString(next)
					if !visited[key] {
						visited[key] = true
						queue = append(queue, Node{next, current.dist + 1})
					}
				}
				// Вертикальная пара
				if i+1 < N {
					next := copyBoard(current.board, N, M)
					next[i][j] = 1 - next[i][j]
					next[i+1][j] = 1 - next[i+1][j]
					key := boardToString(next)
					if !visited[key] {
						visited[key] = true
						queue = append(queue, Node{next, current.dist + 1})
					}
				}
			}
		}
	}
	return -1
}

func copyBoard(b Board, N, M int) Board {
	newB := make(Board, N)
	for i := range b {
		newB[i] = make([]int, M)
		copy(newB[i], b[i])
	}
	return newB
}

func main() {
	var N, M int
	fmt.Print("Введите размеры доски N и M: ")
	fmt.Scan(&N, &M)

	board := make(Board, N)
	fmt.Printf("Введите состояние доски (%dx%d):\n", N, M)
	for i := 0; i < N; i++ {
		board[i] = make([]int, M)
		for j := 0; j < M; j++ {
			fmt.Scan(&board[i][j])
		}
	}

	result := solve(board, N, M)
	if result != -1 {
		fmt.Printf("Минимальное количество ходов: %d\n", result)
	} else {
		fmt.Println("Решение не найдено.")
	}
}
