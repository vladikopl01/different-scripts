#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;

struct MyStruct
{
	int n;
	int m;
	int** arr;
};

//int argc												- Переменная которая хранит кол-во передаваймых аргументов, всегда больше или равно единицы, 
//													      по скольку первым аргументом является адрес исполняемого файла .exe
//char* argv[]											- Указатель на массив строк, которыми являются переданные аргументы
int main(int argc, char* argv[]) {
	MyStruct data;

	//Объекты типа string
	string txt, binary;

	//Объект типа ifstream у которого по умолчанию стоит ios::in который отвечает за вывод данных из файла
	ifstream in;
	in.open("labka1.conf");

	if (argc == 5) {
		///Ввод данных через аргументы
		cout << "You have entered the required number of arguments" << endl;
		cout << "Reading arguments..." << endl;

		//argv[0] - Это строка адреса исполняемого файла .exe
		data.n = atoi(argv[1]);///Функция atoi() конвертирует строку, на которую указывает параметр str, в величину типа int
		data.m = atoi(argv[2]);
		txt = argv[3];
		binary = argv[4];

		cout << "N: " << data.n << endl;
		cout << "M: " << data.m << endl;
		cout << "Txt: " << txt << endl;
		cout << "Binary: " << binary << endl;

		cout << "Reading completed successfully!" << endl;
	}
	else if (in.is_open()) { ///is_open() это функция которая возвращает целые значения(1-файл открыт,0-открыт не был))
		///Ввод данных через файл конфига
		cout << "The input of the arguments failed!!!" << endl;
		cout << "Reading config file..." << endl;

		string line;

		//getline(file_name, string_name)				- Записывает строку из файла file_name в string_name
		//												  и возвращает true если запись произошла успешно
		while (getline(in, line)) {
			//line.erase(start_pos, end_pos)			- Удаляет с line строку началом которой есть start_pos до end_pos
			//remove_if(start_pos, end_pos, ::isspace)	- Очищает ячейки памяти в строке с координаты start_pos до end_pos все пробелы, табуляции и тд, 
			//											  вставляя их в конец строки и возвращяя координату начала пустых ячеек в строке
			//line.empty()								- Возвращает true если строка пустая

			line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
			if (line.empty()) continue;

			//line.find("character")					- Возвращает индекс позиции символа "character" в строке line
			int pos = line.find("=");

			//line.substr(start_pos, end_pos)			- Возвращает строку вырезаную из строки line с координаты start_pos до end_pos
			//line.substr(start_pos)					- Возвращает строку вырезаную из строки line с координаты start_pos до конца строки line
			if (line[0] == 'n' || line[0] == 'N') {
				data.n = stoi(line.substr(pos + 1));//извлекает знаковое целое число
			}
			if (line[0] == 'm' || line[0] == 'M') {
				data.m = stoi(line.substr(pos + 1));
			}

			if (line.substr(0, pos) == "txt" || line.substr(0, pos) == "Txt") {
				txt = line.substr(pos + 1);
			}
			if (line.substr(0, pos) == "binary" || line.substr(0, pos) == "Binary") {
				binary = line.substr(pos + 1);
			}
		}

		cout << "N: " << data.n << endl;
		cout << "M: " << data.m << endl;
		cout << "Txt: " << txt << endl;
		cout << "Binary: " << binary << endl;

		cout << "Reading completed successfully!" << endl;
	}
	else {
		///Ввод данных через консоль
		cout << "The input of the arguments failed!!!" << endl;
		cout << "The reading of config file failed!!!" << endl;
		cout << "Please, use keyboard to input values:" << endl;

		cout << "Enter N value: ";
		cin >> data.n;
		cout << "Enter M value: ";
		cin >> data.m;

		//cin.ignore(number, 'character')				- Удаляет все символы в количестве number пока не встретит символ 'character'
		//getline(cin, string)							- Считывание с потока ввода cin строки и запись ее в объект string
		cin.ignore(32767, '\n');
		cout << "Enter output file names: " << endl;
		cout << "Txt: ";
		getline(cin, txt);
		cout << "Binary: ";
		getline(cin, binary);

		cout << "Input completed successfully!" << endl;
	}

	///Динамическое выдиление памяти
	data.arr = new int* [data.n];
	for (int i = 0; i < data.n; i++) {
		data.arr[i] = new int[data.m];
	}

	///Инициализация матрицы
	for (int i = 0; i < data.n; i++) {
		for (int j = 0; j < data.m; j++) {
			data.arr[i][j] = i + j;
		}
	}

	///Вывод матрицы в консоль
	cout << "Array:" << endl;
	for (int i = 0; i < data.n; i++) {
		for (int j = 0; j < data.m; j++) {
			//setw(number)								- Подводит number мест под вывод в потоке для, в нашем случае, числа матрицы data.arr[i][j]
			cout << setw(5) << data.arr[i][j];
		}
		cout << endl;
	}

	///Запись данных в текстовый файл
	//Объект типа ofstream у которого по умолчанию стоит ios::out который отвечает за запись данных в файл
	ofstream out;
	//file_name += ".txt"								- Добавляем к строке file_name разширение ".txt" что бы функция file_name.open() создавала или открывала 
	//													  уже имеющийся файл file_name.txt, а не файл file_name без какого либа формата(разширения)
	out.open(txt += ".txt");
	if (out.is_open()) {
		out << "N = " << data.n << endl;
		out << "M = " << data.m << endl;
		out << "Array:" << endl;

		for (int i = 0; i < data.n; i++) {
			for (int j = 0; j < data.m; j++) {
				out << setw(5) << data.arr[i][j];
			}
			out << endl;
		}

	}
	out.close();

	///Запись данных в бинарный файл
	//Открываем файл с разширением .dat с использованием флага ios::binary для бинарной записи в файл
	out.open(binary += ".dat", ios::binary);
	if (out.is_open()) {
		//Побитовая запись в бинарный файл структуры data, запишется значения N и M, 
		//а также значение указателя, то есть адрес на динамически выделенную матрицу
		out.write((char*)&data, sizeof(data));
	}

	out.close();
	in.close();

	system("pause");
	return 0;
}