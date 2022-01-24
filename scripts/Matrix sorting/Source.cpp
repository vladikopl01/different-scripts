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

	//������� ���� string
	string txt;

	//������ ���� ifstream � �������� �� ��������� ����� ios::in ������� �������� �� ����� ������ �� �����
	ifstream in;

	//������ ���� ofstream � �������� �� ��������� ����� ios::out ������� �������� �� ������ ������ � ����
	ofstream out;

	in.open("lab2.conf");

	if (in.is_open()) {
		///���� ������ ����� ���� �������
		cout << "Reading config file..." << endl;

		string line;

		//getline(file_name, string_name)				- ���������� ������ �� ����� file_name � string_name
		//												  � ���������� true ���� ������ ��������� �������
		while (getline(in, line)) {
			//line.erase(start_pos, end_pos)			- ������� � line ������ ������� ������� ���� start_pos �� end_pos
			//remove_if(start_pos, end_pos, ::isspace)	- ������� ������ ������ � ������ � ���������� start_pos �� end_pos ��� �������, ��������� � ��, 
			//											  �������� �� � ����� ������ � ��������� ���������� ������ ������ ����� � ������
			//line.empty()								- ���������� true ���� ������ ������

			line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
			if (line.empty()) continue;

			//line.find("character")					- ���������� ������ ������� ������� "character" � ������ line
			int pos = line.find("=");

			//line.substr(start_pos, end_pos)			- ���������� ������ ��������� �� ������ line � ���������� start_pos �� end_pos
			//line.substr(start_pos)					- ���������� ������ ��������� �� ������ line � ���������� start_pos �� ����� ������ line
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
		///���� ������ ����� �������
		cout << "The reading of config file failed!!!" << endl;
		cout << "Please, use keyboard to input values:" << endl;

		cout << "Enter N value: ";
		cin >> data.n;
		cout << "Enter M value: ";
		cin >> data.m;

		//cin.ignore(number, 'character')				- ������� ��� ������� � ������ � ���������� number ���� �� �������� ������ 'character'
		//getline(cin, string)							- ���������� � ������ ����� cin ������ � ���������� �� � ������ string
		cin.ignore(32767, '\n');
		cout << "Enter output file name: " << endl;
		cout << "Txt: ";
		getline(cin, txt);

		cout << "Input completed successfully!" << endl;
	}

	//file_name += ".txt"								- ��������� � ������ file_name ���������� ".txt" ��� �� ������� file_name.open() ��������� ��� ��������� 
	//													  ��� ��������� ���� file_name.txt, � �� ���� file_name ��� ������ ���� �������(����������)
	txt += ".txt";
	out.open(txt);

	///������������ ��������� ������
	data.arr = new int* [data.n];
	for (int i = 0; i < data.n; i++) {
		data.arr[i] = new int[data.m];
	}

	int tempSize = data.n * data.m;
	int* tempArr = new int[tempSize];

	getchar();
	system("cls");
	///������������� � ����� ��������� ������� � ������� � ����
	initArr(data.arr, data.n, data.m); //������������� ������� ����������
	cout << "Array:" << endl;
	outArr(data.arr, data.n, data.m); //����� � �������
	out << "Array:" << endl;
	fileArr(data.arr, data.n, data.m, out); //����� � ����

	///1. ���������� ��������� � ����� ����������
	tempArr = convertToArray(data.arr, data.n, data.m); //������� ������� � ������
	bubbleSort(tempArr, tempSize); //���������� ������� ������� ...
	data.arr = convertToMatrix(tempArr, data.n, data.m); //������� ������� ����� ������
	cout << "Bubble:" << endl;
	outArr(data.arr, data.n, data.m);
	out << "Bubble:" << endl;
	fileArr(data.arr, data.n, data.m, out);
	out << endl;

	getchar();
	system("cls");
	///������������� �������
	initArr(data.arr, data.n, data.m);
	cout << "Array:" << endl;
	outArr(data.arr, data.n, data.m);
	out << "Array:" << endl;
	fileArr(data.arr, data.n, data.m, out);

	///2. ���������� ��������� � ����� ����������
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
	///������������� �������
	initArr(data.arr, data.n, data.m);
	cout << "Array:" << endl;
	outArr(data.arr, data.n, data.m);
	out << "Array:" << endl;
	fileArr(data.arr, data.n, data.m, out);

	///3. ���������� ��������� � ����� ����������
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

///������������� �������
void initArr(int** arr, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			arr[i][j] = rand() % 9;
		}
	}
}

///����� ������� � �������
void outArr(int** arr, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			//setw(number)								- �������� number ���� ��� ����� � ������ ���, � ����� ������, ����� ������� data.arr[i][j]
			cout << setw(4) << arr[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

///����� ������� � ����
void fileArr(int** arr, int n, int m, ofstream& file) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			file << setw(4) << arr[i][j];
		}
		file << endl;
	}
	file << endl;
}

///���������� ���������
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

		//���� ��� ������� �������� �� ���� ��������� �� ������ ������ ������������ � �� ���������� ����������
		if (swapped == false) break;
	}
}

///���������� ���������
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

///���������� �������
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

///�����������
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