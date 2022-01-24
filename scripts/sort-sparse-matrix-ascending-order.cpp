#include <iostream>
#include <ctime>
#include <iomanip>
#include <map>

using namespace std;

int **declArr(int);
void delArr(int **, int);

void initArr(int **, int);
void output(int **, int);

void toDictionary(map<pair<int, int>, int> *, int **, int);
int **toArr(map<pair<int, int>, int> *, int);

void output(map<pair<int, int>, int> *);

void sortDictionary(map<pair<int, int>, int> *, int);

int main() {
	srand(time(0));

	int **arr; //��������� �� ��������� �������
	int size; //������ ��������� �������

	map<pair<int, int>, int> sparseArr; //��������� ��� ���������� �������

	//���� ������� ��������� �������
	cout << "Enter size of matrix: ";
	do {
		cin >> size;
		if (size <= 0) {
			cout << "Try again: ";
		}
	} while (size <= 0);

	arr = declArr(size); //��������� ������ ��� ���������
	initArr(arr, size); //������������� ���������� ��������� �������
	cout << "Started matrix:" << endl;
	output(arr, size); //����� ��������� �������

	toDictionary(&sparseArr, arr, size); //������� ��������� ������� � ����������� ���������
	cout << "Sparsed matrix:" << endl;
	output(&sparseArr); //����� ����������� �������

	sortDictionary(&sparseArr, size); //���������� ���������� �� �������
	cout << "Sorted sparsed matrix:" << endl;
	output(&sparseArr); //����� ��������������� ����������

	delArr(arr, size); //������������ ������ ��� ����� �������
	arr = toArr(&sparseArr, size); //������� ���������� � ���������� ����
	cout << "Sorted matrix:" << endl;
	output(arr, size); //����� ����� ��������������� �������

	delArr(arr, size); //������������ ������

	system("pause");
	return 0;
}

//��������� ������ ��� �������
int **declArr(int n) {
	int **arr = new int *[n];
	for (int i = 0; i < n; i++) {
		*(arr + i) = new int[n];
	}
	return arr;
}

//������������ ������
void delArr(int **arr, int n) {
	for (int i = 0; i < n; i++) {
		delete[] arr[i];
	}
	delete[] arr;
}

//������������� ������� ����������
void initArr(int **arr, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			//40% ��������� ������� ����� ������
			*(*(arr + i) + j) = (rand() % 10) <= 3 ? 0 : (rand() % 9 + 1);
		}
	}
}

//����� �������
void output(int **arr, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << setw(3) << *(*(arr + i) + j);
		}
		cout << endl;
	}
}

//������� ������� � ����������� ���
void toDictionary(map<pair<int, int>, int> *sparsed, int **arr, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (arr[i][j] != 0) {
				(*sparsed)[make_pair(i, j)] = arr[i][j];
			}
		}
	}
}

//������� ����������� ������� � ������� ���
int **toArr(map<pair<int, int>, int> *sparsed, int n) {
	int **newArr = declArr(n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			//���������� �������� � ������������ i � j � ����������
			auto temp = sparsed->find(make_pair(i, j));
			if (temp != sparsed->end()) {
				//���� ��� ������ ������� � ���������� �� ���������� 
				//�� ��� ����� � ������� �������� ����� ��������
				newArr[i][j] = temp->second;
			}
			else {
				//���� �� ���� ������� ������ ��������
				newArr[i][j] = 0;
			}
		}
	}

	//������� ������ �� ����� �������
	return newArr;
}

//����� ����������� �������
void output(map<pair<int, int>, int> *sparsed) {
	//����� ������ ������
	cout << "Rows: ";
	for (auto &item : *sparsed) {
		cout << setw(2) << item.first.first;
	}
	cout << endl;

	//����� ������ �������
	cout << "Cols: ";
	for (auto &item : *sparsed) {
		cout << setw(2) << item.first.second;
	}
	cout << endl;

	//����� �������� �� �����������
	cout << "Vals: ";
	for (auto &item : *sparsed) {
		cout << setw(2) << item.second;
	}
	cout << endl;
}

//���������� ����������� �������
//O(1) -> O(n^3)
void sortDictionary(map<pair<int, int>, int> *sparsed, int maxSize) {
	//�������� �� �������� ��� �������� �� ������� �������� �� ����� ������ ������
	int tempJ = maxSize - 1;

	//�������� �� �������� ������ ������� � �����
	for (int row = maxSize - 1; row >= 0; row -= 2) {
		//�������� �� ��. ���������� � ������� ����� ������ ������ ������� � �����
		for (auto iItem = sparsed->rbegin(); iItem != sparsed->rend(); iItem++) {
			if (iItem->first.first != row) continue;

			//�������� �� ��. ���������� ������� �� ������� � ������ ����� ������ ������ ������� � �����
			for (auto jItem = next(iItem); jItem != sparsed->rend(); jItem++) {
				if (jItem->first.first != row) continue;

				//����� ���������� ���� ����������� ������� ����������
				if (iItem->second > jItem->second) {
					auto &t1 = iItem->second;
					auto &t2 = jItem->second;
					swap(t1, t2);
				}
			}

			//���������� ������ ������� � ���������������� ��������
			//����� �������� �� ���������� � ������� ������ (������ ��������������� ��.)
			auto nodeHandler = sparsed->extract(iItem->first); 
			//���������� ������ ������� � ���������� ��. ����������
			nodeHandler.key().second = tempJ; 
			//�������� ������� ���������� ��. ����������
			sparsed->insert(move(nodeHandler)); 
			//������� ��������� �� ���������� ��. ���������� � ���������� �������� ������ �������
			iItem = (map<pair<int, int>, int>::reverse_iterator) sparsed->upper_bound(make_pair(row, tempJ--)); 
		}
		//���������� ��������� ��� ������ ������
		tempJ = maxSize - 1;
	}
}