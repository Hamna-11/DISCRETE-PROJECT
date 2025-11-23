#include <iostream>
#include "UnitTesting.h"
#include "DisplayHelper.h"

using namespace std;

int main() {
    DisplayHelper::printHeader("MODULE 12: UNIT TESTING SUITE");

    cout << "\nRunning comprehensive unit tests...\n";
    cout << "This will test all modules (7-12)\n\n";

    UnitTesting tester;
    tester.runAllTests();

    cout << "\nTesting completed!\n";

    return 0;
}