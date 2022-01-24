#include <iostream>
#include <ctime>
#include <fstream>
#include <clocale>

using namespace std;

const char ch = '\n';
const char len = 15;
const char strings = 41;

int ind = 1;

void correctAnswer(char**, int, int);

int main() {
	srand(time(0));
	setlocale(LC_CTYPE, "Russian");

	int choice;
	int gen;

	//Array declaration
	char **names = new char*[strings];
	for (int i = 0; i < strings; i++) {
		names[i] = new char[len];
	}

	//Opening file
	ifstream file;
	file.open("Names.txt", ios::in);
	if (!file) return 1;

	//Getting names from file
	for (int i = 0; i < strings; i++) {
		file.getline(names[i], 20, ch);
	}

	cout << "����! ������ ��� ���:" << endl;
	cout <<
		" 1 - ��������\n" <<
		" 2 - ����������\n" <<
		" 3 - ��������\n" <<
		" 0 - �����\n" <<
		endl;

	//Game
	do {
		cout << ind++;

		cout << endl;

		gen = rand() % 41;

		cout << " ��� ����� " << names[gen] << " ?" << endl;

		cout << " ������� �����: ";
		cin >> choice;
		if (choice) {
			//cout << names[gen];
			correctAnswer(names, choice, gen);
		}
	} while (choice != 0);



	file.close();
	system("pause");
	return 0;
}

void correctAnswer(char **names, int choice, int gen) {
	int work;
	char *name = new char[len];

	if (gen < 19) {
		work = 1;
	}
	if (gen >= 19 && gen <= 27) {
		work = 2;
	}
	if (gen > 27) {
		work = 3;
	}
	for (int i = 0; i < len; i++) {
		name[i] = *(*(names + gen) + i);
	}
	if (choice == work) {
		switch (choice) {
		case 1:
			cout << " ���������! " << name << " - ��������." << endl;
			break;
		case 2:
			cout << " ���������! " << name << " - ����������." << endl;
			break;
		case 3:
			cout << " ���������! " << name << " - ��������." << endl;
			break;
		}
	}
	else {
		switch (work) {
		case 1:
			cout << " ����� �� ������!" << name << " - ��������." << endl;
			break;
		case 2:
			cout << " ����� �� ������!" << name << " - ����������." << endl;
			break;
		case 3:
			cout << " ����� �� ������!" << name << " - ��������." << endl;
			break;
		}
	}
}