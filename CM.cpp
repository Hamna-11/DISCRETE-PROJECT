#include "CourseManager.h"
#include "DisplayHelper.h"
#include <iostream>
#include <iomanip>

using namespace std;

CourseManager::Course::Course() : id(-1), credits(0) {}

CourseManager::Course::Course(int i, string c, string n, int cr)
    : id(i), code(c), name(n), credits(cr) {
}

int CourseManager::addCourse(const string& code, const string& name, int credits) {
    int id = courses.size();
    courses.push_back(Course(id, code, name, credits));
    DisplayHelper::printSuccess("Added course: " + code);
    return id;
}

const CourseManager::Course* CourseManager::getCourse(int id) const {
    if (id < 0 || id >= (int)courses.size()) return nullptr;
    return &courses[id];
}

int CourseManager::count() const {
    return courses.size();
}

void CourseManager::listAll() const {
    DisplayHelper::printHeader("ALL COURSES");
    cout << "\n" << left << setw(5) << "ID" << setw(12) << "Code"
        << setw(25) << "Name" << "Credits\n";
    cout << string(60, '-') << "\n";

    for (const auto& c : courses) {
        cout << left << setw(5) << c.id << setw(12) << c.code
            << setw(25) << c.name << c.credits << "\n";
    }
    cout << "\nTotal Courses: " << courses.size() << "\n";
}