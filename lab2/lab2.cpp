#include "pch.h"
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	double d, //дискриминант
		x1,	  //первый или единственный корень
		x2;	  //второй корень
	int a,	  //коэффициент а
		b,	  //коэффициент b
		c,	  //коэффициент c
		q;	  //вспомогательная переменная для выхода или продолжения программы
	setlocale(LC_ALL, "Russian");
	do
	{
		cout << "Введите коэффициенты квадратного уравнения (Например: 1 4 -3 где a=1, b=4, c=-3)\n";
		cin >> a >> b >> c;
		if (a == 0)
		{
			x1 = -c / b;
			cout << "x = " << x1 << endl;
		}
		else
		{
			if (b == 0)
			{
				x1 = -c / a;
				if (x1 == 0)
				{
					cout << "x = " << x1 << endl;
				}
				else
				{
					if (x1 > 0)
					{
						x1 = sqrt(x1);
						cout << "x1 = " << x1 << endl
							 << "x2 = " << -x1
							 << endl;
					}
					else
					{
						cout << "Корней нет.\n";
					}
				}
			}
			else
			{
				d = b * b - 4 * a * c;
				if (d < 0)
				{
					cout << "Корней нет.\n";
				}
				else
				{
					if (d == 0)
					{
						x1 = -b / (2 * a);
						cout << "x = " << x1 << endl;
					}
					else
					{
						d = sqrt(d);
						x1 = (-b + d) / (2 * a);
						x2 = (-b - d) / (2 * a);
						cout << "x1 = " << x1 << endl
							 << "x2 = " << x2
							 << endl;
					}
				}
			}
		}
		do
		{
			cout << "Вы хотите продолжить или выйти из программы? (1 - продолжить; 0 - выйти)\n";
			cin >> q;
			if (q != 1 && q != 0)
			{
				cout << "Проверьте правильность введённых данных и попробуйте снова.\n ";
			}
		} while (q != 1 && q != 0);
	} while (q != 0);
	return 0;
}