#include <iostream>
#include "PerformanceBenchmark.h"
#include "DisplayHelper.h"

using namespace std;

int main() {
    DisplayHelper::printHeader("MODULE 10: PERFORMANCE BENCHMARKING");

    cout << "\nThis module will test algorithm performance with different data sizes.\n";
    cout << "Please wait while benchmarks run...\n\n";

    PerformanceBenchmark bench;
    bench.runAllBenchmarks();

    cout << "\nBenchmarking completed!\n";

    return 0;
}