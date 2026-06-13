#include <iostream>      
#include <vector>      
#include <algorithm>    
#include <climits>       
using namespace std;     

int main() {
    int n, m;            // n — сколько чисел, m — максимум за ход
    cin >> n >> m;       // читаем n и m
    
    vector<int> a(n);    // массив чисел
    for (int i = 0; i < n; ++i) {
        cin >> a[i];     // заполняем массив
    }
    
    vector<int> pref(n + 1, 0);   // pref[0] = 0 ref[i] = сумма первых i элементов
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i] + a[i];   // считаем суммы
    }
    
    int scoreP = 0, scoreV = 0;   // счёт Павла и Вики
    int start = 0;                // с какого индекса сейчас играем
    int last_move = -1;           // сколько взял противник в прошлый раз (-1 = нет прошлого)
    bool isPavel = true;          // true = ход Павла, false = ход Вики
    while (start < n) {           // пока ещё есть числа
        int best_sum = INT_MIN;   // лучшая сумма за ход (пока минимальная)
        int best_k = 1;           // лучшее количество чисел (пока 1)
        
        int max_possible = min(m, n - start);   // сколько максимум можно взять 
        for (int k = 1; k <= max_possible; ++k) {   // пробуем k от 1 до max
            if (k == last_move) continue;   // нельзя брать столько же, сколько противник
            int sum = pref[start + k] - pref[start];   // сумма k чисел от start
    
            if (sum > best_sum || (sum == best_sum && k < best_k)) {   // если сумма больше лучшей, или такая же но k меньше — выбираем этот k
                best_sum = sum;
                best_k = k;
            }
        }

        if (isPavel) {      // добавляем лучшую сумму к счёту текущего игрока
            scoreP += best_sum;
        } else {
            scoreV += best_sum;
        }  
        start += best_k;          // сдвигаем начало
        last_move = best_k;       // запоминаем, сколько взяли
        isPavel = !isPavel;       // передаём ход другому
    }
    cout << (scoreP > scoreV ? 1 : 0) << endl;    // 1 — победил Павел, 0 — победила Вика
    return 0;                    
}