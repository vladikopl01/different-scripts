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

	//���������
	bool menuChoice; //���� ����
	bool inputChoice; //���� ������� ��������
	int precision; //������� ���������
	int countZeros; //�-�� �������� ���

	//����� �����
	string inputFileName; //����� ����� ��������
	string outputFileName; //����� ����� ���������

	//�������� ����
	string data; //������� ���
	string binaryWord; //��� � ��������� ������
	string result; //��������� ������

	//�����
	ifstream inFile; //���� ��������
	ofstream outFile; //���� ���������

	do {
		//���� ������ ������ � ���������
		system("cls");
		cout << "1. ����������" << endl;
		cout << "2. �������������" << endl;
		cout << "��� ����: ";
		menuChoice = choice();

		//�������� ������� ���������
		system("cls");
		cout << "������ ������� ���������: ";
		do {
			cin >> precision;

			//���� ��� �� �������
			if (precision < 1) {
				cout << "�������!! ������ �������� ����� 1!!" << endl;
				cout << "��������� �����: ";
			}
		} while (precision < 1);

		//���� ������ ������� �������� �����
		system("cls");
		cout << "������� ����� �������� �����:" << endl;
		cout << "1. ������� ��� � �����" << endl;
		cout << "2. ������ �� ��������� ���������" << endl;
		cout << "��� ����: ";
		inputChoice = choice();

		if (inputChoice) {
			//1. ���������� � �����

			//�������� ����� �����
			system("cls");
			cout << "������ ����� ����� ��������: ";
			do {
				cin >> inputFileName;

				//³������� ����� ��������
				inFile.open(inputFileName + ".txt");

				//�������� �� ��������� ����� ��������
				if (!inFile.is_open()) {
					cout << "�������!! ����� �������� �� ���� � ����� ��'��" << endl << endl;
					cout << "��������� �����: ";
				}
			} while (!inFile.is_open());

			//���������� ����� � �����
			system("cls");
			data = readingFile(inFile);
		}
		else {
			//2. ��� � ���������
			string line;

			//�������� ������ ��������
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			system("cls");
			cout << "������ ����� ������ ������ ����������� \n(������� �������� ������� ���� ~): " << endl;
			getline(cin, data, '~');

			//�������� ������ �� ����� ���� ������ ~
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		//�������� ����� ����� ���������
		system("cls");
		cout << "������ ����� ����� ���������: ";
		cin >> outputFileName;

		//³������� ����� ���������
		outFile.open(outputFileName + ".txt");

		system("cls");
		if (menuChoice) {
			///1. ����������
			//������������ ����� � ������� ���
			binaryWord = wordToBinary(&data);

			//�������� ������� ���� �� ������� �� �������
			for (int i = 0; i < binaryWord.length(); i+=precision) {
				binaryWord.insert(i, precision - 1, binaryWord[i]);
			}

			//������������ ������ �������� ���� � ���������� ���
			result = binaryToWord(&binaryWord);
		}
		else {
			///2. ������������� 
			//������������ ������������ ����� � ������� ���
			binaryWord = wordToBinary(&data);

			//��������� ������ ���� �� �������
			for (int i = 0; i < binaryWord.length(); i++) {
				countZeros = 0;

				//ϳ�������� ������� ���� ��� ������ �������
				for (int j = 0; j < precision; j++) {
					if (binaryWord[i + j] == '0') countZeros++;
				}

				//��������� ������ �����
				binaryWord.erase(i, precision);

				//������� 0 �� 1 � ��������� �� �������
				if (countZeros >= ceil((double)precision / 2)) {
					//������� 0, ���� ���� >= �� �������� �������
					binaryWord.insert(i, 1, '0');
				}
				else {
					//������� 1, ���� ���� < �� �������� �������
					binaryWord.insert(i, 1, '1');
				}
			}

			//������������ ������ �������� ���� � ����������� ���
			result = binaryToWord(&binaryWord);
		}

		//��������� ��� ����� � �����������
		cout << "��������� " << (menuChoice ? "����������:" : "�������������:") << endl << endl;
		cout << "�������: " << precision << endl << endl;
		cout << (inputChoice ? "���� ��������: " + inputFileName + "\n" : "");
		cout << "���� ���������: " << outputFileName << endl << endl;
		cout << "���� ���:" << endl;
		cout << data << endl << endl;
		cout << "���������:" << endl;
		cout << result << endl << endl;

		//����� ���������� �� �����
		outFile << result << endl;
		
		//�������� �����
		inFile.close();
		outFile.close();

		//����� �� ����������� ������ � ���������
		cout << "���������� ������? (1 - ���, 2 - �): ";
	} while (choice());
	
	return 0;
}

//������� ������ (1 �� 2)
bool choice() {
	int ch;
	do {
		cin >> ch;
		if (ch != 1 && ch != 2) {
			cout << "�������!! ����� ������� ���� 1 �� 2!!" << endl;
			cout << "��������� �����: ";
		}
	} while (ch != 1 && ch != 2);

	if (ch == 1) {
		return true;
	}
	return false;
}

//���������� ��� ����� � ����� 
string readingFile(ifstream &file) {
	//���������� ������ ����� � ������ ��������
	string data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

	return data;
}

//������������ ����� � ������� ���
string wordToBinary(string *word) {
	string resultedBinary;
	int number;

	//����������� �� ����� �������
	for (int i = 0; i < word->length(); i++) {
		number = (*word)[i];

		//����� ������� ��� �������� ���� ��������� �������
		for (int i = 7; i >= 0; i--) {
			int k = number >> i;
			(k & 1) ? resultedBinary += '1' : resultedBinary += '0';
		}
	}

	return resultedBinary;
}

//������������ �������� ���� � ���
string binaryToWord(string *binary) {
	string word;
	int temp;
	int sum;
	int base;

	//����������� ����� �������� ���� �� 8 ���
	for (int i = 0; i < binary->length(); i += 8) {
		sum = 0;
		base = 1;

		//�������� 8-�� ��� � ������������ �� � �����
		temp = stoi(binary->substr(i, 8));

		//��������� ����� � 8-�� ������ ��������
		while (temp) {
			sum += temp % 10 * base;

			temp /= 10;
			base *= 2;
		}

		//����� ���������� ������� �� ������������ �����
		word += (char)sum;
	}

	return word;
}