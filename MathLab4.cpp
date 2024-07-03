#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using std::cout;
using std::tan;
using std::vector;
using std::endl;
using std::setw;
using std::swap;

double a{ 0.5 }, b{ 1.2 };
int n1{ 8 }, n2{ 20 };
double h1{ (b-a)/n1 }, h2{ (b-a)/n2 };

vector<double> h1_xi = {};
vector<double> h1_yi = {};
vector<double> h1_xi_1_2 = {};
vector<double> h1_yi_1_2 = {};

vector<double> h2_xi = {};
vector<double> h2_yi = {};
vector<double> h2_xi_1_2 = {};
vector<double> h2_yi_1_2 = {};

double function(double x)
{
	return tan(x*x)/(x+1);
}

void counting()
{
	double tmp1{ a };
	double tmp2{ a };
	unsigned int i1{ 0 };
	unsigned int i2{ 0 };

	cout << "+-----+----------+----------+----------+----------+" << endl;
	cout << "|  i  |    xi    |    yi    |  xi-1/2  |  yi-1/2  |" << endl;
	cout << "+-----+----------+----------+----------+----------+" << endl;
	do
	{
		h1_xi.push_back(tmp1);
		h1_yi.push_back(function(tmp1));
		tmp1 += h1;
		if (i1 == 0)
		{
			h1_xi_1_2.push_back(0.0);
			h1_yi_1_2.push_back(0.0);
		}
		else
		{
			h1_xi_1_2.push_back((h1_xi[i1 - 1] + h1_xi[i1]) / 2);
			h1_yi_1_2.push_back(function(h1_xi_1_2[i1]));
		}
		cout << "| " << setw(3) << i1 << " | " << setw(8) << h1_xi[i1] << " | " << setw(8) << h1_yi[i1] << " | " << setw(8) << h1_xi_1_2[i1] << " | " << setw(8) << h1_yi_1_2[i1] << " | " << endl;
		i1++;
	} while (tmp1 <= b);
	cout << "+-----+----------+----------+----------+----------+" << endl << endl;

	cout << "+-----+----------+----------+----------+----------+" << endl;
	cout << "|  i  |    xi    |    yi    |  xi-1/2  |  yi-1/2  |" << endl;
	cout << "+-----+----------+----------+----------+----------+" << endl;
	do
	{
		h2_xi.push_back(tmp2);
		h2_yi.push_back(function(tmp2));
		tmp2 += h2;
		if (i2 == 0)
		{
			h2_xi_1_2.push_back(0.0);
			h2_yi_1_2.push_back(0.0);
		}
		else
		{
			h2_xi_1_2.push_back((h2_xi[i2 - 1] + h2_xi[i2]) / 2);
			h2_yi_1_2.push_back(function(h2_xi_1_2[i2]));
		}
		cout << "| " << setw(3) << i2 << " | " << setw(8) << h2_xi[i2] << " | " << setw(8) << h2_yi[i2] << " | " << setw(8) << h2_xi_1_2[i2] << " | " << setw(8) << h2_yi_1_2[i2] << " | " << endl;
		i2++;
	} while (tmp2 <= b);
	cout << "+-----+----------+----------+----------+----------+" << endl << endl;
}



double Rectangles1()
{
	double I{ 0.0 };

	for (unsigned int q = 0; q < h1_yi_1_2.size(); q++)
	{
		I += h1_yi_1_2[q];
	}

	return I*h1;
}

double Rectangles2()
{
	double I{ 0.0 };

	for (unsigned int q = 0; q < h2_yi_1_2.size(); q++)
	{
		I += h2_yi_1_2[q];
	}

	return I * h2;
}

double Trapezoids1()
{
	double I{ 0.0 };

	for (unsigned int q = 1; q < h1_yi.size() - 1; q++)
	{
		I += h1_yi[q];
	}

	return (I + (h1_yi[0] + h1_yi[h1_yi.size() - 1]) / 2) * h1;
}

double Trapezoids2()
{
	double I{ 0.0 };

	for (unsigned int q = 1; q < h2_yi.size() - 1; q++)
	{
		I += h2_yi[q];
	}

	return (I + (h2_yi[0] + h2_yi[h2_yi.size() - 1]) / 2) * h2;
}

double Simpson1()
{
	double I{ 0.0 };

	for (unsigned int q = 1; q < h1_yi.size() - 1; q++)
	{
		if (q % 2 != 0)
		{
			I += 4 * h1_yi[q];
		}

		else
		{
			I += 2 * h1_yi[q];
		}
	}

	return (I + h1_yi[0] + h1_yi[h1_yi.size() - 1]) * (h1 / 3);
}

double Simpson2()
{
	double I{ 0.0 };

	for (unsigned int q = 1; q < h2_yi.size() - 1; q++)
	{
		if (q % 2 != 0)
		{
			I += 4 * h2_yi[q];
		}

		else
		{
			I += 2 * h2_yi[q];
		}
	}

	return (I + h2_yi[0] + h2_yi[h2_yi.size() - 1]) * (h2 / 3);
}

int main()
{
	counting();

	double results[6][3] = {};

	results[0][0] = 8;
	results[1][0] = 8;
	results[2][0] = 8;
	results[3][0] = 20;
	results[4][0] = 20;
	results[5][0] = 20;

	results[0][2] = 0;
	results[1][2] = 1;
	results[2][2] = 2;
	results[3][2] = 0;
	results[4][2] = 1;
	results[5][2] = 2;

	results[0][1] = Rectangles1();
	results[1][1] = Trapezoids1();
	results[2][1] = Simpson1();
	results[3][1] = Rectangles2();
	results[4][1] = Trapezoids2();
	results[5][1] = Simpson2();

	for (int q = 0; q < 5; q++)
	{
		for (int i = 0; i < 5; i++)
		{
			if (results[i][1] > results[i+1][1])
			{
				swap(results[i][0], results[i+1][0]);
				swap(results[i][1], results[i+1][1]);
				swap(results[i][2], results[i+1][2]);
			}
		}
	}
	cout << "+----------+-----+--------------------+" << endl;
	cout << "|  Result  |  n  |       Method       |" << endl;
	cout << "+----------+-----+--------------------+" << endl;

	for (unsigned int q = 0; q < 6; q++)
	{
		cout << "| " << setw(8) << results[q][1] << " | " << setw(3) << results[q][0] << " | ";
		if (results[q][2] == 0)
		{
			cout << "Central rectangles |" << endl;
		}
		if (results[q][2] == 1)
		{
			cout << "     Trapezoid     |" << endl;
		}
		if (results[q][2] == 2)
		{
			cout << "     Simpson's     |" << endl;
		}
		cout << "+----------+-----+--------------------+" << endl;
	}

	return 0;
}