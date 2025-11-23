
#ifndef PERFORMANCEBENCHMARK_H
#define PERFORMANCEBENCHMARK_H

#include <string>
#include <vector>
#include "Relations.h"
#include "CourseManager.h"
#include "PeopleManager.h"

class PerformanceBenchmark {
private:
    struct BenchResult {
        std::string operation;
        long long milliseconds;
        int dataSize;
    };

    std::vector<BenchResult> results;
    long long getTimeMillis();

public:
    template<typename Func>
    long long measure(Func f);

    void benchmarkTransitiveClosure(Relations& rel, int size);
    void benchmarkFunctionChecks(int size);
    void benchmarkConsistencyChecks(CourseManager& cm, PeopleManager& pm, Relations& rel, int size);
    void runAllBenchmarks();
    void displayResults() const;
};

#endif