#include <iostream>
#include "ConsistencyChecker.h"
#include "CourseManager.h"
#include "PeopleManager.h"
#include "Relations.h"
#include "CustomMap.h"
#include "DisplayHelper.h"

using namespace std;

int main() {
    DisplayHelper::printHeader("MODULE 9: CONSISTENCY CHECKER");

    CourseManager cm;
    PeopleManager pm;
    Relations rel;
    CustomMap<int, int> courseToFaculty;
    CustomMap<int, int> courseToRoom;

    cm.addCourse("CS101", "Programming", 3);
    cm.addCourse("CS102", "DataStructures", 4);
    cm.addCourse("CS201", "Algorithms", 4);

    pm.addStudent("Noor");
    pm.addStudent("Khadija");
    pm.addFaculty("Sir Raza");
    pm.addRoom("R101", 30);

    rel.ensureSize(3);
    rel.addPrereq(0, 1);
    rel.addPrereq(1, 2);

    courseToFaculty.insert(0, 0);
    courseToFaculty.insert(1, 0);
    courseToRoom.insert(0, 0);

    auto* noor = pm.getStudent(0);
    if (noor) {
        noor->enrolled.push_back(1);
        noor->enrolled.push_back(2);
    }

    ConsistencyChecker checker(cm, pm, rel, courseToFaculty, courseToRoom);

    cout << "\nRunning consistency checks...\n";
    checker.runAllChecks();
    checker.displayReport();

    return 0;
}