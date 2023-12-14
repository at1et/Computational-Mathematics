#include <iostream>

using namespace std;

const int n = 5;  // Размерность матрицы и вектора

// Функция для вывода матрицы
void printMatrix(double mat[][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

// Функция для LU-разложения
void luDecomposition(double mat[][n], double L[][n], double U[][n]) {
    for (int i = 0; i < n; i++) {
        for (int k = i; k < n; k++) {
            double sum = 0;
            // Рассчитываем элемент матрицы U
            for (int j = 0; j < i; j++)
                sum += (L[i][j] * U[j][k]);
            U[i][k] = mat[i][k] - sum;
        }

        for (int k = i; k < n; k++) {
            if (i == k)
                L[i][i] = 1; // Устанавливаем диагональные элементы L равными 1
            else {
                double sum = 0;
                // Рассчитываем элемент матрицы L
                for (int j = 0; j < i; j++)
                    sum += (L[k][j] * U[j][i]);
                L[k][i] = (mat[k][i] - sum) / U[i][i];
            }
        }
    }
}

// Функция для решения системы линейных уравнений
void solveSystem(double L[][n], double U[][n], double B[], double X[]) {
    double Y[n];

    // Решение LY = B
    for (int i = 0; i < n; i++) {
        double sum = 0;
        // Рассчитываем элементы вектора Y
        for (int j = 0; j < i; j++)
            sum += L[i][j] * Y[j];
        Y[i] = B[i] - sum;
    }

    // Решение UX = Y
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0;
        // Рассчитываем элементы вектора X
        for (int j = i + 1; j < n; j++)
            sum += U[i][j] * X[j];
        X[i] = (Y[i] - sum) / U[i][i];
    }
}

int main() {
    double A[n][n] = { {9, 1, 5, 7, 6},
                      {5, 2, 4, 9, 9},
                      {1, 5, 5, 3, 7},
                      {1, 7, 8, 2, 6},
                      {3, 1, 2, 1, 2} };

    double L[n][n] = { 0 };  // Матрица L
    double U[n][n] = { 0 };  // Матрица U
    double B[n] = { 28, 29, 21, 24, 9 };  // Вектор свободных членов (исправленный)
    double X[n] = { 0 };  // Вектор решения

    luDecomposition(A, L, U);  // Выполнение LU-разложения

    cout << "Matrix L:\n";
    printMatrix(L);

    cout << "Matrix U:\n";
    printMatrix(U);

    solveSystem(L, U, B, X);  // Решение системы линейных уравнений

    cout << "Solution X:\n";
    for (int i = 0; i < n; i++)
        cout << X[i] << " ";

}
