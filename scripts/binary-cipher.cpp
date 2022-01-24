#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

using namespace std;

bool choice();

string readingFile(ifstream&);

string wordToBinary(string*);
string binaryToWord(string*);

int main() {
	system("chcp 1251");

	//Параметри
	bool menuChoice; //Вибір меню
	bool inputChoice; //Вибір способу введення
	int precision; //Точність кодування
	int countZeros; //К-ть нульових бітів

	//Назви файлів
	string inputFileName; //Назва файлу введення
	string outputFileName; //Назва файлу виведення

	//Тимчасові змінні
	string data; //Введенні дані
	string binaryWord; //Дані в двійковому форматі
	string result; //Результат роботи

	//Файли
	ifstream inFile; //Файл введення
	ofstream outFile; //Файл виведення

	do {
		//Меню вибору роботи з програмою
		system("cls");
		cout << "1. Шифрування" << endl;
		cout << "2. Розшифрування" << endl;
		cout << "Ваш вибір: ";
		menuChoice = choice();

		//Введення точності кодування
		system("cls");
		cout << "Введіть точність кодування: ";
		do {
			cin >> precision;

			//Якщо ввід не успішний
			if (precision < 1) {
				cout << "Помилка!! Введіть значення більше 1!!" << endl;
				cout << "Спробуйте знову: ";
			}
		} while (precision < 1);

		//Меню вибору способу введення даних
		system("cls");
		cout << "Виберіть спосіб введення даних:" << endl;
		cout << "1. Зчитати дані з файлу" << endl;
		cout << "2. Ввести за допомогою клавіатури" << endl;
		cout << "Ваш вибір: ";
		inputChoice = choice();

		if (inputChoice) {
			//1. Зчитування з файлу

			//Введення назви файлу
			system("cls");
			cout << "Введіть назву файлу введення: ";
			do {
				cin >> inputFileName;

				//Відкриття файлу введення
				inFile.open(inputFileName + ".txt");

				//Перевірка на існування файлу введення
				if (!inFile.is_open()) {
					cout << "Помилка!! Файлу введення не існує з таким ім'ям" << endl << endl;
					cout << "Спробуйте знову: ";
				}
			} while (!inFile.is_open());

			//Зчитування даних з файлу
			system("cls");
			data = readingFile(inFile);
		}
		else {
			//2. Ввід з клавіатури
			string line;

			//Очищення потоку введення
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			system("cls");
			cout << "Введіть текст котрий хочете використати \n(останнім символом повинен бути ~): " << endl;
			getline(cin, data, '~');

			//Очищення потоку від сміття після симолу ~
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		//Введення назви файлу виведення
		system("cls");
		cout << "Введіть назву файлу виведення: ";
		cin >> outputFileName;

		//Відкриття файлу виведення
		outFile.open(outputFileName + ".txt");

		system("cls");
		if (menuChoice) {
			///1. Шифрування
			//Перетворення даних у бінарний код
			binaryWord = wordToBinary(&data);

			//Множення кожного нуля та одиниці на точність
			for (int i = 0; i < binaryWord.length(); i+=precision) {
				binaryWord.insert(i, precision - 1, binaryWord[i]);
			}

			//Перетворення нового бінарного коду в зашифровані дані
			result = binaryToWord(&binaryWord);
		}
		else {
			///2. Розшифрування 
			//Перетворення зашифрованих даних в бінарний код
			binaryWord = wordToBinary(&data);

			//Видалення зайвих нулів та одиниць
			for (int i = 0; i < binaryWord.length(); i++) {
				countZeros = 0;

				//Підрахунок кількості нулів при заданій точності
				for (int j = 0; j < precision; j++) {
					if (binaryWord[i + j] == '0') countZeros++;
				}

				//Видалення старих байтів
				binaryWord.erase(i, precision);

				//Вставка 0 чи 1 в залежності від кількості
				if (countZeros >= ceil((double)precision / 2)) {
					//Вставка 0, якщо нулів >= ніж половина точності
					binaryWord.insert(i, 1, '0');
				}
				else {
					//Вставка 1, якщо нулів < ніж половина точності
					binaryWord.insert(i, 1, '1');
				}
			}

			//Перетворення нового бінарного коду в розшифровані дані
			result = binaryToWord(&binaryWord);
		}

		//виведення всіх даних з результатом
		cout << "Результат " << (menuChoice ? "шифрування:" : "розшифрування:") << endl << endl;
		cout << "Точність: " << precision << endl << endl;
		cout << (inputChoice ? "Файл введення: " + inputFileName + "\n" : "");
		cout << "Файл виведення: " << outputFileName << endl << endl;
		cout << "Ваші дані:" << endl;
		cout << data << endl << endl;
		cout << "Результат:" << endl;
		cout << result << endl << endl;

		//Запис результату до файлу
		outFile << result << endl;
		
		//Закриття файлів
		inFile.close();
		outFile.close();

		//Запит на продовження роботи з програмою
		cout << "Продовжити роботу? (1 - так, 2 - ні): ";
	} while (choice());
	
	return 0;
}

//Функція вибору (1 чи 2)
bool choice() {
	int ch;
	do {
		cin >> ch;
		if (ch != 1 && ch != 2) {
			cout << "Помилка!! Число повинно бути 1 чи 2!!" << endl;
			cout << "Спробуйте знову: ";
		}
	} while (ch != 1 && ch != 2);

	if (ch == 1) {
		return true;
	}
	return false;
}

//Зчитування всіх даних з файлу 
string readingFile(ifstream &file) {
	//Зчитування всього файлу з потоку введення
	string data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

	return data;
}

//Перетворення даних в бінарний код
string wordToBinary(string *word) {
	string resultedBinary;
	int number;

	//Проходження по кожну символу
	for (int i = 0; i < word->length(); i++) {
		number = (*word)[i];

		//Запис кожного біту бінарного коду поточного символу
		for (int i = 7; i >= 0; i--) {
			int k = number >> i;
			(k & 1) ? resultedBinary += '1' : resultedBinary += '0';
		}
	}

	return resultedBinary;
}

//Перетворення бінарного коду в дані
string binaryToWord(string *binary) {
	string word;
	int temp;
	int sum;
	int base;

	//Проходження всьго бінарного коду по 8 бітів
	for (int i = 0; i < binary->length(); i += 8) {
		sum = 0;
		base = 1;

		//Вирізання 8-ми бітів і перетворення їх в число
		temp = stoi(binary->substr(i, 8));

		//Отримання числа з 8-ми бітного значення
		while (temp) {
			sum += temp % 10 * base;

			temp /= 10;
			base *= 2;
		}

		//Запис отриманого символу до результуючих даних
		word += (char)sum;
	}

	return word;
}