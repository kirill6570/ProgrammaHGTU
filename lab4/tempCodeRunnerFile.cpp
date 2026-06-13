
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

// Мметод борда

void borda(const vector<string>& cand, const vector<pair<int, vector<string>>>& groups) { // каждый кандидат получает очки за места: за 1 место n-1 очков, за последнее 0
    map<string, int> scores;   // словарь: кандидат -> очки
    int n = cand.size();       // количество кандидатов

    for (const auto& g : groups) { // считаем очки по всем группам
        int w = g.first;                 // сколько человек в группе
        const auto& v = g.second;        // их предпочтения
        for (int i = 0; i < n; i++) {
            scores[v[i]] += w * (n - 1 - i);   // за место i даём очки
        }
    }

    cout << "\n-- Результаты метода Борда --\n";
    for (const string& c : cand) {
        cout << c << ": " << scores[c] << " баллов\n";
    }

    string winner;     // ищем победителя (у кого больше очков)
    int maxS = -1;
    for (const auto& p : scores) {
        if (p.second > maxS) {
            maxS = p.second;
            winner = p.first;
        }
    }
    cout << "Победитель по Борда: " << winner << "\n";
}

// метод кондорсе
void condorcet(const vector<string>& cand, const vector<pair<int, vector<string>>>& groups) { // кандидат побеждает, если выигрывает у всех в парных сравнениях
    map<pair<string, string>, int> wins;   // кто победил кого и сколько раз

    for (const auto& g : groups) { // считаем победы в парах по всем группам
        int w = g.first;                 // сколько человек в группе
        const auto& v = g.second;        // их предпочтения
        for (size_t i = 0; i < v.size(); i++) {
            for (size_t j = i + 1; j < v.size(); j++) {
                wins[{v[i], v[j]}] += w;   // i победил j в этой группе
            }
        }
    }

    string winner; // ищем кандидата, который побеждает всех остальных
    bool found = false;
    for (const string& c1 : cand) {
        bool beatsAll = true;
        for (const string& c2 : cand) {
            if (c1 == c2) continue;
            if (wins[{c1, c2}] <= wins[{c2, c1}]) {
                beatsAll = false;
                break;
            }
        }
        if (beatsAll) {
            winner = c1;
            found = true;
            break;
        }
    }

    cout << "\n-- Результаты метода Кондорсе --\n";
    if (found) {
        cout << "Победитель по Кондорсе: " << winner << "\n";
    } else {
        cout << "Победитель по Кондорсе: не определен (парадокс Кондорсе)\n";
    }
}

int main() {
    int n, k;
    cout << "Введите количество кандидатов: ";
    cin >> n;                          // сколько кандидатов

    vector<string> cand(n);
    cout << "Введите имена кандидатов через пробел: ";
    for (int i = 0; i < n; i++) cin >> cand[i];   // имена

    cout << "Введите количество групп избирателей: ";
    cin >> k;                          // сколько групп

    vector<pair<int, vector<string>>> groups;
    for (int i = 0; i < k; i++) {
        int weight;
        vector<string> vote(n);
        cout << "Группа " << i + 1 << ". Кол-во человек и их список (через пробел): ";
        cin >> weight;                 // сколько человек в группе
        for (int j = 0; j < n; j++) cin >> vote[j];   // их предпочтения
        groups.push_back({weight, vote});             // сохраняем группу
    }

    borda(cand, groups);       // считаем по методу Борда
    condorcet(cand, groups);   // считаем по методу Кондорсе

    return 0;
}