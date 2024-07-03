#include <iostream>
#include <vector>
#include <iomanip>

using std::cout;
using std::endl;
using std::vector;
using std::setw;
using std::setprecision;

int factorial(int a)
{
    if (a == 0)
    {
        return 1;
    }

    else
    {
        return a * factorial(a - 1);
    }
}

void Newton()
{
    vector<vector<double>> coord = { {2.121, 5.04732}, {2.226, 5.10576}, {2.331, 5.16488}, {2.436, 5.22468}, {2.541, 5.2852}, {2.646, 5.3464}, {2.751, 5.40828}, {2.856, 5.47092}, {2.961, 5.53428}, {3.066, 5.59836}, {3.171, 5.66316}, {3.276, 5.72408}, {3.381, 5.8316} };
    vector<double> xi = { 3.5, 3.0, 2.5, 2.0, 2.331 };
    vector<vector<double>> differences;
    vector<double> tmp;
    vector<double> result;

    for (unsigned int i = 0; i < coord.size() - 1; i++)
    {
        tmp.push_back(coord[i + 1][1] - coord[i][1]); //Вычисление конечных разностей
    }

    differences.push_back(tmp);
    tmp.clear();

    for (unsigned int i = 0; i < coord.size() - 2; i++)
    {
        for (unsigned int j = 0; j < differences[i].size() - 1; j++)
        {
            tmp.push_back(differences[i][j + 1] - differences[i][j]); //Вычисление конечных разностей нового порядка
        }
        differences.push_back(tmp);
        tmp.clear();
    }

    cout << "---------------------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+" << endl;
    for (unsigned int i = 0; i < differences.size(); i++) //Вывод конечных разностей в лестничном виде
    {
        if (i < 9)
        {
            cout << "Finite difference  " << (i + 1) << " order |";
        }
        else
        {
            cout << "Finite difference " << (i + 1) << " order |";
        }

        for (unsigned int j = 0; j < differences[i].size(); j++)
        {
            cout << " " << setw(11) << setprecision(5) << differences[i][j] << " |";
        }
        cout << endl;
    }
    cout << "---------------------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+-------------+" << endl;

    double h = coord[1][0] - coord[0][0];//Вычисление шага
    double temp;
    double mid = (coord[0][0] + coord[coord.size() - 1][0]) / 2;//Вычисление середины отрезка

    for (unsigned int k = 0; k < xi.size(); k++) //Находим значения функции
    {
        if (xi[k] < mid)//Если лежит в первой половине
        {
            temp = (xi[k] - coord[0][0]) / h;

            double res{ 0.0 }; //Интерполируем вперед
            res += coord[0][1] + temp * differences[0][0];

            for (unsigned int i = 1; i < differences.size(); i++) //Вычисление членов
            {
                double t{ 1.0 };

                for (unsigned int j = 1; j <= i; j++)
                {
                    t *= (temp - j); //Промежуточные вычисления знаменателя
                }

                res += t * temp * differences[i][0] / factorial((i + 1));
            }
            result.push_back(res);
        }
        else
        {
            temp = (xi[k] - coord[coord.size() - 1][0]) / h;

            double res{ 0.0 }; //Интерполируем назад
            res += coord[coord.size() - 1][1] + temp * differences[0][(differences[0].size() - 1)];

            for (unsigned int i = 1; i < differences.size(); i++)
            {
                double t = 1.0;

                for (unsigned int j = 1; j <= i; j++)
                {
                    t *= (temp + j);
                }
                res += temp * t * differences[i][(differences[i].size() - 1)] / factorial((i + 1));
            }
            result.push_back(res); 
        }
    }

    cout << endl;
    cout << "y1 = " << result[0] << endl << "y2 = " << result[1] << endl << "y3 = " << result[2] << endl << "y4 = " << result[3] << endl << "y5 = " << result[4] << endl;
}

