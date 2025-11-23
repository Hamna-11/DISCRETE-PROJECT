#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "CustomMap.h"
#include "CustomSet.h"
#include "CourseManager.h"
#include "PeopleManager.h"

class Functions {
public:
    static bool isInjective(const CustomMap<int, int>& f);
    static bool isSurjective(const CustomMap<int, int>& f, int codomainSize);
    static bool isBijective(const CustomMap<int, int>& f, int codomainSize);
    static CustomMap<int, int> compose(const CustomMap<int, int>& f, const CustomMap<int, int>& g);
    static void display(const CustomMap<int, int>& courseToFaculty, const CourseManager& cm, PeopleManager& pm);
};

#endif