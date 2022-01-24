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

	int **arr; //Указатель на начальную матрицу
	int size; //Размер начальной матрицы

	map<pair<int, int>, int> sparseArr; //Контейнер для упакованой матрицы

	//Ввод размера начальной матрицы
	cout << "Enter size of matrix: ";
	do {
		cin >> size;
		if (size <= 0) {
			cout << "Try again: ";
		}
	} while (size <= 0);

	arr = declArr(size); //Выделение памяти под указатель
	initArr(arr, size); //Инициализация значениями начальной матрицы
	cout << "Started matrix:" << endl;
	output(arr, size); //Вывод начальной матрицы

	toDictionary(&sparseArr, arr, size); //Перевод начальной матрицы в упакованное состояние
	cout << "Sparsed matrix:" << endl;
	output(&sparseArr); //Вывод упакованной матрицы

	sortDictionary(&sparseArr, size); //Сортировка контейнера по заданию
	cout << "Sorted sparsed matrix:" << endl;
	output(&sparseArr); //Вывод отсортированого контейнера

	delArr(arr, size); //Освобождение памяти под новую матрицу
	arr = toArr(&sparseArr, size); //Перевод контейнера к матричному виду
	cout << "Sorted matrix:" << endl;
	output(arr, size); //Вывод новой отсортированной матрицы

	delArr(arr, size); //Освобождение памяти

	system("pause");
	return 0;
}

//Выделение памяти под матрицу
int **declArr(int n) {
	int **arr = new int *[n];
	for (int i = 0; i < n; i++) {
		*(arr + i) = new int[n];
	}
	return arr;
}

//Освобождение памяти
void delArr(int **arr, int n) {
	for (int i = 0; i < n; i++) {
		delete[] arr[i];
	}
	delete[] arr;
}

//Инициализация матрицы значениями
void initArr(int **arr, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			//40% элементов матрицы будут нулями
			*(*(arr + i) + j) = (rand() % 10) <= 3 ? 0 : (rand() % 9 + 1);
		}
	}
}

//Вывод матрицы
void output(int **arr, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << setw(3) << *(*(arr + i) + j);
		}
		cout << endl;
	}
}

//Перевод матрицы в упакованный вид
void toDictionary(map<pair<int, int>, int> *sparsed, int **arr, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (arr[i][j] != 0) {
				(*sparsed)[make_pair(i, j)] = arr[i][j];
			}
		}
	}
}

//Перевод упакованной матрицы в обычный вид
int **toArr(map<pair<int, int>, int> *sparsed, int n) {
	int **newArr = declArr(n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			//Нахождение элемента с координатами i и j в контейнере
			auto temp = sparsed->find(make_pair(i, j));
			if (temp != sparsed->end()) {
				//Если был найден элемент в контейнере то записываем 
				//на его место в матрице значение этого элемента
				newArr[i][j] = temp->second;
			}
			else {
				//Если не было найдено такого элемента
				newArr[i][j] = 0;
			}
		}
	}

	//Возврат адреса на новую матрицу
	return newArr;
}

//Вывод упакованной матрицы
void output(map<pair<int, int>, int> *sparsed) {
	//Вывод номера строки
	cout << "Rows: ";
	for (auto &item : *sparsed) {
		cout << setw(2) << item.first.first;
	}
	cout << endl;

	//Вывод номера столбца
	cout << "Cols: ";
	for (auto &item : *sparsed) {
		cout << setw(2) << item.first.second;
	}
	cout << endl;

	//Вывод значения по координатам
	cout << "Vals: ";
	for (auto &item : *sparsed) {
		cout << setw(2) << item.second;
	}
	cout << endl;
}

//Сортировка упакованной матрицы
//O(1) -> O(n^3)
void sortDictionary(map<pair<int, int>, int> *sparsed, int maxSize) {
	//Итератор по столбцам для перевода не нулевых значений на начало каждой строки
	int tempJ = 0; 

	//Итерация по индексам строки 
	for (int row = 1; row < maxSize; row += 2) {
		//Итерация по эл. контейнера у которых номер строки непарный
		for (auto iItem = sparsed->begin(); iItem != sparsed->end(); iItem++) {
			if (iItem->first.first != row) continue;

			//Итерация по эл. контейнера начиная со второго у котрых номер строки непарный
			for (auto jItem = next(iItem); jItem != sparsed->end(); jItem++) {
				if (jItem->first.first != row) continue;

				//Обмен значениями если справедливо условие сортировки
				if (iItem->second < jItem->second) {
					auto &t1 = iItem->second;
					auto &t2 = jItem->second;
					swap(t1, t2);
				}
			}

			//Обновление номера столбца у отсортированного элемента
			auto nodeHandler = sparsed->extract(iItem->first); //Вывод элемента из контейнера с заданым ключем (ключем отсортированого эл.)
			nodeHandler.key().second = tempJ; //Обновление номера столбца у вытянутого эл. контейнера
			sparsed->insert(move(nodeHandler)); //Обратная вставка изминённого эл. контейнера
			iItem = sparsed->find(make_pair(row, tempJ++)); //Возврат итератора на измененный эл. контейнера и увеличение счетчика номера столбца
		}
		//Обновление итератора для каждой строки
		tempJ = 0;
	}
}