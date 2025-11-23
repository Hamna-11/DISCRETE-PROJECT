#include "PerformanceBenchmark.h"
#include "DisplayHelper.h"
#include "Functions.h"
#include "ConsistencyChecker.h"
#include "CustomMap.h"
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

long long PerformanceBenchmark::getTimeMillis() {
    return clock() * 1000 / CLOCKS_PER_SEC;
}

template<typename Func>
long long PerformanceBenchmark::measure(Func f) {
    long long start = getTimeMillis();
    f();
    long long end = getTimeMillis();
    return end - start;
}

void PerformanceBenchmark::benchmarkTransitiveClosure(Relations& rel, int size) {
    rel.ensureSize(size);

    for (int i = 0; i < size - 1; i++) {
        rel.addPrereq(i, i + 1);
    }

    long long time = measure([&]() {
        rel.closurePrereq();
        });

    results.push_back({ "Transitive Closure", time, size });
}

void PerformanceBenchmark::benchmarkFunctionChecks(int size) {
    CustomMap<int, int> f;
    for (int i = 0; i < size; i++) {
        f.insert(i, i % (size / 2));
    }

    long long time = measure([&]() {
        Functions::isInjective(f);
        Functions::isSurjective(f, size);
        Functions::isBijective(f, size);
        });

    results.push_back({ "Function Property Checks", time, size });
}

void PerformanceBenchmark::benchmarkConsistencyChecks(CourseManager& cm, PeopleManager& pm,
    Relations& rel, int size) {
    for (int i = 0; i < size; i++) {
        cm.addCourse("CS" + to_string(i), "Course" + to_string(i), 3);
        string studentNames[] = { "Noor", "Khadija", "Nimra", "Kashaf" };
        pm.addStudent(studentNames[i % 4] + to_string(i));
    }

    CustomMap<int, int> cf, cr;
    ConsistencyChecker checker(cm, pm, rel, cf, cr);

    long long time = measure([&]() {
        checker.runAllChecks();
        });

    results.push_back({ "Consistency Checks", time, size });
}

void PerformanceBenchmark::runAllBenchmarks() {
    DisplayHelper::printHeader("PERFORMANCE BENCHMARKING (MODULE 10)");

    cout << "\nRunning benchmarks...\n";

    Relations rel1, rel2, rel3;

    benchmarkTransitiveClosure(rel1, 10);
    benchmarkTransitiveClosure(rel2, 20);
    benchmarkTransitiveClosure(rel3, 50);

    benchmarkFunctionChecks(100);
    benchmarkFunctionChecks(500);
    benchmarkFunctionChecks(1000);

    CourseManager cm;
    PeopleManager pm;
    Relations rel4;
    benchmarkConsistencyChecks(cm, pm, rel4, 20);

    displayResults();
}

void PerformanceBenchmark::displayResults() const {
    DisplayHelper::printHeader("BENCHMARK RESULTS");

    cout << "\n" << left << setw(35) << "Operation"
        << setw(15) << "Time (ms)" << "Data Size\n";
    cout << string(60, '-') << "\n";

    for (const auto& r : results) {
        cout << left << setw(35) << r.operation
            << setw(15) << r.milliseconds
            << r.dataSize << "\n";
    }

    cout << "\nNote: ms = milliseconds\n";
}