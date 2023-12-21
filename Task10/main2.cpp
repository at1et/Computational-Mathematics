#include <iostream>
using namespace std;

double f1(double x)
{
    return (4 * x + pow(2, x) + 6);
}

double f2(double x)
{
    return -2 * pow(x, 3) - 2 * pow(x, 2) + 2 * x + 5;
}
double f2p(double x)
{
    return -6 * pow(x, 2) - 4 * x + 2;
}
double f2pp(double x)
{
    return -12 * x - 4;
}

double MetodPopolam()
{
    int n = 0;
    double a = -2;
    double b = -1;
    double c = (a + b) / 2;
    int eps = 0.0001;
    while ((b - a) >= 2 * eps)
    {
        if (f1(a) * f1(c) < 0)
        {
            b = c;
        }
        else
        {
            if (f1(b) * f1(c) < 0)
            {
                a = c;
            }
            else {
                if (f1(c) == 0) { {break; };
                }
            }
        }
        c = (a + b) / 2;
        n = n + 1;

    }
    return c;

}
double KombMetod(double a, double b)
{
    double eps = 0.0001;
    double d, c;
    while (abs(b - a) > eps)
    {
        if (f2(a) * f2pp(a) > 0)
        {
            d = a - f2(a) / f2p(a);
            c = (a * f2(b) - b * f2(a)) / (f2(b) - f2(a));
            a = d;
            b = c;
        }
        else
        {
            if (f2(b) * f2pp(b) > 0)
            {
                d = b - f2(b) / f2p(b)*1.0;
                c = (a * f2(b) - b * f2(a)) / (f2(b) - f2(a) * 1.0);
                b = d;
                a = c;
            }
            else
            {
                break;
            }
        };

    };
    return (a+b)/2.0;
}

int main()
{
    cout << MetodPopolam() << endl;

    cout << KombMetod(1, 1.5) << endl;

    cout << KombMetod(-1.5, -0.5) << endl;

    cout << KombMetod(0, 0.5) << endl;

    cout << KombMetod(-0.5, 0) << endl;
}
