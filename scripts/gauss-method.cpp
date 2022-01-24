#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

void inputA(double**, int);
void inputB(double*, int);

void randAB(double**, double*, int);

void outputAB(double**, double*, int);
void outputX(double*, int);

void gauss(double**, double*, double*, int);

int main() {
	//srand(time(0));

	int size;

	cout << "Enter number of equations: ";
	do {
		cin >> size;
		if (size <= 0) {
			cout << "Error!! Try again: ";
		}
	} while (size <= 0);

	double **a = new double*[size];
	for (int i = 0; i < size; i++) {
		a[i] = new double[size];
	}
	double *b = new double[size];
	double *x = new double[size];

	inputA(a, size);
	inputB(b, size);
	//randAB(a, b, size);

	system("cls");
	cout << "Your input: " << endl;
	outputAB(a, b, size);

	gauss(a, b, x, size);
	cout << "Result: " << endl;
	outputAB(a, b, size);
	outputX(x, size);

	system("pause");
	return 0;
}

void inputA(double **a, int n) {
	cout << "Enter equation coefficients: " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << setw(6) << "a" << i + 1 << " = ";
			cin >> a[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void inputB(double *b, int n) {
	cout << "Enter free member column: " << endl;
	for (int i = 0; i < n; i++) {
		cout <<setw(6) << "b" << i + 1 << " = ";
		cin >> b[i];
	}
	cout << endl;
}

void randAB(double **a, double *b, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			a[i][j] = rand() % 10;
		}
		b[i] = rand() % 10;
	}
}

void outputAB(double **a, double *b, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << setw(6) << setprecision(4) << a[i][j];
		}
		cout << "|" << setw(6) << setprecision(4) << b[i] << endl;
	}
	cout << endl;
}

void outputX(double *x, int n) {
	cout << "Answer: " << endl;
	for (int i = 0; i < n; i++) {
		cout << "x[" << i + 1 << "] = " << setw(6) << setprecision(4) << x[i] << endl;
	}
	cout << endl;
}

void gauss(double **a, double *b, double *x, int n) {
	double R;
	double s;

	double max;
	int row;
	double temp;

	for (int k = 0; k < n; k++) {
		max = a[k][k];
		row = k;

		for (int i = k + 1; i < n; i++) {
			if (a[i][k] > max) {
				max = a[i][k];
				row = i;
			}
		}

		for (int j = 0; j < n; j++) {
			temp = a[row][j];
			a[row][j] = a[k][j];
			a[k][j] = temp;
		}
		temp = b[row];
		b[row] = b[k];
		b[k] = temp;

		for (int i = k + 1; i < n; i++) {
			if (fabs(a[k][k]) < 0.0000001 || i == k) continue;
			R = a[i][k] / a[k][k];

			for (int j = k; j < n; j++) {
				a[i][j] = (a[i][j] - a[k][j] * R);
			}
			b[i] = b[i] - b[k] * R;
		}
	}

	for (int i = 0; i < n; i++) {
		x[i] = 0;
	}
	for (int i = n - 1; i >= 0; i--) {
		s = b[i];
		for (int j = n - 1; j > i; j--) {
			s -= x[j] * a[i][j];
		}
		x[i] = s / a[i][i];
	}

}