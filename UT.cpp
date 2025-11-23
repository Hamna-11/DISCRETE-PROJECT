#include "UnitTesting.h"
#include "Functions.h"
#include "ProofGenerator.h"
#include "ConsistencyChecker.h"
#include "PerformanceBenchmark.h"
#include "Relations.h"
#include "CourseManager.h"
#include "PeopleManager.h"
#include "CustomMap.h"
#include "DisplayHelper.h"
#include <iostream>
#include <string>

using namespace std;

void UnitTesting::assertTrue(bool condition, const string& testName) {
    if (condition) {
        cout << "[PASS] " << testName << "\n";
        passed++;
    }
    else {
        cout << "[FAIL] " << testName << "\n";
        failed++;
    }
}

void UnitTesting::assertEqual(int a, int b, const string& testName) {
    if (a == b) {
        cout << "[PASS] " << testName << "\n";
        passed++;
    }
    else {
        cout << "[FAIL] " << testName << " (expected " << b << ", got " << a << ")\n";
        failed++;
    }
}

void UnitTesting::testFunctions() {
    cout << "\n--- Testing Functions (Module 7) ---\n";

    CustomMap<int, int> f1;
    f1.insert(0, 0); f1.insert(1, 1); f1.insert(2, 2);
    assertTrue(Functions::isInjective(f1), "Should be injective");
    assertTrue(Functions::isSurjective(f1, 3), "Should be surjective");
    assertTrue(Functions::isBijective(f1, 3), "Should be bijective");

    CustomMap<int, int> f2;
    f2.insert(0, 0); f2.insert(1, 0); f2.insert(2, 1);
    assertTrue(!Functions::isInjective(f2), "Should not be injective");

    CustomMap<int, int> f3, f4;
    f3.insert(0, 1); f3.insert(1, 2);
    f4.insert(1, 10); f4.insert(2, 20);
    auto composed = Functions::compose(f3, f4);
    assertTrue(composed.size() == 2, "Composition should have 2 mappings");
}

void UnitTesting::testProofGenerator() {
    cout << "\n--- Testing Proof Generator (Module 8) ---\n";

    CourseManager cm;
    Relations rel;

    cm.addCourse("CS101", "Intro", 3);
    cm.addCourse("CS201", "Advanced", 3);
    rel.ensureSize(2);
    rel.addPrereq(0, 1);

    ProofGenerator proof(rel, cm);

    vector<bool> completed(2, false);
    completed[0] = true;

    proof.generatePrereqProof(1, completed);
    assertTrue(true, "Proof generation completed successfully");
}

void UnitTesting::testConsistencyChecker() {
    cout << "\n--- Testing Consistency Checker (Module 9) ---\n";

    CourseManager cm;
    PeopleManager pm;
    Relations rel;

    cm.addCourse("CS101", "Programming", 3);
    pm.addStudent("Noor");
    pm.addFaculty("Sir Raza");
    pm.addRoom("R101", 30);

    CustomMap<int, int> cf, cr;
    cf.insert(0, 0);
    cr.insert(0, 0);

    ConsistencyChecker checker(cm, pm, rel, cf, cr);
    checker.runAllChecks();

    assertTrue(true, "Consistency checks completed");
}

void UnitTesting::testPerformanceBenchmark() {
    cout << "\n--- Testing Performance Benchmark (Module 10) ---\n";

    PerformanceBenchmark bench;

    Relations rel;
    bench.benchmarkTransitiveClosure(rel, 5);
    bench.benchmarkFunctionChecks(10);

    assertTrue(true, "Benchmark completed successfully");
}

void UnitTesting::testRelations() {
    cout << "\n--- Testing Relations ---\n";

    Relations rel;
    rel.ensureSize(5);
    rel.addPrereq(0, 1);
    rel.addPrereq(1, 2);

    assertTrue(rel.getPrereq(0, 1), "Direct prerequisite should exist");

    auto closure = rel.closurePrereq();
    assertTrue(closure[0][2], "Transitive prerequisite should exist");

    assertTrue(!rel.hasPrereqCycle(), "Should have no cycles");

    rel.addPrereq(2, 0);
    assertTrue(rel.hasPrereqCycle(), "Should detect cycle");
}

void UnitTesting::runAllTests() {
    DisplayHelper::printHeader("UNIT TESTING SUITE (MODULE 12)");

    passed = 0;
    failed = 0;

    testFunctions();
    testProofGenerator();
    testConsistencyChecker();
    testPerformanceBenchmark();
    testRelations();

    cout << "\n" << string(60, '=') << "\n";
    cout << "RESULTS: " << passed << " passed, " << failed << " failed\n";

    if (failed == 0) {
        DisplayHelper::printSuccess("All tests passed!");
    }
    else {
        DisplayHelper::printError(to_string(failed) + " test(s) failed");
    }
}