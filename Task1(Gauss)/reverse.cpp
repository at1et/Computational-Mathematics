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
    // Размер исходной матрицы
    int n = 4;

    // Создаем расширенную матрицу
    vector<vector<double>> B = {
        {3, 8, 2, 2, 8},
        {4, 5, 9, 9, 9},
        {2, 9, 8, 9, 6},
        {4, 3, 7, 4, 3}
    };

    // Пересчет по методу Жордана-Гаусса
    for (int k = 0; k < n; k++) {
        // Методом прямоугольника пересчитываем все элементы правее ведущего столбца и не в ведущей строке
        for (int i = 0; i < n; i++) {
            for (int j = k + 1; j < n + 1; j++) {  // Исправлено ограничение до n + 1
                if (i != k) {
                    B[i][j] = (B[i][j] * B[k][k] - B[k][j] * B[i][k]) / B[k][k];
                }
            }
        }

        // Обнуляем элементы ведущего столбца (кроме ведущего элемента)
        for (int i = 0; i < n; i++) {
            if (i != k) {
                B[i][k] = 0;
            }
        }

        // Делим ведущую строку на ведущий элемент
        for (int j = n; j >= k; j--) {  // Исправлено ограничение до n
            B[k][j] = B[k][j] / B[k][k];
        }

        // Выводим на экран очередную матрицу
        cout << "Matrix after iteration " << k + 1 << ":\n";
        printMatrix(B);
        cout << endl;
    }

    return 0;
}
