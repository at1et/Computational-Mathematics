#include <iostream>
#include <vector>

using namespace std;

// Функция для вывода матрицы
void printMatrix(vector<vector<double>>& mat) {
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[0].size(); j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    const int n = 5;  // Размерность матрицы и вектора

    // Определение массивов
    vector<vector<double>> A = {
        {3, 8, 2, 2, 8},
        {4, 5, 9, 9, 9},
        {2, 9, 8, 9, 6},
        {4, 3, 7, 4, 3},
        {3, 1, 9, 8, 4}
    };

    vector<vector<double>> L(n, vector<double>(n, 0));
    vector<vector<double>> U(n, vector<double>(n, 0));
    vector<vector<double>> Y(n, vector<double>(n, 0));
    vector<vector<double>> X(n, vector<double>(n, 0));
    vector<vector<double>> AInv(n, vector<double>(n, 0));

    // Вычисление матриц L и U
    for (int i = 0; i < n; i++) {
        L[i][0] = A[i][0];
    }

    for (int j = 1; j < n; j++) {
        U[0][j] = A[0][j] / L[0][0];
    }

    for (int k = 1; k < n; k++) {
        for (int i = k; i < n; i++) {
            L[i][k] = A[i][k];
            for (int m = 0; m < k; m++) {
                L[i][k] -= L[i][m] * U[m][k];
            }
        }

        if (k <= n - 2) {
            for (int j = k + 1; j < n; j++) {
                U[k][j] = A[k][j];
                for (int m = 0; m < k; m++) {
                    U[k][j] -= L[k][m] * U[m][j];
                }
                U[k][j] /= L[k][k];
            }
        }
    }

    // Вычисление матрицы Y
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j > i) {
                Y[i][j] = 0;
            } else if (j == i) {
                Y[i][j] = 1 / L[i][i];
            } else {
                double sum = 0;
                for (int m = j; m < i; m++) {
                    sum += L[i][m] * Y[m][j];
                }
                Y[i][j] = -sum / L[i][i];
            }
        }
    }

    // Вычисление матрицы X
    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            if (j < i) {
                X[i][j] = 0;
            } else if (j == i) {
                X[i][j] = 1;
            } else {
                double sum = 0;
                for (int m = i + 1; m <= j; m++) {
                    sum += U[i][m] * X[m][j];
                }
                X[i][j] = -sum;
            }
        }
    }

    // Вычисление и вывод матрицы, обратной к A
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            AInv[i][j] = 0;
            for (int m = 0; m < n; m++) {
                AInv[i][j] += X[i][m] * Y[m][j];
            }
        }
    }

    // Вывод обратной матрицы
    cout << "Inverse of matrix A:\n";
    printMatrix(AInv);

    return 0;
}
