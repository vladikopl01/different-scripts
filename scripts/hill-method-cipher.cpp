#include <iostream>
#include <math.h>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

bool choice();

int** wordToCode(string&, int, int);
int** keyToCode(string&, int);

template <class T>
void outputMatrix(T**, int, int);

string encryption(int**, int, int, int**, int);
string decryption(int**, int, int, int**, int);

bool inverse(int**, float**, int);
float determinant(int**, int);
void allied(int**, int**, int);
void getMinor(int**, int**, int, int, int);
int gcdExtended(int, int, int&, int&);

int main() {
	string myWord;
	string keyWord;

	int** wordCode;
	int** keyCode;

	int wordLength;
	int keyCodeLength;

	int wordCodeRows;
	int wordCodeCols;

	do {

		//Ввод слов шифрования
		cout << "Enter word: ";
		cin >> myWord;
		cout << "Enter key: ";
		cin >> keyWord;

		//Перевод слов в верхний регистр
		transform(myWord.begin(), myWord.end(), myWord.begin(), ::toupper);
		transform(keyWord.begin(), keyWord.end(), keyWord.begin(), ::toupper);

		//Размерность векторов кода
		wordLength = myWord.length();
		keyCodeLength = sqrt(keyWord.length());
		wordCodeRows = keyCodeLength;
		wordCodeCols = ceil((float)wordLength / keyCodeLength);

		//Получение векторов кода для введенных слов шифрования
		wordCode = wordToCode(myWord, wordCodeRows, wordCodeCols);
		keyCode = keyToCode(keyWord, keyCodeLength);

		//Вывод кода слов
		cout << "Code for " << myWord << ": " << endl;
		outputMatrix(wordCode, wordCodeRows, wordCodeCols);
		cout << "Code for " << keyWord << ": " << endl;
		outputMatrix(keyCode, keyCodeLength, keyCodeLength);

		cout << "Enter number of function:" << endl
			<< "\t0. Encryption" << endl
			<< "\t1. Decryption" << endl;
		cout << "Your choice: ";

		switch (choice()) {
		case 0: {
			cout << "Encrypted word: " <<
				encryption(wordCode, wordCodeRows, wordCodeCols, keyCode, keyCodeLength)
				<< endl;
			break;
		}
		case 1: {
			cout << "Decrypted word: " <<
				decryption(wordCode, wordCodeRows, wordCodeCols, keyCode, keyCodeLength)
				<< endl;
			break;
		}
		}

		cout << "Continue? (1-yes, 0-no): ";
	} while (choice());

	system("pause");
	return 0;
}

bool choice() {
	int ch;
	do {
		cin >> ch;
		if (ch != 0 && ch != 1) {
			cout << "Incorrect input. Try again: ";
		}
	} while (ch != 0 && ch != 1);
	cin.get();
	if (ch == 1) {
		return true;
	}
	return false;
}

int** wordToCode(string& word, int rows, int cols) {
	int** ptr = new int* [rows];
	for (int i = 0; i < rows; i++) {
		ptr[i] = new int[cols];
	}

	int k = 0;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			ptr[i][j] = (k < word.length()) ? (word[k++]) % 64 : 0;
		}
	}

	return ptr;
}

int** keyToCode(string& key, int size) {
	int** ptr = new int* [size];
	for (int i = 0; i < size; i++) {
		ptr[i] = new int[size];
	}
	int k = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			ptr[i][j] = (key[k]) % 64;
			k++;
		}
	}

	return ptr;
}

template <class T>
void outputMatrix(T** ptr, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << setw(8) << setprecision(3) << ptr[i][j];
		}
		cout << endl;
	}
}

string encryption(int** word, int wordRows, int wordCols, int** key, int keySize) {
	string result;
	int** productMatrix = new int* [wordRows];
	for (int i = 0; i < wordRows; i++) {
		productMatrix[i] = new int[keySize];
	}

	//Умножение матриц слова и ключа
	for (int i = 0; i < wordRows; i++) {
		for (int j = 0; j < keySize; j++) {
			productMatrix[j][i] = 0;

			for (int k = 0; k < wordCols; k++) {
				productMatrix[j][i] += key[i][k] * word[j][k];
			}
		}
	}

	//Декодируем произведение
	for (int i = 0; i < wordRows; i++) {
		for (int j = 0; j < keySize; j++) {
			productMatrix[i][j] %= 26;
		}
	}

	//Перевод матрицы в строку
	int k = 0;
	for (int i = 0; i < wordRows; i++) {
		for (int j = 0; j < keySize; j++) {
			result += productMatrix[i][j] + 64;
		}
	}

	return result;
}

