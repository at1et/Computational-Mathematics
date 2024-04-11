#include <iostream>
#include <iomanip> // Для установки точности вывода
using namespace std;

// Функция для ввода координат точек
void input_coord(double* x, double* y, unsigned n) {
    for (unsigned i = 0; i < n; i++) {
        cout << "Введите x" << i + 1 << ": ";
        cin >> x[i];
        cout << "Введите y" << i + 1 << ": ";
        cin >> y[i];
    }
}

// Функция для печати матрицы (двумерного массива)
void print_matrix(double** a, unsigned n)
{
    for (unsigned i = 0; i < n; i++)
    {
        for (unsigned j = 0; j < n; j++)
            cout << a[i][j] << " ";

        cout << "\n";
    }
    cout << "\n";
}

// Функция для вывода координат точек
void print_coord(double* x, double* y, unsigned n) {
    for (unsigned i = 0; i < n; i++)
        cout << x[i] << " ; " << y[i] << endl;
}

// Функция для вычисления таблицы разделённых разностей
double** matr_razdel_razn(double* x, double* y, unsigned n) {
    double** a = new double* [n]; // Выделение памяти для двумерного массива
    for (unsigned i = 0; i < n; i++) {
        a[i] = new double[n] {0}; // Инициализация значений 0
        a[i][0] = y[i]; // Заполнение первого столбца значениями y
    }

    // Заполнение остальных столбцов таблицы разделённых разностей
    for (unsigned j = 1; j < n; j++) {
        for (unsigned i = 0; i < n - j; i++) {
            double num = a[i + 1][j - 1] - a[i][j - 1];
            double den = x[i + j] - x[i];
            a[i][j] = num / den;
        }
    }

    return a; // Возвращение таблицы разделённых разностей
}

// Функция для вычисления значения интерполяционного полинома методом Ньютона в прямом направлении
double NF(double* x, double** y, unsigned n, double x0) {
    double a = y[0][0]; // Начальное значение полинома
    double d = 1;
    for (unsigned i = 1; i < n; i++) {
        d = d * (x0 - x[i - 1]); // Вычисление значения базисной функции
        a = a + y[0][i] * d; // Добавление к полиному следующего члена
    }
    return a; // Возвращение значения интерполяции
}

// Функция для вычисления значения интерполяционного полинома методом Ньютона в обратном направлении
double NB(double* x, double** y, unsigned n, double x0) {
    double a = y[n - 1][0]; // Начальное значение полинома
    double d = 1;
    for (unsigned i = 1; i < n; i++) {
        d = d * (x0 - x[n - i]); // Вычисление значения базисной функции
        a = a + y[n - 1 - i][i] * d; // Добавление к полиному следующего члена
    }
    return a; // Возвращение значения интерполяции
}

int main()
{
    setprecision(5); // Установка точности вывода
    setlocale(LC_ALL, "RUS");
    cout << "Введите кол-во точек: ";
    unsigned n;
    cin >> n;

    // Выделение памяти для массивов
    double* x = new double[n]; 
    double* y = new double[n]; 

    input_coord(x, y, n); // Ввод координат точек
    cout << "Точки\n";
    print_coord(x, y, n); // Вывод координат точек

    double** Y = matr_razdel_razn(x, y, n); // Вычисление таблицы разделённых разностей
    print_matrix(Y, n); // Вывод таблицы разделённых разностей

    double X = 0; // Точка, в которой вычисляется интерполяция

    double y_next = NF(x, Y, n, X); // Вычисление интерполяции в прямом направлении
    double y_back = NB(x, Y, n, X); // Вычисление интерполяции в обратном направлении

    // Вывод результатов
    cout << "Y Forward: " << y_next << endl;
    cout << "Y Back: " << y_back << endl;
}
