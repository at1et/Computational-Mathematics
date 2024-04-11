#include <iostream>
using namespace std;

/// Ввод координат точек
void input_coordinate(double* x, double* y, unsigned n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "Введите x" << i + 1 << ": ";
        cin >> x[i];
        cout << "Введите y" << i + 1 << ": ";
        cin >> y[i];
    }
}

/// Вывод координат точек
void print_coordinate(double* x, double* y, unsigned n)
{
    cout << "Точки" << endl;
    for (int i = 0; i < n; i++)
        cout << x[i] << ", " << y[i] << endl;
}

int main() {
    setlocale(0, "Russian");
    cout << "Введите кол-во точек: ";
    int n;
    cin >> n;

    double* x = new double[n];
    double* y = new double[n];
    double* z = new double[n];
    double* a = new double[n]{0};
    double* b = new double[n]{0};
    double* c = new double[n]{0};

    input_coordinate(x, y, n); // Ввод координат точек
    print_coordinate(x, y, n); // Вывод координат точек

    z[0] = -1;

    // Вычисление коэффициентов кубического сплайна
    for (int i = 1; i < n; i++) {
        double d = x[i] - x[i - 1];
        double e = y[i] - y[i - 1];
        a[i] = e / (d * d) - z[i - 1] / d;
        b[i] = 2 * e / d - z[i - 1];
        c[i] = y[i];
        z[i] = b[i];
    }

    cout << "Коэф-ты a" << endl;
    for (int i = 0; i < n; i++) {
        cout << a[i] << endl;
    }
    cout << "Коэф-ты b" << endl;
    for (int i = 0; i < n; i++) {
        cout << b[i] << endl;
    }
    cout << "Коэф-ты c" << endl;
    for (int i = 0; i < n; i++) {
        cout << c[i] << endl;
    }

    cout << "Производная" << endl;
    for (int i = 0; i < n; i++) {
        cout << z[i] << endl;
    }
}
