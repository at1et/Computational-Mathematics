#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Создаем матрицу системы уравнений, включая правую часть
    vector<vector<double>> matrix = {
        {3.04, 8.39, 4.6, 5.45, 6.95, 5.84},   // Уравнение 1
        {8.18, 2.85, 9.71, 0.26, 6.49, 5.78},   // Уравнение 2
        {7.06, 9.67, 5.62, 2.57, 7.27, 4.33},   // Уравнение 3
        {1.5, 8.94, 7.22, 6.78, 5.07, 6.31},   // Уравнение 4
        {4.09, 6.16, 2.15, 8.38, 9.73, 5.07}    // Уравнение 5
    };

    int n = matrix.size();  // Определяем размерность системы уравнений

    // Прямой ход метода Гаусса: приведение матрицы к верхнетреугольному виду
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double factor = matrix[j][i] / matrix[i][i];  // Вычисление коэффициента для обнуления элемента
            for (int k = i; k < n + 1; k++) {
                matrix[j][k] -= factor * matrix[i][k];  // Обнуление элемента под диагональю
            }
        }
    }

    vector<double> result(n);  // Создаем вектор для хранения решений

    // Обратный ход метода Гаусса: нахождение решений
    for (int i = n - 1; i >= 0; i--) {
        result[i] = matrix[i][n] / matrix[i][i];  // Вычисление решения для x_i
        for (int j = i - 1; j >= 0; j--) {
            matrix[j][n] -= matrix[j][i] * result[i];  // Обновление правой части
        }
    }

    // Вывод решений на экран
    cout << "Result:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "x" << i << " = " << result[i] << endl;
    }

    return 0;
}