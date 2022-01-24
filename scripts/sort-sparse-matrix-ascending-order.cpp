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
	//Итератор по столбцам для перевода не нулевых значений на конец каждой строки
	int tempJ = maxSize - 1;

	//Итерация по индексам строки начиная с конца
	for (int row = maxSize - 1; row >= 0; row -= 2) {
		//Итерация по эл. контейнера у которых номер строки парный начиная с конца
		for (auto iItem = sparsed->rbegin(); iItem != sparsed->rend(); iItem++) {
			if (iItem->first.first != row) continue;

			//Итерация по эл. контейнера начиная со второго у котрых номер строки парный начиная с конца
			for (auto jItem = next(iItem); jItem != sparsed->rend(); jItem++) {
				if (jItem->first.first != row) continue;

				//Обмен значениями если справедливо условие сортировки
				if (iItem->second > jItem->second) {
					auto &t1 = iItem->second;
					auto &t2 = jItem->second;
					swap(t1, t2);
				}
			}

			//Обновление номера столбца у отсортированного элемента
			//Вывод элемента из контейнера с заданым ключем (ключем отсортированого эл.)
			auto nodeHandler = sparsed->extract(iItem->first); 
			//Обновление номера столбца у вытянутого эл. контейнера
			nodeHandler.key().second = tempJ; 
			//Обратная вставка изминённого эл. контейнера
			sparsed->insert(move(nodeHandler)); 
			//Возврат итератора на измененный эл. контейнера и уменьшение счетчика номера столбца
			iItem = (map<pair<int, int>, int>::reverse_iterator) sparsed->upper_bound(make_pair(row, tempJ--)); 
		}
		//Обновление итератора для каждой строки
		tempJ = maxSize - 1;
	}
}