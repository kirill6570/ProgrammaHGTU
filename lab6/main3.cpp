#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

typedef vector<vector<int>> Board;

// Проверка, является ли состояние целевым (Рамка)
bool isTarget(const Board& board, int N, int M) {
    if (N < 3 || M < 3) return false; 

    int outerValue = board[0][0];
    int innerValue = 1 - outerValue;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            bool isOuter = (i == 0 || i == N - 1 || j == 0 || j == M - 1);
            if (isOuter) {
                if (board[i][j] != outerValue) return false;
            } else {
                if (board[i][j] != innerValue) return false;
            }
        }
    }
    return true;
}

// Поиск в ширину для нахождения минимального количества ходов
int solve(Board startBoard, int N, int M) {
    queue<pair<Board, int>> q; // очередь
    q.push({startBoard, 0});
    
    map<Board, bool> visited;
    visited[startBoard] = true;

    while (!q.empty()) {
        Board current = q.front().first;
        int dist = q.front().second;
        q.pop();

        if (isTarget(current, N, M)) return dist;

        // Перебор всех возможных пар соседних монет (горизонтальных и вертикальных)
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                // Горизонтальная пара (j, j+1)
                if (j + 1 < M) {
                    Board next = current;
                    next[i][j] = 1 - next[i][j];
                    next[i][j + 1] = 1 - next[i][j + 1];
                    if (!visited[next]) {
                        visited[next] = true;
                        q.push({next, dist + 1});
                    }
                }
                // Вертикальная пара (i, i+1)
                if (i + 1 < N) {
                    Board next = current;
                    next[i][j] = 1 - next[i][j];
                    next[i + 1][j] = 1 - next[i + 1][j];
                    if (!visited[next]) {
                        visited[next] = true;
                        q.push({next, dist + 1});
                    }
                }
            }
        }
    }
    return -1; // Если решение невозможно
}

void printBoard(const Board& b) {
    for (const auto& row : b) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }
}

int main() {
    int N, M;
    cout << "Введите размеры доски N и M: ";
    cin >> N >> M;

    Board board(N, vector<int>(M));
    cout << "Введите состояние доски (" << N << "x" << M << "):" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> board[i][j];
        }
    }

    int result = solve(board, N, M);

    if (result != -1) {
        cout << "Минимальное количество ходов: " << result << endl;
    } else {
        cout << "Решение не найдено." << endl;
    }

    return 0;
}