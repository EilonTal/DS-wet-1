#include "Course.h"

Course::Course()
    : courseId(null_course), numOfClasses(0), classes(nullptr)
{
}

Course::Course(int id, int num)
    : courseId(id), numOfClasses(num), classes(new Class *[numOfClasses])
{
    for (int i=0; i<numOfClasses; i++)
    {
        classes[i] = nullptr;
    }
}

Course::~Course()
{
    delete [] classes;
}

Course::Course(Course &course)
    : courseId(course.courseId), numOfClasses(course.numOfClasses), classes(new Class *[numOfClasses])
{
    for (int i = 0; i < numOfClasses; i++)
    {
        if (course.getClass(i) != nullptr)
        {
            Class c(*(course.getClass(i)));
            classes[i] = &c;
        }
        else
        {
            classes[i] = nullptr;
        }
        
    }
}

Course& Course::operator=(Course &course)
{
    delete[] classes;
    courseId = course.courseId;
    numOfClasses = course.numOfClasses;
    classes = new Class*[numOfClasses];
    for (int i = 0; i < numOfClasses; i++)
    {
        
        if (course.getClass(i) != nullptr)
        {
            classes[i] = new Class(*(course.getClass(i)));
        }
        else
        {
            classes[i] = nullptr;
        }
    }
    return *this;
}

bool Course::operator<(Course &c)
{
    // we reversed the order of operation
    // since the "best" organ in the AVL tree is the one that has the highest ID
    return courseId > c.courseId;
}

bool Course::operator>(Course &c)
{
    return c < *this;
}

bool Course::operator==(Course &c)
{
    return courseId == c.courseId;
}

bool Course::operator==(int id)
{
    return courseId == id;
}

bool Course::operator<(int id)
{
    return courseId > id;
}

bool Course::operator>(int id)
{
    return courseId < id;
}

int Course::getNumOfClasses()
{
    return numOfClasses;
}

int Course::getCourseId() const
{
    return courseId;
}

StatusType Course::addClass(Class& c)
{

    if (classes[c.getClassId()] == nullptr)
    {
        classes[c.getClassId()] = &c;
        return SUCCESS;
    }

    return FAILURE;
}

Class* Course::getClass(int classId)
{
    if (classId >= numOfClasses || classId < 0 || classes == nullptr)
    {
        return nullptr;
    }
    return classes[classId];
}

//for debuge
std::ostream &operator<<(std::ostream &os, const Course &c)
{
    int id = c.getCourseId();
    os << id;
    return os;
}
