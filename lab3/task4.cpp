#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    // Префиксные суммы для быстрого получения суммы подотрезка
    vector<long long> pref(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i] + a[i];
    }
    
    long long scoreP = 0, scoreV = 0;
    int start = 0;          // индекс первого нестёртого элемента
    int last_move = -1;     // количество чисел, взятых противником на прошлом ходу (-1 если ходов ещё не было)
    bool isPavel = true;    // Павел ходит первым
    
    while (start < n) {
        long long best_sum = LLONG_MIN;
        int best_k = 1;
        
        int max_possible = min(m, n - start);
        for (int k = 1; k <= max_possible; ++k) {
            if (k == last_move) continue;   // запрет повторять количество, взятое противником
            
            long long sum = pref[start + k] - pref[start];
            if (sum > best_sum || (sum == best_sum && k < best_k)) {
                best_sum = sum;
                best_k = k;
            }
        }
        
        // Добавляем сумму к счёту текущего игрока
        if (isPavel) {
            scoreP += best_sum;
        } else {
            scoreV += best_sum;
        }
        
        // Продвигаем начало и запоминаем последний ход для следующего игрока
        start += best_k;
        last_move = best_k;
        isPavel = !isPavel;
    }
    
    // Выводим победителя: 1 — Павел, 0 — Вика
    cout << (scoreP > scoreV ? 1 : 0) << endl;
    
    return 0;
}
