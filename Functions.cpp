#include <iostream>
#include "Functions.h"
#include "CourseManager.h"
#include "PeopleManager.h"
#include "CustomMap.h"
#include "DisplayHelper.h"

using namespace std;

int main() {
    DisplayHelper::printHeader("MODULE 7: FUNCTION PROPERTIES");

    CourseManager cm;
    PeopleManager pm;
    CustomMap<int, int> courseToFaculty;

    cm.addCourse("CS101", "Programming", 3);
    cm.addCourse("CS102", "DataStructures", 4);
    cm.addCourse("CS201", "Algorithms", 4);
    cm.addCourse("MATH101", "Calculus", 3);

    pm.addFaculty("Sir Raza");
    pm.addFaculty("Sir Qamar");
    pm.addFaculty("Sir Fayyaz");

    courseToFaculty.insert(0, 0);
    courseToFaculty.insert(1, 0);
    courseToFaculty.insert(2, 1);
    courseToFaculty.insert(3, 2);

    Functions::display(courseToFaculty, cm, pm);

    cout << "\nTesting Function Composition:\n";
    CustomMap<int, int> facultyToRoom;
    facultyToRoom.insert(0, 10);
    facultyToRoom.insert(1, 20);
    facultyToRoom.insert(2, 30);

    auto composed = Functions::compose(courseToFaculty, facultyToRoom);
    cout << "Course -> Room (composed):\n";
    for (const auto& pair : composed) {
        const auto* c = cm.getCourse(pair.first);
        cout << "  " << (c ? c->code : to_string(pair.first))
            << " -> Room " << pair.second << "\n";
    }

    return 0;
}