#include "pch.h"
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
	int i, //переменная для циклов и индекс элемента массива
		k; //количество строк

	double stp, //шаг
		x, //аргумент (изначально левая граница)
		rg, //правая граница
		xv2, //аргумент в квадрате
		*mas = NULL; //указатель для динамического массива

	setlocale(LC_ALL, "Russian");
	cout << "Введите границы и шаг. Например -10 10 1. " << endl;
	cin >> x >> rg >> stp;
	k = (abs(x) + abs(rg)) / stp + 1;
	mas = new double[k];
	for (i = 0; i < k; i++) {
		xv2 = x * x;
		mas[i] = 4.85 + (0.00001*sin(xv2)) / (1 + abs(x)*sqrt(xv2*(xv2 + 3) + 3));
		x = x + stp;
	}
	setlocale(LC_ALL, ".866");
	cout << endl << char(-38) << setfill(char(-60)) << setw(5) << char(-62) << setw(13) << char(-65) << endl;
	cout << setfill(' ') << char(-77) << setw(3) << "x" << setw(2) << char(-77) << setw(3) << "y" << setw(10) << char(-77) << endl;
	cout << setfill(char(-60)) << char(-61) << setw(5) << char(-59) << setw(13) << char(-76) << endl << setfill(' ');
	x = x - stp * k;
	for (i = 0; i < k; i++) {
		cout << char(-77) << setw(3) << x << setw(2) << char(-77) << setprecision(10) << setw(12) << left << mas[i] << right << char(-77) << endl;
		x = x + stp;
	}
	cout << setfill(char(-60)) << char(-64) << setw(5) << char(-63) << setw(13) << char(-39) << endl;
	system("pause");
	delete[] mas;
	return 0;
}