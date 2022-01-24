#include <iostream>
#include <string>
#include <vector>

void Reverse(std::vector<int>& nums) {
	int tmp;
	for (int i = 0; i < nums.size() / 2; i++) {
		tmp = nums[i];
		nums[i] = nums[nums.size() - i - 1];
		nums[nums.size() - i - 1] = tmp;
	}
}


int main() {
	std::vector<int> numbers = { 1, 5, 3, 4, 2 };
	Reverse(numbers);

	for (auto num : numbers) {
		std::cout << num << " ";
	}

	return 0;
}