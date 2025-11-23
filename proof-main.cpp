#include <iostream>
#include "ProofGenerator.h"
#include "CourseManager.h"
#include "Relations.h"
#include "DisplayHelper.h"

using namespace std;

int main() {
    DisplayHelper::printHeader("MODULE 8: AUTOMATED PROOF GENERATOR");

    CourseManager cm;
    Relations rel;

    cm.addCourse("CS101", "Programming", 3);
    cm.addCourse("CS102", "DataStructures", 4);
    cm.addCourse("CS201", "Algorithms", 4);

    rel.ensureSize(3);
    rel.addPrereq(0, 1);
    rel.addPrereq(1, 2);

    ProofGenerator proof(rel, cm);

    cout << "\n=== Test 1: Prerequisite Proof (All Satisfied) ===\n";
    vector<bool> completed1(3, false);
    completed1[0] = true;
    completed1[1] = true;
    proof.generatePrereqProof(2, completed1);
    proof.display();

    cout << "\n=== Test 2: Prerequisite Proof (Missing Prerequisites) ===\n";
    vector<bool> completed2(3, false);
    completed2[0] = true;
    proof.generatePrereqProof(2, completed2);
    proof.display();

    cout << "\n=== Test 3: Equivalence Relation Proof ===\n";
    vector<vector<bool>> equiv(3, vector<bool>(3, false));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            equiv[i][j] = true;
        }
    }
    proof.generateEquivalenceProof(equiv);
    proof.display();

    return 0;
}