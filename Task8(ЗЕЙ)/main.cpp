//Полуэктов Андрей
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    const int n = 5;
    const float eps = 0.0001;
    int iter = 0;

    vector<vector<double>> matrix = {
        {41, 1, 5, 2, 1, 63},   // Уравнение 1
        {2, 30, 4, 1, 2, 78},   // Уравнение 2
        {1, 1, 22, 3, 3, 78},   // Уравнение 3
        {3, 3, 5, 24, 1, 73},   // Уравнение 4
        {3, 5, 5, 3, 33, 67}    // Уравнение 5
    };
    vector<double> x_old{ 0,0,0,0,0 };
    vector<double> x_new{ 0,0,0,0,0 };
    
    bool flag = true;
    while (true) {
        flag = true;
        iter++;
        for (int k = 0; k < n; k++) {
            x_new[k] = matrix[k][5];
            for (int j = 0; j < n; j++)  // Исправленная строка
                if (j != k)
                    x_new[k] = x_new[k] - matrix[k][j] * x_new[j];
            if (abs(x_new[k] - x_old[k]) < eps)
                flag = false;
        }
        cout << "Итерация: " << iter << ";";
        for (int i = 0; i < n; i++)
            cout << x_new[i] << "   ";
        cout << "\n";
        for (int i = 0; i < n; i++)
            x_old[i] = x_new[i];
        if (flag == false)
            break;
    }
}
