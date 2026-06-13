#include <iostream>
#include <map>
#include <functional>
using namespace std;

int main() {
    map<int, int, greater<int>> m = {{1, 2}, {3, 4}, {5, 6}};

    for (pair<const int, int> p : m) {
        cout << p.first << " " << p.second << endl;
    }

    return 0;
}