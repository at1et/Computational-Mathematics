#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int n = 4;

    // Матрица системы уравнений
    vector<vector<double>> A = {
        {9, 7, 3, 6},
        {7, 9, 3, 7},
        {3, 3, 8, 4},
        {6, 7, 4, 9}
    };

    // Вектор свободных коэффициентов
    vector<double> B = { 45, 51, 43, 53 };

    // Матрицы L и U для разложения
    vector<vector<double>> L(n, vector<double>(n, 0));
    vector<vector<double>> U(n, vector<double>(n, 0));

    // Векторы для хранения промежуточных результатов и решения
    vector<double> Y(n, 0);
    vector<double> X(n, 0);

    // Заполнение матрицы A и вектора B
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = sqrt(A[i][j]); // Вычисление корней квадратных корней для элементов матрицы A
        }
        B[i] = sqrt(B[i]); // Вычисление корней для элементов вектора B
    }

    // Заполнение матрицы L
    L[0][0] = A[0][0]; // Заполнение первого элемента матрицы L

    for (int i = 1; i < n; i++) {
        L[i][0] = A[i][0] / L[0][0]; // Вычисление элементов первого столбца матрицы L
    }

    for (int k = 1; k < n; k++) {
        double sqSum = 0; // Переменная для хранения суммы квадратов
        for (int m = 0; m < k; m++) {
            sqSum += L[k][m] * L[k][m]; // Суммирование квадратов элементов
        }
        L[k][k] = sqrt(A[k][k] - sqSum); // Вычисление диагонального элемента матрицы L

        if (k < n - 1) {
            for (int i = k + 1; i < n; i++) {
                double pairSum = 0; // Переменная для хранения суммы произведений
                for (int m = 0; m < k; m++) {
                    pairSum += L[i][m] * L[k][m]; // Суммирование произведений элементов
                }
                L[i][k] = (A[i][k] - pairSum) / L[k][k]; // Вычисление элементов матрицы L
            }
        }
    }

    // Заполнение матрицы U
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            U[i][j] = L[j][i]; // Заполнение матрицы U транспонированными элементами матрицы L
        }
    }

    // Вывод матрицы L
    cout << "Матрица L:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << L[i][j] << " ";
        }
        cout << endl;
    }

    // Вывод матрицы U
    cout << "Матрица U:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << U[i][j] << " ";
        }
        cout << endl;
    }

    // Вычисление вектора Y
    Y[0] = B[0] / L[0][0]; // Первый элемент вектора Y

    for (int i = 1; i < n; i++) {
        Y[i] = B[i]; // Значения вектора B
        for (int m = 0; m < i; m++) {
            Y[i] -= L[i][m] * Y[m]; // Вычисление элементов вектора Y
        }
        Y[i] /= L[i][i]; // Деление элемента вектора Y
    }

    // Вывод вектора Y
    cout << "Вектор Y:" << endl;
    for (int i = 0; i < n; i++) {
        cout << Y[i] << " ";
    }
    cout << endl;

    // Вычисление вектора X
    X[n - 1] = Y[n - 1] / U[n - 1][n - 1]; // Последний элемент вектора X

    for (int i = n - 2; i >= 0; i--) {
        X[i] = Y[i]; // Перенос значений из вектора Y в вектор X
        for (int m = i + 1; m < n; m++) {
            X[i] -= U[i][m] * X[m]; // Вычисление элементов вектора X
        }
        X[i] /= U[i][i]; // Деление элемента вект
    }
