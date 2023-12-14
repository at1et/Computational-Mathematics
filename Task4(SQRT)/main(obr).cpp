#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

// Показать матрицу
void ShowMatrix(vector<vector<double>>& Matrix) {
    for (int i = 0; i < Matrix.size(); i++) {
        for (int j = 0; j < Matrix[0].size(); j++) {
            cout << fixed << Matrix[i][j] << "      ";  // Вывод элемента матрицы с фиксированным числом знаков после запятой
        }
        cout << endl;
    }
    cout << endl;
}

// LU-разложение матрицы
void Matrix_L(vector<vector<double>>& Matrix, vector<vector<double>>& L) {
    int n = Matrix.size();
    L[0][0] = pow(Matrix[0][0], 0.5);  // Инициализация первого элемента матрицы L
    for (int i = 1; i < n; i++) {
        L[i][0] = Matrix[i][0] / L[0][0];  // Вычисление элементов первого столбца матрицы L
    }

    for (int k = 1; k < n; k++) {
        double sum = 0;
        for (int i = 0; i < k; i++) {
            sum = sum + pow(L[k][i], 2);  // Вычисление суммы квадратов элементов
        }
        L[k][k] = pow(Matrix[k][k] - sum, 0.5);  // Вычисление диагональных элементов матрицы L

        for (int i = k + 1; i < n; i++) {
            double sum2 = 0;
            for (int j = 0; j < k; j++) {
                sum2 = sum2 + L[i][j] * L[k][j];  // Вычисление элементов ниже диагонали матрицы L
            }
            L[i][k] = (Matrix[i][k] - sum2) / L[k][k];  // Заполнение элементов ниже диагонали матрицы L
        }
    }
}

// Получение матрицы Y
void Matrix_Y(vector<vector<double>>& L, vector<vector<double>>& Y) {
    int n = L.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j > i) {
                Y[i][j] = 0;  // Элементы выше главной диагонали матрицы Y
            }
            else if (j == i) {
                Y[i][j] = 1 / L[i][j];  // Диагональные элементы матрицы Y
            }
            else {
                double sum = 0;
                for (int m = j; m < i; m++) {
                    sum = sum + L[i][m] * Y[m][j];  // Элементы ниже главной диагонали матрицы Y
                }
                Y[i][j] = (-1) / L[i][i] * sum;  // Заполнение элементов ниже главной диагонали матрицы Y
            }
        }
    }
}

// Получение матрицы A
void Matrix_A(vector<vector<double>>& Y, vector<vector<double>>& A) {
    int n = Y.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = 0;
            for (int m = 0; m < n; m++) {
                A[i][j] = A[i][j] + Y[m][i] * Y[m][j];  // Получение матрицы A
            }
        }
    }
}

int main() {
    // Исходная матрица
    vector<vector<double>> Matrix {{7, 2, 3, 1}, {2, 9, 4, 1}, {3, 4, 8, 5}, {1, 1, 5, 7}};
    
    // Матрицы L, Y, A
    vector<vector<double>> L; vector<vector<double>> Y; vector<vector<double>> A;
    L.resize(Matrix.size()); Y.resize(Matrix.size()); A.resize(Matrix.size());
    for (int i = 0; i < L.size(); i++) { L[i].resize(Matrix[i].size()); }
    for (int i = 0; i < Y.size(); i++) { Y[i].resize(Matrix[i].size()); }
    for (int i = 0; i < A.size(); i++) { A[i].resize(Matrix[i].size()); }

    // Вывод исходной матрицы
    ShowMatrix(Matrix);

    // LU-разложение матрицы
    Matrix_L(Matrix, L);

    // Вывод матрицы L
    ShowMatrix(L);

    // Получение матрицы Y
    Matrix_Y(L, Y);

    // Вывод матрицы Y
    ShowMatrix(Y);

    // Получение матрицы A
    Matrix_A(Y, A);

    // Вывод матрицы A
    ShowMatrix(A);

    return 0;
}
