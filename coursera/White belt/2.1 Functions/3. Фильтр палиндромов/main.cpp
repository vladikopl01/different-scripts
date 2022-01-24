#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> PalindromFilter(std::vector<std::string> words, int minLength) {
	std::vector<std::string> result;
	bool isPalindrom;

	for (auto word : words) {
		isPalindrom = true;
		for (int i = 0; i <= word.size() / 2 && isPalindrom; i++) {
			if (word[i] != word[word.size() - i - 1]) {
				isPalindrom = false;
			}
		}

		if (isPalindrom && word.size() >= minLength)
			result.push_back(word);
	}
	
	return result;
}


int main() {
	std::vector<std::string> filter = PalindromFilter({ "aba", "abb", "caac", "cac", "aa" }, 3);

	for (auto w : filter) {
		std::cout << w << " ";
	}

	return 0;
}