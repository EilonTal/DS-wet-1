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
    for (int i=0; i<numOfClasses; i++) 
    {
        if (classes[i] != nullptr)
        {
            delete classes[i];
            classes[i] = nullptr;
        }
    }
    delete [] classes;
}

Course::Course(Course &course)
    : courseId(course.courseId), numOfClasses(course.numOfClasses), classes(new Class *[numOfClasses])
{
    for (int i = 0; i < numOfClasses; i++)
    {
        classes[i] = new Class(*(course.getClass(i)));
    }
}

Course& Course::operator=(Course &course)
{
    for (int i = 0; i < numOfClasses; i++)
    {
        if (classes[i] != nullptr)
        {
            delete classes[i];
            classes[i] = nullptr;
        }
    }
    delete[] classes;
    courseId = course.courseId;
    numOfClasses = course.numOfClasses;
    classes = new Class*[numOfClasses];
    for (int i = 0; i < numOfClasses; i++)
    {
        classes[i] = new Class(*(course.getClass(i)));
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

int Course::getCourseId()
{
    return courseId;
}

StatusType Course::addClass(Class& c)
{
    for (int i = 0; i < numOfClasses; i++)
    {
        if (classes[i] == nullptr)
        {
            classes[i] = &c;
            return SUCCESS;
        }
    }
    return FAILURE;
}

Class* Course::getClass(int classId)
{
    if (courseId >= numOfClasses || courseId < 0 || classes == nullptr)
    {
        return nullptr;
    }
    return classes[courseId];
}