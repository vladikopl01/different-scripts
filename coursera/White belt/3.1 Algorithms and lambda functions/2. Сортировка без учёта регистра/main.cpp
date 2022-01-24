#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
	int num;
	std::cin >> num;

	std::vector<std::string> v(num);

	for (auto &item : v) {
		std::cin >> item;
	}
	
	std::sort(v.begin(), v.end(),
		[](const std::string &l, const std::string &r) {
			return std::lexicographical_compare(
				l.begin(), l.end(),
				r.begin(), r.end(),
				[](char cl, char cr) {
					return std::tolower(cl) < std::tolower(cr);
				}
			);
		}
	);

	for (const auto &item : v) {
		std::cout << item << " ";
	}
	std::cout << '\n';

    return 0;
}



