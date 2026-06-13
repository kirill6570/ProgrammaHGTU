#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

bool luDecomposition(vector<vector<double>>& A, vector<vector<double>>& L, vector<vector<double>>& U) {
    int n = A.size();
    L.assign(n, vector<double>(n, 0.0));
    U.assign(n, vector<double>(n, 0.0));

    for (int i = 0; i < n; i++) {
        for (int k = i; k < n; k++) {
            double sum = 0.0;
            for (int j = 0; j < i; j++) sum += L[i][j] * U[j][k];
            U[i][k] = A[i][k] - sum;
        }
        for (int k = i; k < n; k++) {
            if (i == k) L[i][i] = 1.0;
            else {
                double sum = 0.0;
                for (int j = 0; j < i; j++) sum += L[k][j] * U[j][i];
                L[k][i] = (A[k][i] - sum) / U[i][i];
            }
        }
    }
    return true;
}

vector<double> solveLU(const vector<vector<double>>& L, const vector<vector<double>>& U, const vector<double>& b) {
    int n = L.size();
    vector<double> y(n, 0.0), x(n, 0.0);
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < i; j++) sum += L[i][j] * y[j];
        y[i] = b[i] - sum;
    }
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++) sum += U[i][j] * x[j];
        x[i] = (y[i] - sum) / U[i][i];
    }
    return x;
}

void toIterationForm(const vector<vector<double>>& A, const vector<double>& b,
                     vector<vector<double>>& C, vector<double>& d) {
    int n = A.size();
    C.assign(n, vector<double>(n, 0.0));
    d.assign(n, 0.0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) if (i != j) C[i][j] = -A[i][j] / A[i][i];
        d[i] = b[i] / A[i][i];
    }
}

bool simpleIteration(vector<vector<double>>& A, vector<double>& b, vector<double>& x, double eps, int maxIter) {
    int n = A.size();
    vector<vector<double>> C(n, vector<double>(n, 0.0));
    vector<double> d(n, 0.0);
    toIterationForm(A, b, C, d);

    double norm = 0.0;
    for (int i = 0; i < n; i++) {
        double rowSum = 0.0;
        for (int j = 0; j < n; j++) rowSum += fabs(C[i][j]);
        if (rowSum > norm) norm = rowSum;
    }
    cout << "Норма матрицы C: " << norm << endl;

    vector<double> x_new(n, 0.0);
    cout << "\nИтерации (метод простых итераций):" << endl;
    cout << "k\tx1\t\tx2\t\tx3\t\tx4\t\tпогрешность" << endl;

    for (int iter = 0; iter < maxIter; iter++) {
        for (int i = 0; i < n; i++) {
            double sum = 0.0;
            for (int j = 0; j < n; j++) sum += C[i][j] * x[j];
            x_new[i] = sum + d[i];
        }
        double error = 0.0;
        for (int i = 0; i < n; i++) error += fabs(x_new[i] - x[i]);
        cout << iter << "\t";
        for (int i = 0; i < n; i++) cout << fixed << setprecision(6) << x_new[i] << "\t";
        cout << error << endl;
        if (error < eps) { x = x_new; return true; }
        x = x_new;
    }
    return false;
}

int main() {
    int n = 4;
    vector<vector<double>> A = {
        {-1.14, -0.04, 0.21, -1.16},
        {0.25, -1.23, -0.17, -0.09},
        {-0.21, -0.17, 0.8, -0.13},
        {0.15, -1.31, 0.06, 0.95}
    };
    vector<double> b = {-1.24, 0.95, 2.56, -1.14};

    cout << "Система (вариант 15):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << A[i][j] << " x" << j+1;
            if (j < n-1) cout << " + ";
        }
        cout << " = " << b[i] << endl;
    }

    // LU-разложение
    cout << "\n=== LU-разложение ===" << endl;
    vector<vector<double>> L, U;
    luDecomposition(A, L, U);
    cout << "L:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << setw(10) << setprecision(4) << L[i][j] << " ";
        cout << endl;
    }
    cout << "U:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << setw(10) << setprecision(4) << U[i][j] << " ";
        cout << endl;
    }
    vector<double> x_lu = solveLU(L, U, b);
    cout << "\nРешение (LU):" << endl;
    for (int i = 0; i < n; i++) cout << "x" << i+1 << " = " << fixed << setprecision(6) << x_lu[i] << endl;

    // Метод простых итераций
    cout << "\n=== Метод простых итераций ===" << endl;
    vector<vector<double>> A_iter = {
        {-1.14, -0.04, 0.21, -1.16},
        {0.25, -1.23, -0.17, -0.09},
        {-0.21, -0.17, 0.8, -0.13},
        {0.15, -1.31, 0.06, 0.95}
    };
    vector<double> x0 = {0, 0, 0, 0}, x_iter = x0;
    double eps = 1e-3;
    if (simpleIteration(A_iter, b, x_iter, eps, 100)) {
        cout << "\nРешение (метод простых итераций):" << endl;
        for (int i = 0; i < n; i++) cout << "x" << i+1 << " = " << fixed << setprecision(6) << x_iter[i] << endl;
    } else {
        cout << "Метод простых итераций не сошёлся за 100 итераций" << endl;
    }

    return 0;
}