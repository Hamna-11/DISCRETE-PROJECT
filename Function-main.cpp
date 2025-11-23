#include "Functions.h"
#include "DisplayHelper.h"
#include <iostream>
#include <iomanip>

using namespace std;

bool Functions::isInjective(const CustomMap<int, int>& f) {
    CustomSet<int> values;
    for (const auto& pair : f) {
        if (values.contains(pair.second)) return false;
        values.insert(pair.second);
    }
    return true;
}

bool Functions::isSurjective(const CustomMap<int, int>& f, int codomainSize) {
    CustomSet<int> values;
    for (const auto& pair : f) {
        values.insert(pair.second);
    }
    return values.size() == codomainSize;
}

bool Functions::isBijective(const CustomMap<int, int>& f, int codomainSize) {
    return isInjective(f) && isSurjective(f, codomainSize);
}

CustomMap<int, int> Functions::compose(const CustomMap<int, int>& f, const CustomMap<int, int>& g) {
    CustomMap<int, int> result;
    for (const auto& pair : f) {
        const int* gval = g.get(pair.second);
        if (gval) {
            result.insert(pair.first, *gval);
        }
    }
    return result;
}

void Functions::display(const CustomMap<int, int>& courseToFaculty, const CourseManager& cm, PeopleManager& pm) {
    DisplayHelper::printHeader("FUNCTION PROPERTIES (MODULE 7)");
    
    cout << "\nAnalyzing Course -> Faculty mapping\n";
    cout << "Domain size: " << courseToFaculty.size() << "\n";
    cout << "Codomain size: " << pm.getFacultyCount() << "\n\n";
    
    bool inj = isInjective(courseToFaculty);
    bool sur = isSurjective(courseToFaculty, pm.getFacultyCount());
    bool bij = isBijective(courseToFaculty, pm.getFacultyCount());
    
    cout << "Properties:\n";
    cout << "  Injective (One-to-One): " << (inj ? "[YES]" : "[NO]") << "\n";
    cout << "  Surjective (Onto):      " << (sur ? "[YES]" : "[NO]") << "\n";
    cout << "  Bijective:              " << (bij ? "[YES]" : "[NO]") << "\n\n";
    
    cout << "Mapping:\n";
    for (const auto& pair : courseToFaculty) {
        const auto* course = cm.getCourse(pair.first);
        auto* faculty = pm.getFaculty(pair.second);
        cout << "  " << (course ? course->code : to_string(pair.first)) << " -> "
             << (faculty ? faculty->name : to_string(pair.second)) << "\n";
    }
    cout << "\n";
}