void LagrangianEqually()
{
    vector<vector<double>> coord = { {2.121, 5.04732}, {2.226, 5.10576}, {2.331, 5.16488}, {2.436, 5.22468}, {2.541, 5.2852}, {2.646, 5.3464}, {2.751, 5.40828}, {2.856, 5.47092}, {2.961, 5.53428}, {3.066, 5.59836}, {3.171, 5.66316}, {3.276, 5.72408}, {3.381, 5.8316} };
    vector<double> xi = { 3.5, 3.0, 2.5, 2.0, 2.331 };
    vector<double> result;

    double step = coord[1][0] - coord[0][0];

    for (unsigned int k = 0; k < xi.size(); k++)
    {
        double res{ 0.0 };

        for (unsigned int i = 0; i < coord.size(); i++)
        {
            double tmp{ 1.0 };

            for (unsigned int j = 0; j < coord.size(); j++)
            {
                if (i != j)
                {
                    tmp *= (xi[k] - coord[0][0] - j * step) / (step * (i - j)); //Вычисление членов произведения
                }
            }
            res += tmp * coord[i][1];
        }
        result.push_back(res);
    }

    cout << endl << "Set values:" << endl;
    cout << "+-------+-------+" << endl;
    cout << "|   x   |   y   |" << endl;
    cout << "+-------+-------+" << endl;
    for (unsigned int i = 0; i < coord.size(); i++)
    {
        cout << "|" << setw(7) << setprecision(5) << coord[i][0] << "|" << setw(7) << setprecision(5) << coord[i][1] << "|\n";
    }
    cout << "+-------+-------+" << endl << endl;


    cout << "Answer:" << endl;
    cout << "+---+------+-----------+" << endl;
    cout << "| i |  xi  |     yi    |" << endl;
    cout << "+---+------+-----------+" << endl;
    for (unsigned int i = 0; i < xi.size(); i++)
    {
        cout << "| " << i + 1 << " |" << setw(6) << xi[i] << "|" << setw(11) << result[i] << "|" << endl;
        cout << "+---+------+-----------+" << endl;
    }
    cout << endl;
}

void LagrangianUnequally()
{
    vector<vector<double>> coord = { {0.02, 1.02316}, {0.08, 1.09590}, {0.12, 1.14725}, {0.17, 1.21483}, {0.23, 1.30120}, {0.30, 1.40976} };
    vector<double> xi = { 0.203, 0.111 };
    vector<double> result;

    for (unsigned int k = 0; k < xi.size(); k++)
    {
        double res{ 0.0 };

        for (unsigned int i = 0; i < coord.size(); i++)
        {
            double tmp {1.0};

            for (unsigned int j = 0; j < coord.size(); j++)
            {
                if (i != j)
                {
                    tmp *= (xi[k] - coord[j][0]) / (coord[i][0] - coord[j][0]);
                }
            }
            res += tmp * coord[i][1];
        }
        result.push_back(res);
    }

    cout << endl << "Set values:" << endl;
    cout << "+-------+-------+" << endl;
    cout << "|   x   |   y   |" << endl;
    cout << "+-------+-------+" << endl;
    for (unsigned int i = 0; i < coord.size(); i++)
    {
        cout << "|" << setw(7) << setprecision(5) << coord[i][0] << "|" << setw(7) << setprecision(5) << coord[i][1] << "|\n";
    }
    cout << "+-------+-------+" << endl << endl;


    cout << "Answer:" << endl;
    cout << "+---+------+-----------+" << endl;
    cout << "| i |  xi  |     yi    |" << endl;
    cout << "+---+------+-----------+" << endl;
    for (unsigned int i = 0; i < xi.size(); i++)
    {
        cout << "| " << i + 1 << " |" << setw(6) << xi[i] << "|" << setw(11) << result[i] << "|" << endl;
        cout << "+---+------+-----------+" << endl;
    }
    cout << endl;
}

int main()
{
    cout << "####################################################################################################################################################################################################" << endl;
    cout << "##############################################################################################\x1B[0;32m Task 1 \x1B[0m##############################################################################################" << endl;
    cout << "####################################################################################################################################################################################################" << endl << endl;

    Newton();
    LagrangianEqually();

    cout << "####################################################################################################################################################################################################" << endl;
    cout << "####################################################################################################################################################################################################" << endl << endl << endl << endl << endl << endl;

    cout << endl << endl << "####################################################################################################################################################################################################" << endl;
    cout << "##############################################################################################\x1B[0;32m Task 2 \x1B[0m##############################################################################################" << endl;
    cout << "####################################################################################################################################################################################################" << endl << endl;

    LagrangianUnequally();

    cout << "####################################################################################################################################################################################################" << endl;
    cout << "####################################################################################################################################################################################################" << endl;

    return 0;
}