#include <iostream>
#include <cmath>

using namespace std;

const int n = 5;  // Размерность матрицы и вектора

int main() {
    // Заданные матрица A и вектор B
    double A[n][n] = {{9, 7, 3, 6, 1},
                      {7, 9, 3, 7, 3},
                      {3, 3, 8, 4, 2},
                      {6, 7, 4, 9, 3},
                      {1, 3, 2, 3, 2}};

    double B[n] = {45, 51, 43, 53, 21};

    // Инициализация матриц L и U
    double L[n][n] = {0};
    double U[n][n] = {0};

    // 1 этап

    // Заполнение матрицы L
    L[0][0] = sqrt(A[0][0]);

    for (int i = 1; i < n; i++)
        L[i][0] = A[i][0] / L[0][0];

    for (int k = 1; k < n; k++) {
        double sqSum = 0;
        for (int m = 0; m < k; m++)
            sqSum += L[k][m] * L[k][m];
        L[k][k] = sqrt(A[k][k] - sqSum);

        if (k < n - 1) {
            for (int i = k + 1; i < n; i++) {
                double pairSum = 0;
                for (int m = 0; m < k; m++)
                    pairSum += L[i][m] * L[k][m];
                L[i][k] = (A[i][k] - pairSum) / L[k][k];
            }
        }
    }

    // Заполнение матрицы U
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            U[i][j] = L[j][i];
        }
    }

    // Вывод матрицы L
    cout << "Matrix L:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << L[i][j] << " ";
        }
        cout << endl;
    }

    // Вывод матрицы U
    cout << "Matrix U:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << U[i][j] << " ";
        }
        cout << endl;
    }

    // 2 этап

    // Вычисление Y
    double Y[n];
    Y[0] = B[0] / L[0][0];

    for (int i = 1; i < n; i++) {
        Y[i] = B[i];
        for (int m = 0; m < i; m++)
            Y[i] -= L[i][m] * Y[m];
        Y[i] /= L[i][i];
    }

    // Вывод вектора Y
    cout << "Vector Y:\n";
    for (int i = 0; i < n; i++)
        cout << Y[i] << " ";
    cout << endl;

    // 3 этап

    // Вычисление X
    double X[n];
    X[n - 1] = Y[n - 1] / U[n - 1][n - 1];

    for (int i = n - 2; i >= 0; i--) {
        X[i] = Y[i];
        for (int m = i + 1; m < n; m++)
            X[i] -= U[i][m] * X[m];
        X[i] /= U[i][i];
    }

    // Вывод вектора X
    cout << "Solution X:\n";
    for (int i = 0; i < n; i++)
        cout << X[i] << " ";
    cout << endl;
}
