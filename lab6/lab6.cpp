#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

void bubble(int *, int);
void head(int *, int);
void inver(int *, int);
void set(int *, int *, int);
void prnt(void(*)(int *, int), int *, int *, void(*)(int *, int), void(*)(int *, int *, int));

int main()
{
	setlocale(LC_ALL, "Russian");
	int mas1[40], //для случайных чисел (исходный)
		mas2[40], //для цикла (индекс элемента массива)
		i; //для цикла (индекс элемента массива)
	srand(time(0));
	cout << "Массив случайных чисел: " << endl;
	for (i = 0; i < 40; i++) {
		mas1[i] = rand() % 100;
		mas2[i] = mas1[i];
		cout << mas1[i] << " ";
	}
	cout << endl << setfill(char('-')) << setw(70) << "-" << endl << endl << endl << "Сортировка пузырьком:" << endl << endl;
	prnt(bubble, mas1, mas2, inver, set);
	cout << setfill(char('-')) << setw(70) << "-" << endl << endl << endl << "Сортировка выбором:" << endl << endl;
	prnt(head, mas1, mas2, inver, set);
	system("pause");
	return 0;
}

void bubble(int *arr, int nm) {
	int sr = 0, //счетчик сравнений
		pr = 0; //счетчик перестановок
	for (int i = 0; i < nm - 1; i++) {
		for (int j = 0; j < nm - i - 1; j++) {
			sr++;
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
				pr++;
			}
		}
		if (pr == 0) break;
	}
	cout << "Количество сравнений: " << sr << endl << "Количество перестановок: " << pr << endl << "Отсортированный массив: " << endl;
	for (int i = 0; i < nm; i++) {
		cout << arr[i] << " ";
	}
	cout << endl << endl;
}

void head(int *arr, int nm) {
	int sr = 0, //счетчик сравнений
		pr = 0, //счетчик перестановок
		ij; //индекс элемента массива
	for (int i = 0; i < nm - 1; i++) {
		ij = i;
		for (int j = i + 1; j < nm; j++) {
			sr++;
			if (arr[j] < arr[ij]) {
				ij = j;
			}
		}
		if (ij != i) {
			swap(arr[i], arr[ij]);
			pr++;
		}
	}
	cout << "Количество сравнений: " << sr << endl << "Количество перестановок: " << pr << endl << "Отсортированный массив: " << endl;
	for (int i = 0; i < nm; i++) {
		cout << arr[i] << " ";
	}
	cout << endl << endl;
}

void inver(int *arr, int nm) {
	for (int i = 0; i < nm; i++) {
		arr[i] = -arr[i];
	}
}

void set(int *arr1, int *arr2, int nm) {
	for (int i = 0; i < nm; i++) {
		arr1[i] = arr2[i];
	}
}

void prnt(void(*sort)(int *, int), int *mas1, int *mas2, void(*inver)(int *, int), void(*set)(int *, int *, int)) {
	int nmb = 0; //номер списка вывода
	for (int i = 1, k = 40; i < 4; i++, k = k / 2) {
		cout << ++nmb << ". Сортировка неупорядоченного массива из " << k << " элементов:" << endl;
		sort(mas2, k);
		cout << ++nmb << ". Сортировка упорядоченного массива из " << k << " элементов:" << endl;
		sort(mas2, k);
		inver(mas2, k);
		cout << ++nmb << ". Сортировка упорядоченного массива из " << k << " элементов с инверсией знаков значений элементов:" << endl;
		sort(mas2, k);
		set(mas2, mas1, k);
	}
}