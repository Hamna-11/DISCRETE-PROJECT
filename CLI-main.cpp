#include <iostream>
#include "CLIInterface.h"
#include "CourseManager.h"
#include "PeopleManager.h"
#include "Relations.h"
#include "CustomMap.h"
#include "DisplayHelper.h"

using namespace std;

int main() {
    DisplayHelper::printHeader("MODULE 11: CLI INTERFACE");

    CourseManager cm;
    PeopleManager pm;
    Relations rel;
    CustomMap<int, int> courseToFaculty;
    CustomMap<int, int> courseToRoom;

    CLIInterface cli(cm, pm, rel, courseToFaculty, courseToRoom);

    cli.showWelcome();

    while (true) {
        cout << "\n=== CLI FEATURES MENU ===\n";
        cout << "1. Display System Statistics\n";
        cout << "2. Quick Setup (Sample Data)\n";
        cout << "3. Export Data to File\n";
        cout << "4. Show Help & Documentation\n";
        cout << "0. Exit\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;

        if (choice == 0) break;

        switch (choice) {
        case 1:
            cli.displayStatistics();
            break;

        case 2:
            cli.quickSetup();
            break;

        case 3: {
            string filename;
            cout << "Enter filename: ";
            cin >> filename;
            cli.exportData(filename);
            break;
        }

        case 4:
            cli.showHelp();
            break;

        default:
            DisplayHelper::printError("Invalid choice!");
        }
    }

    return 0;
}