#include "ProofGenerator.h"
#include "DisplayHelper.h"
#include <iostream>

using namespace std;

ProofGenerator::ProofGenerator(const Relations& r, const CourseManager& c)
    : relations(r), cm(c) {
}

void ProofGenerator::generatePrereqProof(int courseId, const vector<bool>& completed) {
    proofSteps.clear();

    const auto* course = cm.getCourse(courseId);
    string courseName = course ? course->code : to_string(courseId);

    proofSteps.push_back({
        "THEOREM: Student can enroll in " + courseName,
        "To be proven using mathematical induction",
        0
        });

    proofSteps.push_back({
        "BASE CASE: Check direct prerequisites",
        "Definition of prerequisite relation",
        1
        });

    auto prereq = relations.getPrereqMatrix();
    bool hasDirectPrereq = false;

    for (int i = 0; i < (int)prereq.size(); i++) {
        if (prereq[i][courseId]) {
            hasDirectPrereq = true;
            const auto* p = cm.getCourse(i);
            string pName = p ? p->code : to_string(i);

            if (completed[i]) {
                proofSteps.push_back({
                    pName + " is completed [PASS]",
                    "Given in completed courses set",
                    2
                    });
            }
            else {
                proofSteps.push_back({
                    pName + " is NOT completed [FAIL]",
                    "Missing from completed set",
                    2
                    });
            }
        }
    }

    if (!hasDirectPrereq) {
        proofSteps.push_back({
            "No direct prerequisites required",
            "Empty prerequisite set",
            2
            });
    }

    proofSteps.push_back({
        "INDUCTIVE STEP: Check transitive closure",
        "Strong induction on prerequisite chain",
        1
        });

    auto closure = relations.closurePrereq();
    for (int i = 0; i < (int)closure.size(); i++) {
        if (closure[i][courseId] && i != courseId) {
            const auto* p = cm.getCourse(i);
            string pName = p ? p->code : to_string(i);

            if (completed[i]) {
                proofSteps.push_back({
                    "Indirect prerequisite " + pName + " satisfied [PASS]",
                    "By transitive closure of prerequisite relation",
                    2
                    });
            }
            else {
                proofSteps.push_back({
                    "Indirect prerequisite " + pName + " NOT satisfied [FAIL]",
                    "Required by transitivity",
                    2
                    });
            }
        }
    }

    bool allSatisfied = true;
    for (int i = 0; i < (int)closure.size(); i++) {
        if (closure[i][courseId] && !completed[i]) {
            allSatisfied = false;
            break;
        }
    }

    proofSteps.push_back({
        allSatisfied ? "CONCLUSION: Prerequisites satisfied [PASS] Q.E.D."
                    : "CONCLUSION: Prerequisites NOT satisfied [FAIL]",
        allSatisfied ? "By mathematical induction, all prerequisites met"
                    : "Proof fails - missing required courses",
        0
        });
}

void ProofGenerator::generateEquivalenceProof(const vector<vector<bool>>& relation) {
    proofSteps.clear();

    proofSteps.push_back({
        "THEOREM: Relation R is an equivalence relation",
        "Must prove reflexive, symmetric, and transitive",
        0
        });

    bool reflexive = true;
    for (int i = 0; i < (int)relation.size(); i++) {
        if (!relation[i][i]) {
            reflexive = false;
            break;
        }
    }

    proofSteps.push_back({
        reflexive ? "REFLEXIVE: For all x, (x,x) in R [PASS]" : "NOT REFLEXIVE [FAIL]",
        reflexive ? "Verified for all elements" : "Found element not related to itself",
        1
        });

    bool symmetric = true;
    for (int i = 0; i < (int)relation.size(); i++) {
        for (int j = 0; j < (int)relation.size(); j++) {
            if (relation[i][j] != relation[j][i]) {
                symmetric = false;
                break;
            }
        }
        if (!symmetric) break;
    }

    proofSteps.push_back({
        symmetric ? "SYMMETRIC: For all x,y, (x,y) in R implies (y,x) in R [PASS]" : "NOT SYMMETRIC [FAIL]",
        symmetric ? "Verified for all pairs" : "Found asymmetric pair",
        1
        });

    bool transitive = true;
    for (int i = 0; i < (int)relation.size(); i++) {
        for (int j = 0; j < (int)relation.size(); j++) {
            for (int k = 0; k < (int)relation.size(); k++) {
                if (relation[i][j] && relation[j][k] && !relation[i][k]) {
                    transitive = false;
                    break;
                }
            }
        }
    }

    proofSteps.push_back({
        transitive ? "TRANSITIVE: For all x,y,z, (x,y) and (y,z) implies (x,z) [PASS]" : "NOT TRANSITIVE [FAIL]",
        transitive ? "Verified for all triples" : "Found violation of transitivity",
        1
        });

    bool isEquiv = reflexive && symmetric && transitive;
    proofSteps.push_back({
        isEquiv ? "CONCLUSION: R is an equivalence relation [PASS] Q.E.D."
               : "CONCLUSION: R is NOT an equivalence relation [FAIL]",
        isEquiv ? "All three properties satisfied" : "One or more properties failed",
        0
        });
}

void ProofGenerator::display() const {
    DisplayHelper::printHeader("FORMAL PROOF (MODULE 8)");

    for (const auto& step : proofSteps) {
        string indent(step.level * 2, ' ');
        cout << indent << step.statement << "\n";
        cout << indent << "  -> " << step.justification << "\n\n";
    }
}