#pragma once
#ifndef CONSISTENCYCHECKER_H
#define CONSISTENCYCHECKER_H

#include <string>
#include <vector>
#include "CourseManager.h"
#include "PeopleManager.h"
#include "Relations.h"
#include "CustomMap.h"

class ConsistencyChecker {
private:
    const CourseManager& cm;
    PeopleManager& pm;
    const Relations& rel;
    CustomMap<int, int>& courseToFaculty;
    CustomMap<int, int>& courseToRoom;

    std::vector<std::string> errors;
    std::vector<std::string> warnings;

public:
    ConsistencyChecker(const CourseManager& c, PeopleManager& p,
        const Relations& r, CustomMap<int, int>& cf, CustomMap<int, int>& cr);

    void runAllChecks();
    void checkPrereqCycles();
    void checkStudentPrereqs();
    void checkStudentOverload();
    void checkFacultyConflicts();
    void checkRoomCapacity();
    void checkUnassignedCourses();
    void displayReport() const;
};

#endif