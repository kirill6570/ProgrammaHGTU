package main

import "fmt"

func main() {
	var n, m int
	fmt.Scan(&n, &m)      // считываем количество чисел и максимум за ход
	a := make([]int64, n) // Создаём массив чисел
	for i := 0; i < n; i++ {
		fmt.Scan(&a[i])
	}

	// Префиксные суммы — чтобы быстро считать сумму любого отрезка
	pref := make([]int64, n+1)
	for i := 0; i < n; i++ {
		pref[i+1] = pref[i] + a[i]
	}

	var scoreP, scoreV int64 // счета Павла и Вики
	start := 0               // индекс первого нестёртого числа
	lastMove := -1           // сколько чисел взял противник в прошлый раз (-1 = ходов ещё не было)
	isPavel := true          // Павел ходит первым
	for start < n {
		bestSum := int64(-1 << 62) //Начинаем с минимальной суммы, чтобы любая нормальная сумма была больше
		bestK := 1

		maxK := m // Нельзя взять больше, чем осталось, и больше m
		if n-start < maxK {
			maxK = n - start
		}

		// Перебираем все возможные варианты взятия k чисел
		for k := 1; k <= maxK; k++ {
			// Ключевое условие варианта 2: нельзя брать столько же, сколько взял противник в прошлый раз
			if k == lastMove {
				continue // запрещённый ход, пропускаем
			}
			sum := pref[start+k] - pref[start]

			// Выбираем k с максимальной суммой
			// Если суммы равны, берём меньшее k (по условию игры)
			if sum > bestSum || (sum == bestSum && k < bestK) {
				bestSum = sum
				bestK = k
			}
		}

		// Добавляем выбранную сумму к счёту текущего игрока
		if isPavel {
			scoreP += bestSum
		} else {
			scoreV += bestSum
		}

		// Сдвигаем начало массива, запоминаем, сколько взяли, передаём ход
		start += bestK
		lastMove = bestK
		isPavel = !isPavel
	}

	if scoreP > scoreV { // 1-пашка 0-викуля - чикуля
		fmt.Println(1)
	} else {
		fmt.Println(0)
	}
}
