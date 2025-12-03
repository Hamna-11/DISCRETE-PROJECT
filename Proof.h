#ifndef PROOFGENERATOR_H
#define PROOFGENERATOR_H

#include <string>
#include <vector>
#include "Relations.h"
#include "CourseManager.h"

class ProofGenerator {
private:
    struct ProofStep {
        std::string statement;
        std::string justification;
        int level;
    };

    const Relations& relations;
    const CourseManager& cm;
    std::vector<ProofStep> proofSteps;

public:
    ProofGenerator(const Relations& r, const CourseManager& c);
    void generatePrereqProof(int courseId, const std::vector<bool>& completed);
    void generateEquivalenceProof(const std::vector<std::vector<bool>>& relation);
    void display() const;
};

#endif