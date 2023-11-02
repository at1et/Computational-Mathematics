#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Создаем матрицу системы уравнений, включая правую часть
    vector<vector<double>> matrix = {
        {3.04, 8.39, 4.6, 5.45, 6.95, 5.84},
        {8.18, 2.85, 9.71, 0.26, 6.49, 5.78},
        {7.06, 9.67, 5.62, 2.57, 7.27, 4.33},
        {1.5, 8.94, 7.22, 6.78, 5.07, 6.31},
        {4.09, 6.16, 2.15, 8.38, 9.73, 5.07}
    };

    int n = matrix.size();

    // Прямой и обратный ход метода Жордана-Гаусса
    for (int i = 0; i < n; i++) {
        // Преобразуем текущий элемент главной диагонали в 1
        double diagonalElement = matrix[i][i];
        for (int j = i; j < n + 1; j++) {
            matrix[i][j] /= diagonalElement;
        }

        // Обнуляем элементы под и над главной диагональю
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = matrix[k][i];
                for (int j = i; j < n + 1; j++) {
                    matrix[k][j] -= factor * matrix[i][j];
                }
            }
        }
    }

    vector<double> result(n);

    // Получаем решения
    for (int i = 0; i < n; i++) {
        result[i] = matrix[i][n];
    }

    // Выводим решения на экран
    cout << "Решение системы:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "x" << i << " = " << result[i] << endl;
    }

    return 0;
}
