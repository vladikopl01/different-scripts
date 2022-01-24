#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

std::vector<std::string> FindNamesHistory(const std::map<int, std::string> &names_by_year, int year) {
    std::vector<std::string> names;

    for (const auto &item : names_by_year) {
        if (item.first <= year && (names.empty() || names.back() != item.second)) {
            names.push_back(item.second);
        }
    }

    return names;
}

std::string BuildJoinedName(std::vector<std::string> names) {
    std::reverse(names.begin(), names.end());

    std::string joined_name = names[0];

    for (int i = 1; i < names.size(); i++) {
        if (i == 1) {
            joined_name += " (";
        }
        else {
            joined_name += ", ";
        }

        joined_name += names[i];
    }

    if (names.size() > 1) {
        joined_name += ")";
    }

    return joined_name;
}

class Person {
private:
    std::map<int, std::string> first_names;
    std::map<int, std::string> last_names;
    int birth;

    std::vector<std::string> FindFirstNamesHistory(int year) const {
        return FindNamesHistory(first_names, year);
    }

    std::vector<std::string> FindLastNamesHistory(int year) const {
        return FindNamesHistory(last_names, year);
    }

public:
    Person(const std::string &f_name, const std::string &l_name, int year) {
        first_names[year] = f_name;
        last_names[year] = l_name;

        birth = year;
    }

    void ChangeFirstName(int year, const std::string &first_name) {
        if (birth <= year) first_names[year] = first_name;
    }

    void ChangeLastName(int year, const std::string &last_name) {
        if (birth <= year) last_names[year] = last_name;
    }

    std::string GetFullName(int year) const {
        if (year < birth) return "No person";

        const std::vector<std::string> first_names_history = FindFirstNamesHistory(year);
        const std::vector<std::string> last_names_history = FindLastNamesHistory(year);

        return first_names_history.back() + " " + last_names_history.back();
    }

    std::string GetFullNameWithHistory(int year) const {
        if (year < birth)return "No person";

        const std::string first_name = BuildJoinedName(FindFirstNamesHistory(year));
        const std::string last_name = BuildJoinedName(FindLastNamesHistory(year));

        return first_name + " " + last_name;
    }
};

int main() {
    
    return 0;
}



