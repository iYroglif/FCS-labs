#include "pch.h"
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double func(double);
double deriv(double);

int main()
{
	setlocale(LC_ALL, "Russian");

	int ex, //переменная для цикла
		stp; //счетчик шагов

	double dot, //точка
		cdot, //копия точки
		aim, //точность
		lf, //левая граница
		rg, //правая граница 
		x, //аргумент
		y; //значение функции

	do {
		cout << "Введите точность нахождения корня. Например: 1e-13" << endl;
		cin >> aim;
		cout << "Введите точку вблизи корня. Например: 0" << endl;
		cin >> dot;
		cout << "Введите границы интервала, содержащий корень. Например: 0 1" << endl;
		cin >> lf >> rg;

		stp = 0;
		cdot = dot;
		y = cdot;
		do {
			cdot = y;
			y = cdot - func(cdot);
			stp++;
		} while (abs(cdot - y) > aim);

		y = cdot - y;
		cout << endl << "Метод простых итераций:" << endl << "Значение функции в точке " << setprecision(int(abs(log10(aim)) + 3)) << cdot << " равно: " << y << " Кол-во шагов: " << stp << endl << endl;
		
		stp = 0;
		do {
			x = (lf + rg) / 2;
			y = func(x);
			if (y > 0) {
				rg = x;
			}
			else {
				lf = x;
			}
			stp++;
		} while (abs(y) > aim);

		cout << "Метод половинного деления:" << endl << "Значение функции в точке " << x << " равно: " << y << " Кол-во шагов: " << stp << endl << endl;
		
		stp = 0;
		cdot = dot;
		x = cdot;
		do {
			cdot = x;
			x = cdot - func(cdot) / deriv(cdot);
			y = func(x);
			stp++;
		} while (abs(y) > aim);

		cout << "Метод Ньютона:" << endl << "Значение функции в точке " << x << " равно: " << y << " Кол-во шагов: " << stp << endl << endl << "Вы хотите продолжить или выйти из программы? 1 - продолжить, 0 - выйти." << endl;
		cin >> ex;
	} while (ex != 0);

	return 0;
}

double func(double x) {
	return x - cos(x);
}

double deriv(double x) {
	return sin(x) + 1;
}