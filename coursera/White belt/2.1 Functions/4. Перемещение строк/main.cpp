#include <iostream>
#include <string>
#include <vector>

void MoveStrings(std::vector<std::string>& source, std::vector<std::string>& destination){
	for (auto w : source) {
		destination.push_back(w);
	}
	source.clear();
}


int main() {
	std::vector<std::string> source = { "a", "b", "c" };
	std::vector<std::string> destination = { "z" };
	MoveStrings(source, destination);

	for (auto w : destination) {
		std::cout << w << " ";
	}

	return 0;
}