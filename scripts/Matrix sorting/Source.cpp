#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <ctime>

using namespace std;

struct MyStruct
{
	int n;
	int m;
	int** arr;
};

void initArr(int**, int, int);
void outArr(int**, int, int);
void fileArr(int**, int, int, ofstream&);

void bubbleSort(int*, int);
void insertSort(int*, int);
void selectionSort(int*, int);

int* convertToArray(int**, int, int);
int** convertToMatrix(int*, int, int);

int main() {
	//srand(time(0));

	MyStruct data;

	//Объекты типа string
	string txt;

	//Объект типа ifstream у которого по умолчанию стоит ios::in который отвечает за вывод данных из файла
	ifstream in;

	//Объект типа ofstream у которого по умолчанию стоит ios::out который отвечает за запись данных в файл
	ofstream out;

	in.open("lab2.conf");

	if (in.is_open()) {
		///Ввод данных через файл конфига
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
				data.n = stoi(line.substr(pos + 1));
			}

			if (line[0] == 'm' || line[0] == 'M') {
				data.m = stoi(line.substr(pos + 1));
			}

			if (line.substr(0, pos) == "txt" || line.substr(0, pos) == "Txt") {
				txt = line.substr(pos + 1);
			}
		}

		cout << "N: " << data.n << endl;
		cout << "M: " << data.m << endl;
		cout << "Txt: " << txt << endl;

		cout << "Reading completed successfully!" << endl;
	}
	else {
		///Ввод данных через консоль
		cout << "The reading of config file failed!!!" << endl;
		cout << "Please, use keyboard to input values:" << endl;

		cout << "Enter N value: ";
		cin >> data.n;
		cout << "Enter M value: ";
		cin >> data.m;

		//cin.ignore(number, 'character')				- Удаляет все символы с потока в количестве number пока не встретит символ 'character'
		//getline(cin, string)							- Считывание с потока ввода cin строки и записывать ее в объект string
		cin.ignore(32767, '\n');
		cout << "Enter output file name: " << endl;
		cout << "Txt: ";
		getline(cin, txt);

		cout << "Input completed successfully!" << endl;
	}

	//file_name += ".txt"								- Добавляем к строке file_name разширение ".txt" что бы функция file_name.open() создавала или открывала 
	//													  уже имеющийся файл file_name.txt, а не файл file_name без какого либа формата(разширения)
	txt += ".txt";
	out.open(txt);

	///Динамическое выдиление памяти
	data.arr = new int* [data.n];
	for (int i = 0; i < data.n; i++) {
		data.arr[i] = new int[data.m];
	}

	int tempSize = data.n * data.m;
	int* tempArr = new int[tempSize];

	getchar();
	system("cls");
	///Инициализация и вывод начальной матрицы в консоль и файл
	initArr(data.arr, data.n, data.m); //Инициализация матрицы значениями
	cout << "Array:" << endl;
	outArr(data.arr, data.n, data.m); //Вывод в консоль
	out << "Array:" << endl;
	fileArr(data.arr, data.n, data.m, out); //Вывод в файл

	///1. Сортировка пузырьком и вывод результата
	tempArr = convertToArray(data.arr, data.n, data.m); //Перевод матрицы в массив
	bubbleSort(tempArr, tempSize); //Сортировка массива методом ...
	data.arr = convertToMatrix(tempArr, data.n, data.m); //Возврат матрицы через массив
	cout << "Bubble:" << endl;
	outArr(data.arr, data.n, data.m);
	out << "Bubble:" << endl;
	fileArr(data.arr, data.n, data.m, out);
	out << endl;

	getchar();
	system("cls");
	///Востановление матрицы
	initArr(data.arr, data.n, data.m);
	cout << "Array:" << endl;
	outArr(data.arr, data.n, data.m);
	out << "Array:" << endl;
	fileArr(data.arr, data.n, data.m, out);

	///2. Сортировка пузырьком и вывод результата
	tempArr = convertToArray(data.arr, data.n, data.m);
	insertSort(tempArr, tempSize);
	data.arr = convertToMatrix(tempArr, data.n, data.m);
	cout << "Insert:" << endl;
	outArr(data.arr, data.n, data.m);
	out << "Insert:" << endl;
	fileArr(data.arr, data.n, data.m, out);
	out << endl;

	getchar();
	system("cls");
	///Востановление матрицы
	initArr(data.arr, data.n, data.m);
	cout << "Array:" << endl;
	outArr(data.arr, data.n, data.m);
	out << "Array:" << endl;
	fileArr(data.arr, data.n, data.m, out);

	///3. Сортировка пузырьком и вывод результата
	tempArr = convertToArray(data.arr, data.n, data.m);
	selectionSort(tempArr, tempSize);
	data.arr = convertToMatrix(tempArr, data.n, data.m);
	cout << "Selection:" << endl;
	outArr(data.arr, data.n, data.m);
	out << "Selection:" << endl;
	fileArr(data.arr, data.n, data.m, out);

	getchar();
	system("cls");

	out.close();
	in.close();

	system("pause");
	return 0;
}

///Инициализация матрицы
void initArr(int** arr, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			arr[i][j] = rand() % 9;
		}
	}
}

///Вывод матрицы в консоль
void outArr(int** arr, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			//setw(number)								- Подводит number мест под вывод в потоке для, в нашем случае, числа матрицы data.arr[i][j]
			cout << setw(4) << arr[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

///Вывод матрицы в файл
void fileArr(int** arr, int n, int m, ofstream& file) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			file << setw(4) << arr[i][j];
		}
		file << endl;
	}
	file << endl;
}

///Сортировка пузырьком
void bubbleSort(int* arr, int n) {
	int temp;

	bool swapped;
	for (int i = 0; i < n - 1; i++) {
		swapped = false;
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				swapped = true;
			}
		}

		//Если при текущей итерации не было изменений то значит массив отсортирован и мы прекращаем сотрировку
		if (swapped == false) break;
	}
}

///Сортировка вставками
void insertSort(int* arr, int n) {
	int temp, j;

	for (int i = 1; i < n; i++)
	{
		temp = arr[i];
		j = i - 1;

		while (j >= 0 && arr[j] > temp)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = temp;
	}
}

///Сортировка выбором
void selectionSort(int* arr, int n) {
	int min, temp;

	for (int i = 0; i < n - 1; i++) {
		min = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[j] < arr[min]) {
				min = j;
			}
		}

		temp = arr[min];
		arr[min] = arr[i];
		arr[i] = temp;
	}
}

///Конвертация
int* convertToArray(int** matrix, int n, int m) {
	int k = 0;
	int* arr = new int[n * m];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			arr[k++] = matrix[i][j];
		}
	}

	return arr;
}

int** convertToMatrix(int* arr, int n, int m) {
	int k = 0;
	int** matrix = new int* [n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new int[m];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			matrix[i][j] = arr[k++];
		}
	}

	return matrix;
}