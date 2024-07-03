#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::swap;
using std::setw;

double eps{ 0.001 };

double A1{ 0.30 }, A2{ 1.20 }, A3{ 0.20 }, A{ 0.60 };
double B1{ -0.10 }, B2{ -0.20 }, B3{ 1.60 }, B{ 0.30 };
double C1{ -1.50 }, C2{ -0.30 }, C3{ 0.10 }, C{ 0.40 };

double maximum(double a, double b, double c) //Функция определения максимального из трёх чисел
{
    double max{ a };

    if (b > a)
    {
        max = a;
    }

    if (c > a)
    {
        max = c;
    }

    return max;
}

void print(double matrix[3][4]) //Функция вывода матрицы
{
    cout << endl;
    for (int q = 0; q < 3; q++)
    {
        for (int i = 0; i < 4; i++)
        {
            cout << setw(10) << matrix[q][i];
            cout << " | ";
        }
        cout << endl;
    }
}

void gauss() //Метод Гаусса
{
    cout << endl << "\x1B[0;32m" << "----------------------------------------- THE GAUSS METHOD -----------------------------------------" << "\x1B[0m";

    double matrix[3][4] = { {A1, A2, A3, A}, {B1, B2, B3, B}, {C1, C2, C3, C} }; //Заполнение матрицы
    double x1{ 0 }, x2{ 0 }, x3{ 0 };

    print(matrix);

	for (int q = 0; q < 2; q++) //Алгоритм сортировки пузырьком
    {
		for (int i = 0; i <2; i++)
		{
			if (abs(matrix[i + 1][0]) > abs(matrix[i][0]))//Сортируем, чтобы избежать нулевых диагональных элементов
			{
                swap(matrix[i][0], matrix[i + 1][0]);
                swap(matrix[i][1], matrix[i + 1][1]);
                swap(matrix[i][2], matrix[i + 1][2]);
                swap(matrix[i][3], matrix[i + 1][3]);
			}
		}
	}

    print(matrix);

    for (int q = 0; q < 3; q++) //Начинаем преобразовывать матрицу
    {
        for (int i = 3; i >= 0; i--)
        {
            if (q==0)
            {
                matrix[q][i] /= matrix[0][0];
            }

            if (q==1)
            {
                matrix[q][i] /= matrix[1][0];
            }

            if (q==2)
            {
                matrix[q][i] /= matrix[2][0];
            }
        }
    }

    print(matrix);


    for (int q = 1; q < 3; q++)
    {
        for (int i = 0; i < 4; i++)
        {
            matrix[q][i] -= matrix[0][i];
        }
    }

    print(matrix);

    for (int q = 0; q < 3; q++)
    {
        for (int i = 3; i >= 0; i--)
        {

            if (q == 1)
            {
                matrix[q][i] /= matrix[1][1];
            }

            if (q == 2)
            {
                matrix[q][i] /= matrix[2][1];
            }
        }
    }

    print(matrix);

    for (int q = 0; q < 4; q++)
    {
        matrix[2][q] -= matrix[1][q];
    }

    print(matrix);

    matrix[2][3] /= matrix[2][2];
    matrix[2][2] /= matrix[2][2];

    print(matrix);

    x3 = matrix[2][3]; //Вычисляем корни
    x2 = matrix[1][3] - matrix[1][2] * x3;
    x1 = matrix[0][3] - matrix[0][2] * x3 - matrix[0][1] * x2;


    cout << endl;
    cout << "x1 = " << setw(9) << x1 << endl;
    cout << "x2 = " << setw(9) << x2 << endl;
    cout << "x3 = " << setw(9) << x3 << endl;

    cout << "\x1B[0;32m" << "----------------------------------------------------------------------------------------------------" << "\x1B[0m" << endl << endl;
}

void iteration() //Метод итераций
{
    cout << endl << "\x1B[0;34m" << "----------------------------------------- ITERATIVE METHOD -----------------------------------------" << "\x1B[0m";

    double matrix[3][4] = { {A1, A2, A3, A}, {B1, B2, B3, B}, {C1, C2, C3, C} }; //Заполняем матрицу
    
    print(matrix);

    for (int q = 0; q < 2; q++)
    {
        for (int i = 0; i < 2; i++)
        {
            if (abs(matrix[i + 1][0]) > abs(matrix[i][0]))//Приводим матрицу к диагонально-преобладающему виду
            {
                swap(matrix[i][0], matrix[i + 1][0]);
                swap(matrix[i][1], matrix[i + 1][1]);
                swap(matrix[i][2], matrix[i + 1][2]);
                swap(matrix[i][3], matrix[i + 1][3]);
            }
        }
    }

    print(matrix);

    double x1_0{ 0 }, x2_0{ 0 }, x3_0{ 0 };
    double x1{ 0 }, x2{ 0 }, x3{ 0 };
    int n{ 0 };

    cout << endl;
    cout << "+---+----------+----------+----------+-------------+-------------+-------------+--------------+" << endl;
    cout << "| n |    x1    |    x2    |    x3    | |x1_0 - x1| | |x2_0 - x2| | |x3_0 - x3| | max|xj_0-xj| |" << endl;

    do //Вычисление корней
    {
        n++;
        x1_0 = x1;
        x2_0 = x2;
        x3_0 = x3;
        x1 = (matrix[0][3] - (matrix[0][1] * x2_0 + matrix[0][2] * x3_0)) / matrix[0][0];
        x2 = (matrix[1][3] - (matrix[1][0] * x1_0 + matrix[1][2] * x3_0)) / matrix[1][1];
        x3 = (matrix[2][3] - (matrix[2][1] * x2_0 + matrix[2][0] * x1_0)) / matrix[2][2];
        cout << "+---+----------+----------+----------+-------------+-------------+-------------+--------------+" << endl;
        cout << "|" << setw(3) << n << "|" << setw(10) << x1 << "|" << setw(10) << x2 << "|" << setw(10) << x3 << "|" << setw(13) << abs(x1_0 - x1) << "|" << setw(13) << abs(x2_0 - x2) << "|" << setw(13) << abs(x3_0 - x3) << "|" << setw(14) << maximum(abs(x1_0 - x1), abs(x2_0 - x2), abs(x3_0 - x3)) << "|" << endl; //Вывод таблицы
    } while (maximum(abs(x1_0 - x1), abs(x2_0 - x2), abs(x3_0 - x3)) >= eps);
    cout << "+---+----------+----------+----------+-------------+-------------+-------------+--------------+" << endl;

    cout << endl;
    cout << "x1 = " << setw(9) << x1 << endl;
    cout << "x2 = " << setw(9) << x2 << endl;
    cout << "x3 = " << setw(9) << x3 << endl;

    cout << "\x1B[0;34m" << "----------------------------------------------------------------------------------------------------" << "\x1B[0m" << endl << endl;
}

