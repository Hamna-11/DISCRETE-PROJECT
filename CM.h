#ifndef COURSEMANAGER_H
#define COURSEMANAGER_H

#include <string>
#include <vector>

class CourseManager {
public:
    struct Course {
        int id;
        std::string code;
        std::string name;
        int credits;

        Course();
        Course(int i, std::string c, std::string n, int cr);
    };

private:
    std::vector<Course> courses;

public:
    int addCourse(const std::string& code, const std::string& name, int credits);
    const Course* getCourse(int id) const;
    int count() const;
    void listAll() const;
};

#endif