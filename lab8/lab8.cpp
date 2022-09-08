#include "pch.h"
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double func1(double);
double func2(double);
double func3(double);
double func4(double);
double integration(double(*)(double), int);
void prnt(double(*)(double), double(*)(double(*)(double), int));

int main() {
	setlocale(LC_ALL, "Russian");
	cout << "Точность:" << setw(36) << "|" << setw(20) << "0.1 |" << setw(20) << "0.01 |" << setw(20) << "0.001 |" << setw(20) << "0.0001 |" << setw(20) << "0.00001 |" << endl << endl;
	cout << "Имя функции:" << setw(33) << "|" << setw(20) << "f=x |" << endl;
	cout << "Значение интеграла по формуле:" << setw(15) << "|" << setw(20) << "4 |" << endl;
	prnt(func1, integration);
	cout << "Имя функции:" << setw(33) << "|" << setw(20) << "f=sin(22x) |" << endl;
	cout << "Значение интеграла по формуле:" << setw(15) << "|" << setw(20) << "-1.424411037669e-5 |" << endl;
	prnt(func2, integration);
	cout << "Имя функции:" << setw(33) << "|" << setw(20) << "f=x^4 |" << endl;
	cout << "Значение интеграла по формуле:" << setw(15) << "|" << setw(20) << "48.8 |" << endl;
	prnt(func3, integration);
	cout << "Имя функции:" << setw(33) << "|" << setw(20) << "f=arctg(x) |" << endl;
	cout << "Значение интеграла по формуле:" << setw(15) << "|" << setw(20) << "2.15702019758026 |" << endl;
	prnt(func4, integration);
	system("pause");
	return 0;
}

double func1(double x) {
	return x;
}

double func2(double x) {
	return sin(22 * x);
}

double func3(double x) {
	return x * x * x * x;
}

double func4(double x) {
	return atan(x);
}

double integration(double(*func)(double), int aim) {
	double area = 0,
		a = 4.0 / aim,
		bg = -1 + a / 2;
	for (int i = 1; i <= aim; i++) {
		area = area + func(bg)*a;
		bg = bg + a;
	}
	return area;
}

void prnt(double(*func)(double), double(*integration)(double(*)(double), int)) {
	int i,
		stp,
		k = 0;
	double tmp,
		area,
		mas[5][3];
	for (double aim = 0.1; aim >= 1e-5; aim = aim / 10) {
		i = 1;
		stp = 1;
		area = integration(func, i);
		do {
			i++;
			stp = stp + i;
			tmp = area;
			area = integration(func, i);
		} while (abs(area - tmp) > aim);
		mas[k][0] = area;
		mas[k][1] = i;
		mas[k][2] = stp;
		k++;
	}
	cout << "Значение интеграла методом прямоугольников:" << setw(2) << "|" << setw(18) << mas[0][0] << " |" << setw(18) << mas[1][0] << " |" << setw(18) << mas[2][0] << " |" << setw(18) << mas[3][0] << " |" << setw(18) << mas[4][0] << " |" << endl;
	cout << "Степень разделения на прямоугольники:" << setw(8) << "|" << setw(18) << mas[0][1] << " |" << setw(18) << mas[1][1] << " |" << setw(18) << mas[2][1] << " |" << setw(18) << mas[3][1] << " |" << setw(18) << mas[4][1] << " |" << endl;
	cout << "Количество подсчетов:" << setw(24) << "|" << setw(18) << mas[0][2] << " |" << setw(18) << mas[1][2] << " |" << setw(18) << mas[2][2] << " |" << setw(18) << mas[3][2] << " |" << setw(18) << mas[4][2] << " |" << endl << endl;
}