#include "pch.h"
#include <iostream>

using namespace std;

int determinat(double **, double **, int, double &);

int main()
{
	int n, i, j, res, j_2;
	double **matrix, **invmatrix, det, k;

	setlocale(LC_ALL, "Russian");
	cout << "Введите количество строк (столбцов) квадратной матрицы: ";
	cin >> n;
	matrix = new double *[n];
	invmatrix = new double *[n];
	for (i = 0; i < n; i++) {
		matrix[i] = new double[n];
		invmatrix[i] = new double[n];
	}
	cout << endl << "Введите элементы матрицы:" << endl;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			cin >> matrix[i][j];
			if (j == i) {
				invmatrix[j][j] = 1;
			}
			else {
				invmatrix[i][j] = 0;
			}
		}
	}
	cout << endl << "Исходная матрица: " << endl;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			cout << matrix[i][j] << "\t \t";
		}
		cout << endl;
	}
	res = determinat(matrix, invmatrix, n, det);
	if (res == 0) {
		cout << endl << "Определитель: " << det << endl << endl;
		for (j = 0; j < n; j++) {
			k = matrix[j][j];
			for (j_2 = 0; j_2 < n; j_2++) {
				if (j_2 >= j) {
					matrix[j][j_2] = matrix[j][j_2] / k;
				}
				invmatrix[j][j_2] = invmatrix[j][j_2] / k;
			}
		}
		for (j = n - 1; j > 0; j--) {
			for (i = j - 1; i >= 0; i--) {
				for (j_2 = 0; j_2 < n; j_2++) {
					invmatrix[i][j_2] = invmatrix[i][j_2] - matrix[i][j] * invmatrix[j][j_2];
				}
			}
		}
		cout << "Обратная матрица: " << endl;
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				cout << invmatrix[i][j] << "\t \t";
			}
			cout << endl;
		}
	}
	cout << endl;
	for (i = 0; i < n; i++) {
		delete[] matrix[i];
		delete[] invmatrix[i];
	}
	delete[]matrix;
	delete[]invmatrix;
	system("pause");
}

int determinat(double **matrix, double **invmatrix, int n, double &det) {
	int i, j, i_0, j_2;
	double k, buf;
	det = 1;
	for (j = 0; j < n; j++) {
		for (i = j; (i < n) && (fabs(matrix[i][j]) < 1.0e-15); i++) {}
		i_0 = i;
		if (i_0 == n) {
			cout << endl << "Определитель равен: 0" << endl;
			return -1;
		}
		else {
			for (j_2 = 0; j_2 < n; j_2++) {
				buf = matrix[i_0][j_2];
				matrix[i_0][j_2] = (-1)*matrix[j][j_2];
				matrix[j][j_2] = buf;
				buf = invmatrix[i_0][j_2];
				invmatrix[i_0][j_2] = (-1)*invmatrix[j][j_2];
				invmatrix[j][j_2] = buf;
			}
			det = det * matrix[j][j];
			for (i = j + 1; i < n; i++) {
				if (fabs(matrix[i][j]) >= 1.0e-15) {
					k = -matrix[i][j] / matrix[j][j];
					for (j_2 = 0; j_2 < n; j_2++) {
						matrix[i][j_2] = matrix[i][j_2] + k * matrix[j][j_2];
						invmatrix[i][j_2] = invmatrix[i][j_2] + k * invmatrix[j][j_2];
					}
				}
			}
		}
	}
	return 0;
}