#include <iostream>
#include <string>

int main() {
    std::string s;
    std::cin >> s;

    char c = 'f';
    int count = 0;

    for (int i = 0; i < s.size(); i++) {
        if (s[i] == c) count++;
        if (count == 2) {
            std::cout << i;
            break;
        }
    }

    if (count == 1) std::cout << -1;
    if (count == 0) std::cout << -2;

    //system("pause");
    return 0;
}