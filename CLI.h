#ifndef CLIINTERFACE_H
#define CLIINTERFACE_H

#include <string>
#include "CourseManager.h"
#include "PeopleManager.h"
#include "Relations.h"
#include "CustomMap.h"

class CLIInterface {
private:
    CourseManager& cm;
    PeopleManager& pm;
    Relations& rel;
    CustomMap<int, int>& courseToFaculty;
    CustomMap<int, int>& courseToRoom;

public:
    CLIInterface(CourseManager& c, PeopleManager& p, Relations& r,
        CustomMap<int, int>& cf, CustomMap<int, int>& cr);

    void showWelcome();
    void displayStatistics();
    void quickSetup();
    void exportData(const std::string& filename);
    void showHelp();
};

#endif