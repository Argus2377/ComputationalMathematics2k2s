#include <iostream>                   
#include <iomanip>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;
using std::setw;

double a{ 1 }, b{ 2 }, eps{ 0.001 };

double function(double x) //Функция
{
	double f = x * x * x + 2 * x - 4;
	return f;
}

double fi(double x) //Сжимающая функция
{
	double f = pow((-2 * x + 4), (1.0 / 3.0));
	return f;
}

bool sign(double x) //Проверка, является ли число положительным
{
	if (x > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

double derivative1(double x) //Первая производная от функции
{
	return (3 * x * x + 2);
}

double derivative2(double x) //Вторая производная от функции
{
	return (6 * x);
}


double bisection() // Метод биекции
{
	double delta{ 0 };
	int n{ 1 };

	cout << "Biection: "<< endl;
	cout << "+---+--------+--------+-----------+-----------+-----------+" << endl;
	cout << "| n |    a   |    b   |    f(a)   |    f(b)   |  |a - b|  |" << endl;

	do //Цикл нахождения ответа
	{
		cout << "+---+--------+--------+-----------+-----------+-----------+" << endl;
		cout << "|" << setw(3) << n << "|" << setw(8) << a << "|" << setw(8) << b << "|" << setw(11) << function(a) << "|" << setw(11) << function(b) << "|" << setw(11) << delta << "|" << endl; //Вывод таблицы
		delta = abs(a - b); //находим значение |a - b|
		delta /= 2;         //уменьшаем шаг
		if (sign(function(a + delta)) == (sign(function(a)))) //определяем, в какую сторону уменьшать промежуток
		{
			a += delta;
		}
		else
		{
			b -= delta;
		}
		n++;
	} while (delta >= 0.001); //условие выхода из цикла
	cout << "+---+--------+--------+-----------+-----------+-----------+" << endl << endl;

	double result = a + delta; //Подсчёт результата

	return result;
}

double chords() //Метод хорд
{
	double xn{ 0 };
	int n{ 1 };

	cout << "Chords: " << endl;
	cout << "+---+--------+-------------+" << endl;
	cout << "| n |   x(n) |   f(x(n))   |" << endl;
	cout << "+---+--------+-------------+" << endl;

	if (function(a) * derivative2(a) < 0) //Выбор формулы для подсчёта
	{
		xn = a;

		while (abs(function(xn)) >= 0.001) //Подсчёт результатов
		{
			xn = xn - ((function(xn)) / (function(b) - function(xn))) * (b - xn);
			cout << "|" << setw(3) << n << "|" << setw(8) << xn << "|" << setw(13) << function(xn) << "|" << endl; //Вывод таблицы
			cout << "+---+--------+-------------+" << endl;
			n++;
		}
	}
	else
	{
		xn = b;

		while (abs(function(xn)) >= 0.001) //Подсчёт результатов
		{
			xn = xn - ((function(xn)) / (function(xn) - function(a))) * (xn - a);
			cout << "|" << setw(3) << n << "|" << setw(8) << xn << "|" << setw(13) << function(xn) << "|" << endl; //Вывод таблицы
			cout << "+---+--------+-------------+" << endl;
			n++;
		}
	}
	cout << endl;

	return xn;
}

double newton() //Метод Ньютона
{
	double xn{ 0 };
	int n{ 1 };

	cout << "Newton: " << endl;
	cout << "+---+--------+-----------------+" << endl;
	cout << "| n |   x(n) | x(n) - x(n - 1) |" << endl;
	cout << "+---+--------+-----------------+" << endl;

	if (function(a) * derivative1(a) < 0) //Выбор xn
	{
		xn = a;
	}
	else
	{
		xn = b;
	}

	while (abs(function(xn)) >= 0.001) //подсчёт результатов
	{
		cout << "|" << setw(3) << n << "|" << setw(8) << xn << "|"; //Вывод таблицы
		xn = xn - (function(xn) / derivative1(xn));
		cout << setw(17) << xn << "|" << endl; //Вывод таблицы
		cout << "+---+--------+-----------------+" << endl;
		n++;
	}
	cout << endl;

	return xn;
}

double SimpleIterations() //Метод простых итераций
{
	double x{ a }, x0{ 0 };
	int n{ 1 };

	cout << "Simple Iterations: " << endl;
	cout << "+---+-------------+-----------+" << endl;
	cout << "| n | x0 = fi(x0) | x = fi(x) |" << endl;

	do //подсчёт результатов
	{
		cout << "+---+-------------+-----------+" << endl;
		x0 = x;
		x = fi(x0);
		cout << "|" << setw(3) << n << "|" << setw(13) << x0 << "|" << setw(11) << x << "|" << endl; //Вывод таблицы
		n++;
	} while (abs(x0 - x) > eps); //условие выхода из цикла
	cout << "+---+-------------+-----------+" << endl << endl;

	return x;
}

int main()
{
	cout << "+--------------------------------+" << endl;
	cout << "| The equation: x^3 + 2x - 4 = 0 |" << endl;
	cout << "| Interval: [1:2]                |" << endl;
	cout << "| eps: 0.001                     |" << endl;
	cout << "+--------------------------------+" << endl << endl; //Вывод условий задачи

	double results[4]{ 0 };

	results[0] = bisection(); //Подсчёт методом биекций
	results[1] = chords(); //Подсчёт методом хорд
	results[2] = newton(); //Подсчёт методом касательных
	results[3] = SimpleIterations(); //Подсчёт методом простых итераций

	cout << "Biection: " << setw(18) << results[0] << endl;
	cout << "Chords: " << setw(20) << results[1] << endl;
	cout << "Newton: " << setw(20) << results[2] << endl;
	cout << "Simple Iterations: " << setw(9) << results[3] << endl; //Вывод результатов

	return 0;
}