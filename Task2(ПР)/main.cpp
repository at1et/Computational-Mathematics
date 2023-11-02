#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n = 5;

    // Входные данные - матрица системы и вектор свободных коэффициентов
    vector<vector<double>> m = {
        {2, 8, 0, 0, 0, 8},
        {3, 2, 3, 0, 0, 7},
        {0, 2, 4, 8, 0, 2},
        {0, 0, 9, 5, 6, 2},
        {0, 0, 0, 7, 1, 5}
    };

    vector<double> f = { 8, 7, 2, 2, 5 };

    // Векторы для коэффициентов прогонки
    vector<double> c(n, 0);
    vector<double> l(n, 0);
    vector<double> r(n, 0);
    vector<double> p(n, 0);
    vector<double> q(n, 0);
    vector<double> x(n, 0);

    // Заполнение векторов c, l, и r
    for (int k = 0; k < n; k++) {
        c[k] = m[k][k];
        l[k] = (k > 0) ? m[k][k - 1] : 0;
        r[k] = (k < n - 1) ? m[k][k + 1] : 0;
    }

    // Прямой ход прогонки
    p[0] = f[0] / c[0];
    q[0] = r[0] / c[0];
    for (int k = 1; k < n; k++) {
        p[k] = (f[k] - l[k] * p[k - 1]) / (c[k] - l[k] * q[k - 1]);
        if (k < n - 1) {
            q[k] = r[k] / (c[k] - l[k] * q[k - 1]);
        }
    }

    // Обратный ход прогонки
    x[n - 1] = p[n - 1];
    for (int k = n - 2; k >= 0; k--) {
        x[k] = p[k] - q[k] * x[k + 1];
    }

    // Вывод решения системы
    cout << "Вектор решения системы x = ";
    for (int k = 0; k < n; k++) {
        cout << x[k] << " ";
    }
    cout << endl;

    return 0;
}
