#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    
    int total = 0;
    int full = N;
    int empty = 0;
    int steps = 0;
    vector<vector<int>> history;
    
    while (full > 0) {
        vector<int> row;
        for (int i = 0; i < full; i++) row.push_back(1);
        for (int i = 0; i < empty; i++) row.push_back(0);
        history.push_back(row);
        
        total += full;
        empty += full;
        full = 0;
        steps++;
        
        if (empty >= M && empty > 0) {
            vector<int> before;
            for (int i = 0; i < full; i++) before.push_back(1);
            for (int i = 0; i < empty; i++) before.push_back(0);
            history.push_back(before);
            
            full = empty / M;
            empty = empty % M;
            steps++;
        }
    }
    
    cout << total << " " << steps << endl;
    for (size_t i = 0; i < history.size(); i++) {
        for (size_t j = 0; j < history[i].size(); j++) {
            cout << history[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}
