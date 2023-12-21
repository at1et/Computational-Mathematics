#include <iostream>
#include <vector>

using namespace std;

void printMatrix(vector<vector<double>>& mat) {
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[0].size(); j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    const int n = 5;

    // Определение массивов
    vector<vector<double>> A = {
        {9, 7, 3, 6, 1},
        {7, 9, 3, 7, 3},
        {3, 3, 8, 4, 2},
        {6, 7, 4, 9, 3},
        {1, 3, 2, 3, 2}
    };

    vector<vector<double>> L(n, vector<double>(n, 0));
    vector<vector<double>> Y(n, vector<double>(n, 0));
    vector<vector<double>> AInv(n, vector<double>(n, 0));

    // Этап №1: Заполнение матрицы L
    for (int i = 0; i < n; i++) {
        L[i][0] = sqrt(A[i][0]);
    }

    for (int i = 1; i < n; i++) {
        L[i][0] = A[i][0] / L[0][0];
    }

    for (int k = 1; k < n; k++) {
        double sqSum = 0;
        for (int m = 0; m < k; m++) {
            sqSum += L[k][m] * L[k][m];
        }
        L[k][k] = sqrt(A[k][k] - sqSum);

        if (k < n - 1) {
            for (int i = k + 1; i < n; i++) {
                double pairSum = 0;
                for (int m = 0; m < k; m++) {
                    pairSum += L[i][m] * L[k][m];
                }
                L[i][k] = (A[i][k] - pairSum) / L[k][k];
            }
        }
    }

    // Этап №2: Заполнение матрицы Y
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j > i) {
                Y[i][j] = 0;
            }
            else if (j == i) {
                Y[i][j] = 1 / L[i][i];
            }
            else {
                double sum = 0;
                for (int m = j; m < i; m++) {
                    sum += L[i][m] * Y[m][j];
                }
                Y[i][j] = -sum / L[i][i];
            }
        }
    }

    // Этап №3: Вычисление матрицы, обратной к A
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            AInv[i][j] = 0;
            for (int m = 0; m < n; m++) {
                AInv[i][j] += Y[m][i] * Y[m][j];
            }
        }
    }

    // Вывод матрицы, обратной к A
    cout << "Matrix A:\n";
    printMatrix(AInv);

    return 0;
}
