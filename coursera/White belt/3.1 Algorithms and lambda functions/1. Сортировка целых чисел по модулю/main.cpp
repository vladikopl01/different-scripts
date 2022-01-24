#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
	int num;
	std::cin >> num;

	std::vector<int> v(num);

	for (auto &item : v) {
		std::cin >> item;
	}

	std::sort(v.begin(), v.end(),
		[](int i, int j) {
			return abs(i) < abs(j); 
		}
	);

	for (const auto &item : v) {
		std::cout << item << " ";
	}
	std::cout << '\n';

    return 0;
}



