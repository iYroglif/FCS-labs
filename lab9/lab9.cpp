#include "pch.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	int i, j, k, l, sz;
	unsigned long int f = 1, fn;
	setlocale(LC_ALL, "Russian");
	cout << "Введите количество строк и столбцов: ";
	cin >> i >> j;
	long double **matrix = new long double*[i];
	for (k = 0; k < i; k++) {
		matrix[k] = new long double[j];
	}
	for (k = 0; k < j; k++) {
		f = f * (k + 1);
		fn = f;
		for (l = 0; l < i; l++) {
			matrix[l][k] = 1.0 / fn;
			fn = fn * f;
		}
	}
	sz = int(80 / j);
	for (k = 0; k < i; k++) {
		for (l = 0; l < j; l++) {
			cout << setw(sz - 1) << left << setprecision(sz - 7) << matrix[k][l] << "|";
		}
		cout << endl;
	}
	system("pause");
}