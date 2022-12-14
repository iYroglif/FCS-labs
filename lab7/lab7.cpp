#include "pch.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int * createkey(ifstream &, int &);
int * encoding(ifstream &, int *, int, long int &);
int decryption(int *, int *, int, int);
int stat(int *, int *, int, int);

int main()
{
	setlocale(LC_ALL, "Russian");
	int numwords, //количество слов в ключе
		*keywords = NULL, //массив слов ключа, преобразованных в число
		*arrmess = NULL, //массив закодированных символов
		ex = 1, //переменная для цикла
		fin = 0; //переменная для цикла (в случае сбоя в программе)
	long int numsym;

	do {
		ifstream key("key.txt");
		if (!key.is_open()) {
			cout << "Файл с ключом шифра не может быть открыт! Проверьте нахождение файла в нужном каталоге и нажмите любую клавишу для повтора." << endl;
			system("pause");
		}
		else
		{
			keywords = createkey(key, numwords);
			key.close();
			ifstream mess("message.txt");
			if (!mess.is_open()) {
				cout << "Файл с текстом для шифровки не может быть открыт! Проверьте нахождение файла в нужном каталоге и нажмите любую клавишу для повтора." << endl;
				system("pause");
			}
			else {
				arrmess = encoding(mess, keywords, numwords, numsym);
				mess.close();
				fin = decryption(arrmess, keywords, numsym, numwords);
				do {
					ex = stat(arrmess, keywords, numwords, numsym);
				} while (ex != 0);
				delete[] keywords;
				delete[] arrmess;
			}
		}
	} while (fin != 1);
	return 0;
}

int * createkey(ifstream &key, int &numwords) {
	key.seekg(0, ios::end);
	long int numsymex = key.tellg();
	key.seekg(0, ios::beg);
	int *arrkey = new int[numsymex];
	cout << "Ключ: " << endl << endl;
	long int numsym = 0;
	char sym;
	numwords = 0;
	while (!key.eof()) {
		key.get(sym);
		if ((sym == ' ') || (int(sym) == 10)) {
			numwords++;
		}
		unsigned char symex = sym;
		arrkey[numsym] = int(symex);
		numsym++;
	}
	numwords = numwords + 1;

	int *keywords = new int[numwords];
	int i;
	for (i = 0; i < numwords; i++) {
		keywords[i] = 0;
	}

	ofstream kword("words code.txt", ios_base::out | ios_base::trunc);
	int nmword = 0;
	for (i = 0; i < numsym - 1; i++) {
		cout << unsigned char(arrkey[i]);
		if ((arrkey[i] == 32) || (arrkey[i] == 10)) {
			keywords[nmword] = keywords[nmword] % 256;
			kword << keywords[nmword] << " ";
			nmword++;
		}
		else {
			keywords[nmword] = keywords[nmword] + arrkey[i];
		}
	}
	keywords[nmword] = keywords[nmword] % 256;
	kword << keywords[nmword];
	kword.close();
	cout << endl << endl << "Кодовые слова записаны в файл 'words code.txt'" << endl;
	delete[] arrkey;
	return keywords;
}

int * encoding(ifstream &mess, int *keywords, int numwords, long int &numsym) {
	mess.seekg(0, ios::end);
	long int numsymex = mess.tellg();
	mess.seekg(0, ios::beg);
	int *arrmess = new int[numsymex];
	cout << endl << "Шифруемый текст: " << endl << endl;
	numsym = 0;
	char sym;
	while (!mess.eof()) {
		mess.get(sym);
		unsigned char symex = sym;
		arrmess[numsym] = int(symex);
		numsym++;
	}
	ofstream cryp("cipher.txt", ios_base::out | ios_base::trunc);
	int i;
	for (i = 0; i < numsym - 1; i++) {
		cout << unsigned char(arrmess[i]);
		arrmess[i] = (arrmess[i] + keywords[i%numwords]) % 256;
		cryp << arrmess[i] << " ";
	}
	cryp.close();
	cout << endl << endl << "Зашифрованный текст записан в файл 'cipher.txt'" << endl << endl;
	ofstream symcryp("undeciphered message.txt", ios_base::out | ios_base::trunc);
	for (i = 0; i < numsym - 1; i++) {
		symcryp << unsigned char(arrmess[i]);
	}
	symcryp.close();
	cout << "Нерасшифрованный текст записан в файл 'undeciphered message.txt'" << endl << endl;
	return arrmess;
}

int decryption(int *arrmess, int *keywords, int numsym, int numwords) {
	ofstream decryp("decrypted message.txt", ios_base::out | ios_base::trunc);
	int i;
	for (i = 0; i < numsym - 1; i++) {
		arrmess[i] = arrmess[i] - keywords[i%numwords];
		if (arrmess[i] < 0) {
			arrmess[i] = arrmess[i] + 256;
		}
		decryp << unsigned char(arrmess[i]);
	}
	decryp.close();
	cout << "Расшифрованный текст записан в файл 'decrypted message.txt'" << endl;
	return 1;
}

int stat(int *arrmess, int *keywords, int numwords, int numsym) {
	cout << endl << "Введите символ, статистику которого вы хотите узнать: " << endl;
	unsigned char sym;
	sym = cin.get();
	cin.get();
	int isym = int(sym);
	if (isym > 127) {
		isym = isym + 64;
	}
	int *msym = new int[numwords];
	int i;
	for (i = 0; i < numwords; i++) {
		msym[i] = 0;
	}
	int inw,
		sumsym = 0,
		symmax = 0,
		symmin;
	cout << endl << "Данный символ кодируется следущими кодами: " << endl;
	int *mtr = new int[257];
	for (i = 0; i < 257; i++) {
		mtr[i] = 0;
	}
	for (i = 0; i < numsym - 1; i++) {
		if (arrmess[i] == isym) {
			inw = i % numwords;
			msym[inw]++;
			cout << (arrmess[i] + keywords[inw]) % 256 << " ";
			mtr[(arrmess[i] + keywords[inw]) % 256]++;
			sumsym++;
			if (msym[inw] > symmax) {
				symmax = msym[inw];
			}
		}
	}
	cout << endl << endl << "Символ в шифре, код символа и количество:" << endl;

	for (i = 0; i < 257; i++) {
		if (mtr[i] != 0) {
			cout << unsigned char(i) << setw(8) << i << setw(8) << mtr[i] << endl;
		}
	}
	symmin = msym[0];
	for (i = 1; i < numwords; i++) {
		if (msym[i] < symmin) {
			symmin = msym[i];
		}
	}
	double mid = double(sumsym) / numwords;
	cout << endl << "В среднем данный элемент попадает на одно кодовое слово " << mid << " раз(а)." << endl << endl;
	double symmax2 = (symmax - mid) / (mid / 100);
	double symmin2 = (mid - symmin) / (mid / 100);
	if (symmax2 > symmin2) {
		cout << "Значение максимального отклонения от нормы: " << symmax << ". В процентах: " << symmax2 << " %.";
	}
	else {
		cout << "Значение максимального отклонения от нормы: " << symmin << ". В процентах: " << symmin2 << " %.";
	}
	int ex;
	cout << endl << endl << "Вы хотите узнать статистику другого элемента? (1 - да, 0 - нет)" << endl;
	cin >> ex;
	cin.get();
	sumsym = 0;
	symmax = 0;
	delete[] msym;
	return ex;
}