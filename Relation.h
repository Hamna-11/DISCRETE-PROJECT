#ifndef RELATIONS_H
#define RELATIONS_H

#include <vector>

class Relations {
private:
    std::vector<std::vector<bool>> prereq;
    int size;

public:
    Relations();
    void ensureSize(int n);
    void addPrereq(int a, int b);
    bool getPrereq(int a, int b) const;
    int getSize() const;
    std::vector<std::vector<bool>> closurePrereq() const;
    bool hasPrereqCycle() const;
    const std::vector<std::vector<bool>>& getPrereqMatrix() const;
};

#endif