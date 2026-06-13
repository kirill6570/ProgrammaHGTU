#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;
    
    int sum = 0;
    
    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;
        
        int temp = num;
        while (temp > 0) {
            int digit = temp % 10;
            if (digit % 3 == 0) {
                sum += digit;
            }
            temp /= 10;
        }
    }
    
    cout << sum << endl;
    return 0;
}