void GaussSeidel()//Метод Гаусса-Зейделя
{
    cout << endl << "\x1B[0;31m" << "------------------------------------- THE GAUSS-SEIDEL METHOD --------------------------------------" << "\x1B[0m";

    double matrix[3][4] = { {A1, A2, A3, A}, {B1, B2, B3, B}, {C1, C2, C3, C} }; //Заполнение матрицы

    print(matrix);

    for (int q = 0; q < 2; q++)
    {
        for (int i = 0; i < 2; i++)
        {
            if (abs(matrix[i + 1][0]) > abs(matrix[i][0]))//Приводим матрицу к диагонально-преобладающему виду
            {
                swap(matrix[i][0], matrix[i + 1][0]);
                swap(matrix[i][1], matrix[i + 1][1]);
                swap(matrix[i][2], matrix[i + 1][2]);
                swap(matrix[i][3], matrix[i + 1][3]);
            }
        }
    }

    print(matrix);

    double x1_0{ 0 }, x2_0{ 0 }, x3_0{ 0 };
    double x1{ 0 }, x2{ 0 }, x3{ 0 };
    int n = 0;

    cout << endl;
    cout << "+---+----------+----------+----------+-------------+-------------+-------------+--------------+" << endl;
    cout << "| n |    x1    |    x2    |    x3    | |x1_0 - x1| | |x2_0 - x2| | |x3_0 - x3| | max|xj_0-xj| |" << endl;

    do
    {
        n++;
        x1_0 = x1;
        x2_0 = x2;
        x3_0 = x3;
        x1 = (matrix[0][3] - (matrix[0][1] * x2_0 + matrix[0][2] * x3_0)) / matrix[0][0]; //Отличие метода Гаусса-Зейделя от метода итераций(метода Якоби) заключается
        x2 = (matrix[1][3] - (matrix[1][0] * x1 + matrix[1][2] * x3_0)) / matrix[1][1];   //в том, что по мере вычисления корней мы начинаем использовать только что
        x3 = (matrix[2][3] - (matrix[2][1] * x2 + matrix[2][0] * x1)) / matrix[2][2];     //полученные значения, вместо значений, полученных на прошлой итерации
        cout << "+---+----------+----------+----------+-------------+-------------+-------------+--------------+" << endl;
        cout << "|" << setw(3) << n << "|" << setw(10) << x1 << "|" << setw(10) << x2 << "|" << setw(10) << x3 << "|" << setw(13) << abs(x1_0 - x1) << "|" << setw(13) << abs(x2_0 - x2) << "|" << setw(13) << abs(x3_0 - x3) << "|" << setw(14) << maximum(abs(x1_0 - x1), abs(x2_0 - x2), abs(x3_0 - x3)) << "|" << endl; //Вывод таблицы
    } while (maximum(abs(x1_0 - x1), abs(x2_0 - x2), abs(x3_0 - x3)) >= eps);
    cout << "+---+----------+----------+----------+-------------+-------------+-------------+--------------+" << endl;

    cout << endl;
    cout << "x1 = " << setw(9) << x1 << endl;
    cout << "x2 = " << setw(9) << x2 << endl;
    cout << "x3 = " << setw(9) << x3 << endl;

    cout << "\x1B[0;31m" << "----------------------------------------------------------------------------------------------------" << "\x1B[0m" << endl << endl;
}

int main()
{
    cout << "+-----------------------------------+" << endl;
    cout << "| { 0.30x1 + 1.20x2 - 0.20x3 = 0.60 |" << endl;
    cout << "| {-0.10x1 - 0.20x2 + 1.60x3 = 0.30 |" << endl;
    cout << "| {-1.50x1 - 0.30x2 + 0.10x3 = 0.40 |" << endl;
    cout << "+-----------------------------------+" << endl;

    gauss();
    iteration();
    GaussSeidel();

    return 0;
}