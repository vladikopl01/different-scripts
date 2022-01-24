#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

struct Specialization {
    std::string value;

    explicit Specialization(std::string v) {
        value = v;
    }
};

struct Course {
    std::string value;

    explicit Course(std::string v) {
        value = v;
    }
};

struct Week {
    std::string value;

    explicit Week(std::string v) {
        value = v;
    }
};

struct LectureTitle {
    std::string specialization;
    std::string course;
    std::string week;

    LectureTitle(const Specialization &new_spec, 
        const Course &new_course, 
        const Week &new_week) {
        specialization = new_spec.value;
        course = new_course.value;
        week = new_week.value;
    }
};

int main() {
    LectureTitle title(
        Specialization("C++"),
        Course("White belt"),
        Week("4th")
    );

    return 0;
}



