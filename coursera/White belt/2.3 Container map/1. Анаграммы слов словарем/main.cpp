#include <iostream>
#include <vector>
#include <string>
#include <map>

std::map<char, int> countChars(const std::string& str) {
	std::map<char, int> m;
	for (char c : str) {
		m[c]++;
	}
	return m;
}

int main() {
	std::string first, second;

	int num;
	std::cin >> num;

	for (int i = 0; i < num; i++) {
		std::cin >> first >> second;

		if (countChars(first) == countChars(second)) {
			std::cout << "YES" << '\n';
		}
		else {
			std::cout << "NO" << '\n';
		}
	}

	return 0;
}