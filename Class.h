#ifndef CLASS
#define CLASS
#include <memory>
#include <iostream>
class Class
{
private:
    int time;
    int courseId;
    int classId;
public:
    Class();
    Class(int coursId, int classId, int time = 0);
    ~Class() = default;
    Class(Class& c) = default;
    Class& operator=(Class& c) = default;
    bool operator<(Class& c);
    bool operator>(Class& c);
    bool operator==(Class &c);
    int getTime();
    int getCourseId();
    int getClassId();
    void addTime(int time);
    friend std::ostream &operator<<(std::ostream &os, const Class &c);
};

#endif