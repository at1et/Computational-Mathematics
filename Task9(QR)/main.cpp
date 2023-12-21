#include <iostream>
#include <cmath>

int main() {
    setlocale(LC_ALL, "Russian");
        const int n = 5;
    double A[n][n] = { {3, 8, 2, 2, 8},
                      {4, 5, 9, 9, 9},
                      {2, 9, 8, 9, 6},
                      {4, 3, 7, 4, 3},
                      {3, 1, 9, 8, 4} };
    double Q[n][n];
    double R[n][n] = { 0 };

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            Q[i][j] = A[i][j];
        }
    }

    for (int j = 0; j < n; ++j) {
        double SQsum = 0;
        for (int m = 0; m < n; ++m) {
            SQsum += Q[m][j] * Q[m][j];
        }

        R[j][j] = sqrt(SQsum);

        for (int i = 0; i < n; ++i) {
            Q[i][j] /= R[j][j];
        }

        for (int k = j + 1; k < n; ++k) {
            for (int m = 0; m < n; ++m) {
                R[j][k] += Q[m][j] * Q[m][k];
            }
            for (int i = 0; i < n; ++i) {
                Q[i][k] -= Q[i][j] * R[j][k];
            }
        }
    }

    std::cout << "Матрица Q:" << std::endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << Q[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Матрица R:" << std::endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << R[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
