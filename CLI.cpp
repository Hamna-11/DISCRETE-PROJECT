#include "CLIInterface.h"
#include "DisplayHelper.h"
#include <iostream>
#include <fstream>

using namespace std;

CLIInterface::CLIInterface(CourseManager& c, PeopleManager& p, Relations& r,
    CustomMap<int, int>& cf, CustomMap<int, int>& cr)
    : cm(c), pm(p), rel(r), courseToFaculty(cf), courseToRoom(cr) {
}

void CLIInterface::showWelcome() {
    DisplayHelper::printHeader("FAST UNIVERSITY MANAGEMENT SYSTEM");
    cout << "\n  Welcome to the Advanced University Management System\n";
    cout << "  Powered by Discrete Mathematics Concepts\n";
    cout << "\n  Available Modules:\n";
    cout << "  - Functions & Mappings\n";
    cout << "  - Automated Proof Generation\n";
    cout << "  - Consistency Checking\n";
    cout << "  - Performance Benchmarking\n";
    cout << "  - Comprehensive Unit Testing\n\n";
}

void CLIInterface::displayStatistics() {
    DisplayHelper::printHeader("SYSTEM STATISTICS");

    cout << "\nCurrent System Status:\n";
    cout << "  Total Courses:  " << cm.count() << "\n";
    cout << "  Total Students: " << pm.getStudentCount() << "\n";
    cout << "  Total Faculty:  " << pm.getFacultyCount() << "\n";
    cout << "  Total Rooms:    " << pm.getRoomCount() << "\n";

    int totalPrereqs = 0;
    for (int i = 0; i < rel.getSize(); i++) {
        for (int j = 0; j < rel.getSize(); j++) {
            if (rel.getPrereq(i, j)) totalPrereqs++;
        }
    }
    cout << "  Prerequisites:  " << totalPrereqs << "\n";

    cout << "\nAssignments:\n";
    cout << "  Course-Faculty: " << courseToFaculty.size() << " mappings\n";
    cout << "  Course-Room:    " << courseToRoom.size() << " mappings\n";

    int totalEnrollments = 0;
    for (int i = 0; i < pm.getStudentCount(); i++) {
        auto* s = pm.getStudent(i);
        if (s) totalEnrollments += s->enrolled.size();
    }
    cout << "  Enrollments:    " << totalEnrollments << " total\n";
    cout << "\n";
}

void CLIInterface::quickSetup() {
    DisplayHelper::printHeader("QUICK SETUP WIZARD");

    cout << "\nThis will create sample data for testing.\n";
    cout << "Continue? (y/n): ";
    char confirm;
    cin >> confirm;

    if (confirm != 'y' && confirm != 'Y') return;

    cout << "\nCreating sample courses...\n";
    cm.addCourse("CS101", "Programming", 3);
    cm.addCourse("CS102", "DataStructures", 4);
    cm.addCourse("CS201", "Algorithms", 4);
    cm.addCourse("MATH101", "Calculus", 3);

    rel.ensureSize(4);
    rel.addPrereq(0, 1);
    rel.addPrereq(1, 2);

    cout << "Creating sample students...\n";
    pm.addStudent("Noor");
    pm.addStudent("Khadija");
    pm.addStudent("Nimra");

    cout << "Creating sample faculty...\n";
    pm.addFaculty("Sir Raza");
    pm.addFaculty("Sir Qamar");

    cout << "Creating sample rooms...\n";
    pm.addRoom("R101", 50);
    pm.addRoom("R102", 40);

    cout << "Assigning faculty and rooms...\n";
    courseToFaculty.insert(0, 0);
    courseToFaculty.insert(1, 0);
    courseToFaculty.insert(2, 1);
    courseToFaculty.insert(3, 1);

    courseToRoom.insert(0, 0);
    courseToRoom.insert(1, 0);
    courseToRoom.insert(2, 1);
    courseToRoom.insert(3, 1);

    cout << "Enrolling students...\n";
    auto* s1 = pm.getStudent(0);
    if (s1) {
        s1->enrolled.push_back(0);
        s1->enrolled.push_back(3);
    }

    auto* s2 = pm.getStudent(1);
    if (s2) {
        s2->enrolled.push_back(0);
        s2->enrolled.push_back(1);
    }

    DisplayHelper::printSuccess("Quick setup completed!");
    displayStatistics();
}

void CLIInterface::exportData(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        DisplayHelper::printError("Could not open file for writing");
        return;
    }

    file << "FAST UNIVERSITY DATA EXPORT\n";
    file << "===========================\n\n";

    file << "COURSES:\n";
    for (int i = 0; i < cm.count(); i++) {
        auto* c = cm.getCourse(i);
        if (c) {
            file << c->id << "," << c->code << "," << c->name << "," << c->credits << "\n";
        }
    }

    file << "\nSTUDENTS:\n";
    for (int i = 0; i < pm.getStudentCount(); i++) {
        auto* s = pm.getStudent(i);
        if (s) {
            file << s->id << "," << s->name << ",";
            for (size_t j = 0; j < s->enrolled.size(); j++) {
                file << s->enrolled[j];
                if (j < s->enrolled.size() - 1) file << ";";
            }
            file << "\n";
        }
    }

    file.close();
    DisplayHelper::printSuccess("Data exported to " + filename);
}

void CLIInterface::showHelp() {
    DisplayHelper::printHeader("HELP & DOCUMENTATION");

    cout << "\nMODULE 7 - Functions:\n";
    cout << "  Tests function properties (injective, surjective, bijective)\n";
    cout << "  Example: Course->Faculty mapping analysis\n";

    cout << "\nMODULE 8 - Automated Proofs:\n";
    cout << "  Generates formal mathematical proofs\n";
    cout << "  Example: Prerequisite verification using induction\n";

    cout << "\nMODULE 9 - Consistency Checker:\n";
    cout << "  Detects system-wide conflicts and violations\n";
    cout << "  Checks: cycles, prerequisites, capacity, assignments\n";

    cout << "\nMODULE 10 - Performance:\n";
    cout << "  Benchmarks algorithm efficiency\n";
    cout << "  Tests: transitive closure, function checks, etc.\n";

    cout << "\nMODULE 11 - CLI (Current):\n";
    cout << "  Text-based interactive interface\n";
    cout << "  Features: quick setup, export, statistics\n";

    cout << "\nMODULE 12 - Unit Testing:\n";
    cout << "  Comprehensive automated test suite\n";
    cout << "  Validates all discrete structure operations\n\n";
}