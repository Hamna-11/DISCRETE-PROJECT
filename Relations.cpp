#include "Relations.h"
#include <algorithm>

using namespace std;

Relations::Relations() : size(0) {}

void Relations::ensureSize(int n) {
    if (n > size) {
        prereq.resize(n, vector<bool>(n, false));
        size = n;
    }
}

void Relations::addPrereq(int a, int b) {
    ensureSize(max(a, b) + 1);
    prereq[a][b] = true;
}

bool Relations::getPrereq(int a, int b) const {
    if (a < 0 || b < 0 || a >= size || b >= size) return false;
    return prereq[a][b];
}

int Relations::getSize() const {
    return size;
}

vector<vector<bool>> Relations::closurePrereq() const {
    vector<vector<bool>> result = prereq;

    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (result[i][k] && result[k][j]) {
                    result[i][j] = true;
                }
            }
        }
    }
    return result;
}

bool Relations::hasPrereqCycle() const {
    auto closure = closurePrereq();
    for (int i = 0; i < size; i++) {
        if (closure[i][i]) return true;
    }
    return false;
}

const vector<vector<bool>>& Relations::getPrereqMatrix() const {
    return prereq;
}