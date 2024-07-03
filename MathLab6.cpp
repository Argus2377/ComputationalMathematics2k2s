#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::cos;
using std::setw;
using std::setprecision;

double h{ 0.1 };

double func(double x, double y, int q)
{
	switch (q)
	{
	case 1:
	{
		return x + sin(y / sqrt(11));
	}

	case 2:
	{
        return 1 + 2.2 * sin(x) + 1.5 * y * y;
	}

	default:
	{
		return 1;
	}
	}
}

void Adams(vector<vector<double>>& res, double x, double xn, double y, int q) //Метод Адамса
{
    res.resize(2); //Создаём вектор
    res[0].resize(11);
    res[1].resize(11);

    res[0][0] = x; //Добавляем в массив начальные условия
    res[1][0] = y;

    double K[4]{}; //Массив для расчета методом Рунге-Кутта
    double df[3]{}; //Массив для вычисления методом Адамса

    for (int i = 1; i < 4; i++) //Метод Рунге-Кутта
    {
        K[0] = func(x, y, q);
        K[1] = func(x + h / 4.0, y + (h / 4.0) * K[0], q);
        K[2] = func(x + h / 2.0, y + (h / 2.0) * K[1], q);
        K[3] = func(x + h, y + h * K[0] - 2.0 * h * K[1] + 2.0 * h * K[2], q);

        y += (h * (K[0] + 2.0 * K[1] + 2.0 * K[2] + K[3])) / 6.0;
        x += h;

        res[0][i] = x;
        res[1][i] = y;
    }

    for (int i = 4; i < 11; i++) //Метод Адамса
    {
        df[0] = res[1][i] - res[1][i - 1];
        df[1] = res[1][i] - 2.0 * res[1][i - 1] + res[1][i - 2];
        df[2] = res[1][i] - 3.0 * res[1][i - 1] + 3.0 * res[1][i - 2] - res[1][i - 3];

        y += h * func(x, y, q) + (df[0] * h * h / 2.0) + 5.0 * (df[1] * h * h * h / 12.0) + 3.0 * (df[2] * h * h * h * h / 8.0);
        x += h;

        res[0][i] = x;
        res[1][i] = y;
    }

}


void RungeKutt(vector<vector<double>>& res, double x, double xn, double y, int q)
{
    res.resize(2);
    res[0].push_back(x);
    res[1].push_back(y);

    double K[4]{};

    while (x <= xn) //Вычисление остальных точек
    {
        K[0] = func(x, y, q);
        K[1] = func(x + h / 4.0, y + (h / 4.0) * K[0], q);
        K[2] = func(x + h / 2.0, y + (h / 2.0) * K[1], q);
        K[3] = func(x + h, y + h * K[0] - 2.0 * h * K[1] + 2.0 * h * K[2], q);

        y += (h * (K[0] + 2.0 * K[1] + 2.0 * K[2] + K[3])) / 6.0;
        x += h;

        res[0].push_back(x);
        res[1].push_back(y);
    }
}


void Euler(vector<vector<double>>& res, double x, double xn, double y, int q) //Метод Эйлера
{
    res.resize(2);
    res[0].push_back(x);
    res[1].push_back(y);

    while (x <= xn) //Вычисление остальных точек
    {
        y += h * func(x, y, q);
        x += h;

        res[0].push_back(x);
        res[1].push_back(y);
    }
}


void EulerRecalculation(vector<vector<double>>& res, double x, double xn, double y, int q) //Метод Эйлера с перерасчётом
{
    res.resize(2);
    res[0].push_back(x);
    res[1].push_back(y);

    double _y; //Переменная для перерасчёта
    int i{ 1 };

    while (x <= xn)
    {
        _y = y + h * func(x, y, q);
        y += 0.5 * h * (func(x, y, q) + func(x, _y, q));
        x += h;

        res[0].push_back(x);
        res[1].push_back(y);

        i++;
    }
}

void print(const vector<vector<double>>& res)
{
    cout << "+-----------+";
    for (unsigned int q = 0; q < res[0].size(); q++)
    {
        cout << "-----------+";
    }
    cout << endl << "|     x     |";
    for (unsigned int q = 0; q < res[0].size(); q++)
    {
        cout << setw(11) << setprecision(5) << res[0][q] << "|";
    }
    cout << endl << "+-----------+";
    for (unsigned int q = 0; q < res[0].size(); q++)
    {
        cout << "-----------+";
    }
    cout << endl << "|     y     |";
    for (unsigned int q = 0; q < res[0].size(); q++)
    {
        cout << setw(11) << setprecision(5) << res[1][q] << "|";
    }
    cout << endl << "+-----------+";
    for (unsigned int q = 0; q < res[0].size(); q++)
    {
        cout << "-----------+";
    }
    cout << endl << endl;
}


int main()
{
    double x{0.6}; //Начальные условия для первой задачи
    double xn{1.6};
    double y{1.2};

    vector<vector<double>> result; //Вектор с результатами

    cout << "+-----------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "+------------------------------------------------------------------- Task 1 --------------------------------------------------------------------+" << endl;
    cout << "+-----------------------------------------------------------------------------------------------------------------------------------------------+" << endl << endl;

    cout << "Euler:\n";
    Euler(result, x, xn, y, 1);
    print(result);
    result.clear();

    cout << "Euler Recalculation:\n";
    EulerRecalculation(result, x, xn, y, 1);
    print(result);
    result.clear();

    cout << "Runge-Kutt:\n";
    RungeKutt(result, x, xn, y, 1);
    print(result);
    result.clear();

    cout << "+-----------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "+-----------------------------------------------------------------------------------------------------------------------------------------------+" << endl << endl;

    cout << endl << endl;
    cout << "+-----------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "+------------------------------------------------------------------- Task 2 --------------------------------------------------------------------+" << endl;
    cout << "+-----------------------------------------------------------------------------------------------------------------------------------------------+" << endl << endl;

    x = 0; //Изменяем условия для второй задачи
    xn = 1;
    y = 0;

    cout << "Euler Recalculation:\n";
    EulerRecalculation(result, x, xn, y, 2);
    result[0].pop_back();
    result[1].pop_back();
    print(result);
    result.clear();

    cout << "Adams:\n";
    Adams(result, x, xn, y, 2);
    print(result);
    result.clear();

    cout << "+-----------------------------------------------------------------------------------------------------------------------------------------------+" << endl;
    cout << "+-----------------------------------------------------------------------------------------------------------------------------------------------+" << endl << endl;

    return 0;
}