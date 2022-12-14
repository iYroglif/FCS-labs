#include "pch.h"
#include <iostream>

using namespace std;

int main() {
	int tekst[40][80], //двумерный массив, в котором будут храниться коды символов слов текста
		wlen[40], //массив, в котором будет храниться информации о длине слов текста
		i, //
		j, //
		k, //для циклов и индексы элементов в массивах
		st1, //
		st2, //для остановки циклов при выполнении условия
		frst = 0; //для проверки печати первого слова
	for (i = 0; i < 40; i++) {
		for (j = 0; j < 80 - i; j++) {
			tekst[i][j] = 0;
		}
	}
	for (i = 0; i < 40; i++) {
		wlen[i] = 0;
	}
	i = -1;
	j = 0;
	do {
		i++;
		j = 0;
		do {
			tekst[i][j] = int(cin.get());
		} while (!((tekst[i][j] > 64) && (tekst[i][j] < 91)) && !((tekst[i][j] > 96) && (tekst[i][j] < 123)) && (tekst[i][j] != 46));

		while ((tekst[i][j] != 32) && (tekst[i][j] != 46)) {
			if (((tekst[i][j] > 64) && (tekst[i][j] < 91)) || ((tekst[i][j] > 96) && (tekst[i][j] < 123))) {
				if (tekst[i][j] < 91) {
					tekst[i][j] = tekst[i][j] + 32;
				}
				j++;
				tekst[i][j] = int(cin.get());
			}
			else {
				tekst[i][j] = int(cin.get());
			}
		}
		wlen[i] = j;
	} while (tekst[i][j] != 46);
	if (wlen[i] == 0) {
		i--;
	}
	for (j = 0; j < i; j++) {
		if (wlen[j] != wlen[i]) {
			st2 = 0;
			k = wlen[j] - 1;
			do {
				if (tekst[j][k] != 122 - (wlen[j] - 1 - k)) {
					st2++;
				}
				k--;
			} while ((st2 == 0) && (k >= 0));
			if (st2 == 0) {
				if (frst != 0) {
					cout << " ";
				}
				for (k = 0; k < wlen[j]; k++) {
					cout << char(tekst[j][k]);
				}
				frst = 1;
			}
		}
		else {
			k = wlen[j] - 1;
			st1 = 0;
			st2 = 0;
			do {
				if (tekst[j][k] != tekst[i][k]) {
					st1++;
				}
				if (tekst[j][k] != 122 - (wlen[j] - 1 - k)) {
					st2++;
				}
				k--;
			} while ((st1 == 0) && (st2 == 0) && (k >= 0));

			if ((st1 != 0) && (st2 == 0)) {
				if (frst != 0) {
					cout << " ";
				}
				for (k = 0; k < wlen[j]; k++) {
					cout << char(tekst[j][k]);
				}
				frst = 1;
			}
		}
	}
	//	cout << "." << endl;
	cout << endl;
	system("pause");
	return 0;
}