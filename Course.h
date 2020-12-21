#ifndef COURSE
#define COURSE
#include <iostream>
#include "Class.h"
#include "library.h"
class Course
{
private:
    int courseId;
    int numOfClasses;
    Class** classes;
    const static int null_course = -1;
public:
    Course();
    Course(int courseId, int numOfClasses);
    ~Course();
    Course(Course& c);
    Course& operator=(Course& c);
    bool operator<(Course& c);
    bool operator>(Course& c);
    bool operator==(Course& c);
    bool operator<(int id);
    bool operator>(int id);
    bool operator==(int id);
    int getNumOfClasses();
    int getCourseId() const;
    StatusType addClass(int course_id, int class_id, int time);
    Class* getClass(int classId);
    friend std::ostream &operator<<(std::ostream &os, const Course &c);
};
#endif