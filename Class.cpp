#include "Class.h"

Class::Class()
    : courseId(0), classId(0), time(0)
{
}

Class::Class(int course_id, int class_id, int t)
    : courseId(course_id), classId(class_id), time(t)
{
}

bool Class::operator<(Class &c)
{
    if (time < c.time)
    {
        return false;
    }
    if (time > c.time)
    {
        return true;
    }
    if (courseId > c.courseId)
    {
        return false;
    }
    if (courseId < c.courseId)
    {
        return true;
    }
    return classId < c.classId;
}

bool Class::operator>(Class &c)
{
    return c < *this;
}

bool Class::operator==(Class &c)
{
    return !((*this<c)||(*this>c));
}

int Class::getTime()
{
    return time;
}

int Class::getCourseId()
{
    return courseId;
}

int Class::getClassId()
{
    return classId;
}

void Class::addTime(int t)
{
    time +=t ;
}

std::ostream &operator<<(std::ostream &os, const Class &c)
{
    os <<c.courseId<<":"<<c.classId<<":"<<c.time;
    return os;
}