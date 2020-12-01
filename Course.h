#include "Class.h"
class Course
{
private:
    int courseId;
    int numOfClasses;
    std::shared_ptr<Class>* classes;
public:
    Course(int courseId, int numOfClasses);
    ~Course();
    Course(Course& c);
    Course& operator=(Course& c);
    bool operator<(Course& c);
    bool operator>(Course& c);
    bool operator==(Course& c);
    int getNumOfClasses();
    int getCourseId();
    std::shared_ptr<Class>& getClass(int classId);
};

