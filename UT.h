#ifndef UNITTESTING_H
#define UNITTESTING_H

#include <string>

class UnitTesting {
private:
    int passed;
    int failed;

    void assertTrue(bool condition, const std::string& testName);
    void assertEqual(int a, int b, const std::string& testName);

public:
    UnitTesting() : passed(0), failed(0) {}

    void testFunctions();
    void testProofGenerator();
    void testConsistencyChecker();
    void testPerformanceBenchmark();
    void testRelations();
    void runAllTests();
};

#endif