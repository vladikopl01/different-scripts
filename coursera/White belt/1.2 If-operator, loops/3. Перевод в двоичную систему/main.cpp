#include <iostream>
#include <string>
#include <vector>

int main() {
    int a;
    std::cin >> a;

    std::vector<int> result;

    do {
        result.push_back(a % 2);
        a /= 2;
    } while (a != 0);

    for (auto i = result.rbegin(); i != result.rend(); ++i) {
        std::cout << *i;
    }
        
    system("pause");
    return 0;
}