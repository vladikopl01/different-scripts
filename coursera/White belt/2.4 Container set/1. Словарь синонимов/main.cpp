#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>

int main() {
    std::map<std::string, std::set<std::string>> words;

    int num;
    std::cin >> num;

    for (int i = 0; i < num; i++) {
        std::string command;
        std::cin >> command;

        if (command == "ADD") {
            std::string word1, word2;
            std::cin >> word1 >> word2;

            words[word1].insert(word2);
            words[word2].insert(word1);
        }

        if (command == "COUNT") {
            std::string word;
            std::cin >> word;

            std::cout << words[word].size() << '\n';
        }

        if (command == "CHECK") {
            std::string word1, word2;
            std::cin >> word1 >> word2;

            if (words[word1].count(word2)) {
                std::cout << "YES\n";
            }
            else {
                std::cout << "NO\n";
            }
        }
    }

    return 0;
}



