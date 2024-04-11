#include <iostream>
using namespace std;

// Функция для печати матрицы (двумерного массива)
void print_matrix(double** a, unsigned n)
{
	for (unsigned i = 0; i < n; i++)
	{
		for (unsigned j = 0; j < n + 1; j++)
			cout << a[i][j] << " ";

		cout << "\n";
	}
	cout << "\n";
}

// Функция для обмена строк матрицы, чтобы избежать деления на ноль
void swap_string(double** a, unsigned n, unsigned num, double EPS)
{
	unsigned i = num;
	while (a[i][num] < EPS)
	{
		if (i == n - 1) return;
		else i++;
	}

	for (unsigned j = 0; j < n + 1; j++)
	{
		float buf = a[num][j];
		a[num][j] = a[i][j];
		a[i][j] = buf;
	}
}

// Функция для ввода координат точек
void input_coord(double* x, double* y, unsigned n) {
	for (unsigned i = 0; i < n; i++) {
		cout << "Введите x" << i + 1 << ": ";
		cin >> x[i];
		cout << "Введите y" << i + 1 << ": ";
		cin >> y[i];
	}
}

// Функция для печати координат точек
void print_coord(double* x, double* y, unsigned n) {
	for (unsigned i = 0; i < n; i++)
		cout << x[i] << " ; " << y[i] << endl;
}

// Функция для создания матрицы для метода наименьших квадратов
double** create_matrix(double* x, double* y, unsigned n) {
	double** a = new double* [n]; // Строки
	for (unsigned i = 0; i < n; i++)
		a[i] = new double[n + 1]; // Столбцы

	// Заполнение матрицы
	for (unsigned i = 0; i < n; i++) {
		for (unsigned j = 0; j < n; j++)
			a[i][j] = pow(x[i], j); // Заполнение степенями x
		a[i][n] = y[i]; // Последний столбец - значения y
	}
	return a;
}

// Функция, реализующая правило прямоугольника для метода Гаусса
double rule_primoygol(double** a, unsigned i, unsigned j, unsigned k)
{
	return (a[i][j] * a[k][k] - a[i][k] * a[k][j]) / a[k][k];
}

// Функция для метода Гаусса
double* Jardan_Gauss(double** a, unsigned n)
{
	int i, j, k;
	const  double E = 0.0001;

	double* b = new double[n] {0}; // Вектор для решений

	for (k = 0; k < n; k++) // Прямой ход метода Гаусса
	{
		if (abs(a[k][k]) < E) // Проверка на ноль на диагонали
		{
			if (k < n - 1) // Если не последняя строка
			{
				swap_string(a, n, k, E); // Меняем строки местами
				cout << "Поменяли строки" << "\n"; // Вывод сообщения
				print_matrix(a, n); // Печать матрицы после обмена
			}
		}

		// Пересчёт правилом прямоугольника
		for (i = 0; i < n; i++)
			if (i != k)
				for (j = 0; j < n + 1; j++)
					if (j != k)
						a[i][j] = rule_primoygol(a, i, j, k);

		// Деление строки на элемент
		for (j = n; j >= k; j = j - 1)
			a[k][j] = a[k][j] / a[k][k];

		// Обнуление ниже, выше и правее
		for (i = 0; i < n; i++)
			if (i != k) a[i][k] = 0;

		print_matrix(a, n); // Печать матрицы после преобразований
	}

	// Обратный ход метода Гаусса
	for (k = n - 1; k >= 0; k--)
	{
		b[k] = a[k][n]; // Заполнение вектора решений
	}

	return b; // Возвращение вектора решений
}

// Функция для печати вектора решений
void print_answ(double* a, unsigned n)
{
	for (unsigned i = 0; i < n; i++)
		cout << a[i] << endl;
}

int main()
{
	setlocale(LC_ALL, "RUS"); // Установка локали для вывода на кириллице
	cout << "Введите кол-во точек: ";
	unsigned n;
	cin >> n;

	double* x = new double[n]; // Выделение памяти для массива x
	double* y = new double[n]; // Выделение памяти для массива y

	input_coord(x, y, n); // Ввод координат точек
	cout << "\n";
	cout << "Точки" << endl;
	print_coord(x, y, n); // Печать координат точек

	cout << "Матрица:\n";
	double** matr = create_matrix(x, y, n); // Создание матрицы для метода Гаусса
	print_matrix(matr, n); // Печать матрицы

	double* ans = Jardan_Gauss(matr, n); // Вызов метода Гаусса для решения системы уравнений
	cout << "Коэф-ты\n";
	print_answ(ans, n); // Печать вектора решений
}
