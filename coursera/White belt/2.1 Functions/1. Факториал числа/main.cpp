#include <iostream>

int Factorial(int num) {
	if (num <= 1) return 1;
	return num * Factorial(num - 1);
}


int main() {
	int n;
	std::cin >> n;
	std::cout << Factorial(n);

	return 0;
}