string decryption(int** word, int wordRows, int wordCols, int** key, int keySize) {
	string result;
	float** inverseKey = new float* [keySize];
	for (int i = 0; i < keySize; i++) {
		inverseKey[i] = new float[keySize];
	}
	int** productMatrix = new int* [wordRows];
	for (int i = 0; i < wordRows; i++) {
		productMatrix[i] = new int[wordCols];
	}

	//Обратная матрица ключа
	if (inverse(key, inverseKey, keySize)) {
		cout << "Fully inverted key:" << endl;
		outputMatrix(inverseKey, keySize, keySize);
	}
	else {
		return "Error! Key matrix is singular!";
	}

	//Умножение матриц слова и ключа
	for (int i = 0; i < wordRows; i++) {
		for (int j = 0; j < keySize; j++) {
			productMatrix[j][i] = 0;

			for (int k = 0; k < wordCols; k++) {
				productMatrix[j][i] += inverseKey[i][k] * word[j][k];
			}
		}
	}

	//Декодируем произведение
	for (int i = 0; i < wordRows; i++) {
		for (int j = 0; j < keySize; j++) {
			productMatrix[i][j] %= 26;
		}
	}

	//Перевод матрицы в строку
	int k = 0;
	for (int i = 0; i < wordRows; i++) {
		for (int j = 0; j < keySize; j++) {
			result += productMatrix[i][j] + 64;
		}
	}

	delete[]productMatrix;
	delete[]inverseKey;
	return result;
	//inverse - mult - mod
}

bool inverse(int** key, float** inverse, int keySize) {
	float det = determinant(key, keySize);
	if (det == 0) {
		return false;
	}

	int** adj = new int* [keySize];
	for (int i = 0; i < keySize; i++) {
		adj[i] = new int[keySize];
	}



	allied(key, adj, keySize);

	cout << "Key det: " << determinant(adj, keySize) << endl;

	cout << "Allied key matrix:" << endl;
	outputMatrix(adj, keySize, keySize);

	int x, y;
	int gcd = gcdExtended(determinant(adj, keySize), 26, x, y);
	if ((det < 0 && x > 0) || (det > 0 && x > 0)) gcd = x;
	if (det > 0 && x < 0) gcd = 26 + x;
	if (det < 0 && x < 0) gcd = -x;

	cout << "Inverted det: " << gcd << endl;

	for (int i = 0; i < keySize; i++) {
		for (int j = 0; j < keySize; j++) {
			inverse[i][j] = adj[i][j] / det;
		}
	}

	cout << "Inverted matrix: " << endl;
	outputMatrix(inverse, keySize, keySize);

	for (int i = 0; i < keySize; i++) {
		for (int j = 0; j < keySize; j++) {
			inverse[i][j] = (adj[i][j] * gcd) % 26;
			if (inverse[i][j] < 0) {
				inverse[i][j] += 26;
			}
		}
	}

	delete[]adj;
	return true;
}

float determinant(int** arr, int n) {
	int Det = 0;

	if (n == 1) return arr[0][0];

	int** temp = new int* [n];
	for (int i = 0; i < n; i++) {
		temp[i] = new int[n];
	}

	int sign = 1;

	for (int f = 0; f < n; f++) {
		getMinor(arr, temp, 0, f, n);

		Det += sign * arr[0][f] * determinant(temp, n - 1);
		sign *= -1;
	}

	delete[]temp;
	return Det;
}

void allied(int** arr, int** adj, int n) {
	if (n == 1) {
		adj[0][0] = 1;
		return;
	}

	int sign = 1;
	int** temp = new int* [n];
	for (int i = 0; i < n; i++) {
		temp[i] = new int[n];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			getMinor(arr, temp, i, j, n);

			sign = ((i + j) % 2 == 0) ? 1 : -1;

			//Сразу транспонирование [j][i] вместо [i][j]
			adj[j][i] = (sign) * (determinant(temp, n - 1));
		}
	}

	delete[]temp;
}

void getMinor(int** arr, int** temp, int p, int q, int n) {
	int i = 0;
	int j = 0;

	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			if (row != p && col != q) {
				temp[i][j] = arr[row][col];

				//Если конец строки
				if (j == n - 1) {
					j = 0;
					i++;
				}
			}
		}
	}
}

int gcdExtended(int a, int modulo, int& x, int& y) {
	if (a == 0) {
		x = 0;
		y = 1;
		return modulo;
	}

	int x1, y1;
	int gcd = gcdExtended(modulo % a, a, x1, y1);

	x = y1 - (modulo / a) * x1;
	y = x1;

	return gcd;
}