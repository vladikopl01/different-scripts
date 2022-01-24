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

//int argc												- ���������� ������� ������ ���-�� ������������ ����������, ������ ������ ��� ����� �������, 
//													      �� ������� ������ ���������� �������� ����� ������������ ����� .exe
//char* argv[]											- ��������� �� ������ �����, �������� �������� ���������� ���������
int main(int argc, char* argv[]) {
	MyStruct data;

	//������� ���� string
	string txt, binary;

	//������ ���� ifstream � �������� �� ��������� ����� ios::in ������� �������� �� ����� ������ �� �����
	ifstream in;
	in.open("labka1.conf");

	if (argc == 5) {
		///���� ������ ����� ���������
		cout << "You have entered the required number of arguments" << endl;
		cout << "Reading arguments..." << endl;

		//argv[0] - ��� ������ ������ ������������ ����� .exe
		data.n = atoi(argv[1]);///������� atoi() ������������ ������, �� ������� ��������� �������� str, � �������� ���� int
		data.m = atoi(argv[2]);
		txt = argv[3];
		binary = argv[4];

		cout << "N: " << data.n << endl;
		cout << "M: " << data.m << endl;
		cout << "Txt: " << txt << endl;
		cout << "Binary: " << binary << endl;

		cout << "Reading completed successfully!" << endl;
	}
	else if (in.is_open()) { ///is_open() ��� ������� ������� ���������� ����� ��������(1-���� ������,0-������ �� ���))
		///���� ������ ����� ���� �������
		cout << "The input of the arguments failed!!!" << endl;
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
				data.n = stoi(line.substr(pos + 1));//��������� �������� ����� �����
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
		///���� ������ ����� �������
		cout << "The input of the arguments failed!!!" << endl;
		cout << "The reading of config file failed!!!" << endl;
		cout << "Please, use keyboard to input values:" << endl;

		cout << "Enter N value: ";
		cin >> data.n;
		cout << "Enter M value: ";
		cin >> data.m;

		//cin.ignore(number, 'character')				- ������� ��� ������� � ���������� number ���� �� �������� ������ 'character'
		//getline(cin, string)							- ���������� � ������ ����� cin ������ � ������ �� � ������ string
		cin.ignore(32767, '\n');
		cout << "Enter output file names: " << endl;
		cout << "Txt: ";
		getline(cin, txt);
		cout << "Binary: ";
		getline(cin, binary);

		cout << "Input completed successfully!" << endl;
	}

	///������������ ��������� ������
	data.arr = new int* [data.n];
	for (int i = 0; i < data.n; i++) {
		data.arr[i] = new int[data.m];
	}

	///������������� �������
	for (int i = 0; i < data.n; i++) {
		for (int j = 0; j < data.m; j++) {
			data.arr[i][j] = i + j;
		}
	}

	///����� ������� � �������
	cout << "Array:" << endl;
	for (int i = 0; i < data.n; i++) {
		for (int j = 0; j < data.m; j++) {
			//setw(number)								- �������� number ���� ��� ����� � ������ ���, � ����� ������, ����� ������� data.arr[i][j]
			cout << setw(5) << data.arr[i][j];
		}
		cout << endl;
	}

	///������ ������ � ��������� ����
	//������ ���� ofstream � �������� �� ��������� ����� ios::out ������� �������� �� ������ ������ � ����
	ofstream out;
	//file_name += ".txt"								- ��������� � ������ file_name ���������� ".txt" ��� �� ������� file_name.open() ��������� ��� ��������� 
	//													  ��� ��������� ���� file_name.txt, � �� ���� file_name ��� ������ ���� �������(����������)
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

	///������ ������ � �������� ����
	//��������� ���� � ����������� .dat � �������������� ����� ios::binary ��� �������� ������ � ����
	out.open(binary += ".dat", ios::binary);
	if (out.is_open()) {
		//��������� ������ � �������� ���� ��������� data, ��������� �������� N � M, 
		//� ����� �������� ���������, �� ���� ����� �� ����������� ���������� �������
		out.write((char*)&data, sizeof(data));
	}

	out.close();
	in.close();

	system("pause");
	return 0;
}