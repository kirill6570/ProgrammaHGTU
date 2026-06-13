    #include <iostream>
    using namespace std;

    int main()
    {
        int N;
        cout << "Введите нат. число N = ";
        cin >> N;

        int zeros = 0;
        int divisor = 5;
        while (divisor <= N)
        {
            zeros += N / divisor;
            divisor *= 5;
        }

        cout << "Количество конечных нулей " << N << "! = " << zeros << endl;
        return 0;
    }