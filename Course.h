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
    int getCourseId();
    StatusType addClass(Class& c);
    Class* getClass(int classId);
};

