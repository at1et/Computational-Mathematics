#include <iostream>
using namespace std;
//a) f(x) = 7x + 5^x - 2 = 0
double f1(double x) {
	return 7 * x + pow(5, x) - 2;
}
//a') f'(x) = 5^x * ln(5) + 7 (ln(5) = 1,609437)
double f11(double x) {
	return 7 + pow(5, x) * 1, 609437;
}
//a")f"(x) = 5^x * ln(5)^2 (ln(5)^2 = 2.59029)
double f111(double x) {
	return pow(5, x) * 2.59029;
}

// b) f(x) = -2x^3 - x^2 + 5x + 1 = 0
double f2(double x) {
	return -2 * pow(x, 3) - pow(x, 2) + 5 * x + 1;
}

// b') f'(x) = -6x^2 - 2x + 5
double f22(double x) {
	return -6 * pow(x, 2) - 2 * x + 5;
}

// b") f"(x) = -12x - 2
double f222(double x) {
	return -12 * x - 2;
}

// Вычисление методом половинного деления 1
double HalfDiv1(double a, double b, double eps) {
	double c;
	while (b - a > 2 * eps) {
		c = (a + b) / 2;
		if (f1(a) * f1(c) < 0) {
			b = c;
		}
		else if (f1(b) * f1(c) < 0) {
			a = c;
		}
	}
	return (a + b) / 2;
}

// Вычисление методом половинного деления 2
void HalfDiv2(double a, double b, double eps) {
	double c;
	while (b - a > 2 * eps) {
		c = (a + b) / 2;
		if (f2(a) * f2(c) < 0) {
			b = c;
		}
		else if (f2(b) * f2(c) < 0) {
			a = c;
		}
	}
	cout << "x = " << (a + b) / 2 << endl;
}

// Вычисление методом половинного деления 2 на всех промежутках
void SearchHalfDiv2() {
	for (int i = -100; i < 100; i++)
	{
		if (f2(i) * f2(i + 1) < 0) {
			HalfDiv2(i, i + 1, 0.0001);
		}
	}
}

// Вычисление хорд и касательных 1
void HordAndKas1(double a, double b, double eps) {
	double d, c;
	while (b - a > 2 * eps) {
		if (f1(a) * f111(a) > 0) {
			d = a - f1(a) / f11(a);
			c = (a * f1(b) - b * f1(a)) / (f1(b) - f1(a));
			a = d; b = c;
		}
		else if (f1(b) * f111(b) > 0) {
			d = b - f1(b) / f11(b);
			c = (a * f1(b) - b * f1(a)) / (f1(b) - f1(a));
			b = d; a = c;
		}
	}
	cout << "x = " << (a + b) / 2 << endl;
}

// Вычисление хорд и касательных 2
void HordAndKas2(double a, double b, double eps) {
	double d, c;
	while (b - a > 2 * eps) {
		if (f2(a) * f222(a) > 0) {
			d = a - f2(a) / f22(a);
			c = (a * f2(b) - b * f2(a)) / (f2(b) - f2(a));
			a = d; b = c;
		}
		else if (f2(b) * f222(b) > 0) {
			d = b - f2(b) / f22(b);
			c = (a * f2(b) - b * f2(a)) / (f2(b) - f2(a));
			b = d; a = c;
		}
	}
	cout << "x = " << (a + b) / 2 << endl;
}

// Вычисление методом хорд и касательных 2 на всех промежутках
void SearchHordAndKas2() {
	for (int i = -100; i < 100; i++)
	{
		if (f2(i) * f2(i + 1) < 0) {
			HordAndKas2(i, i + 1, 0.0001);
		}
	}
}

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	double a, b, c, x, eps;
	a = 0; b = 1; eps = 0.00000013;
	// Решение первого
	// Половинное деление
	cout << "*** Уравнение 1 ***" << endl;
	cout << "Половинное деление " << endl;
	x = HalfDiv1(a, b, eps);
	cout << "x = " << x << endl;
	// Хорды и касательные
	cout << "Хорды и касательные " << endl;
	HordAndKas1(a, b, eps);
	// Решение второго
	cout << " " << endl;;
	cout << "*** Уравнение 2 ***" << endl;;
	cout << "Половинное деление " << endl;
	SearchHalfDiv2();
	cout << "Хорды и касательные " << endl;
	SearchHordAndKas2();
}
